//
//  ofxIlda::FileFrame.cpp
//  example
//
//  Created by Roy Macdonald on 7/20/19.
//
//

#include "ofxIldaFileFrame.h"
//#define DISABLE_BLANKING

ofxIlda::FileFrame::FileFrame(const ofxIlda::FileFormat& format, const string& frameName, const string& companyName){
	setup(format, frameName, companyName);
}
//--------------------------------------------------------------
void ofxIlda::FileFrame::setup(const ofxIlda::FileFormat& format, const string& frameName, const string& companyName ){
	this->format = format;
	this->frame_name = frameName;
	this->company_name = companyName;
//	this->bNormalizedData = bNormalizeData;
	resetPaths();
}
//--------------------------------------------------------------
void ofxIlda::FileFrame::addPoint(glm::vec3 point, const ofColor& color, bool bIsNormalized){
//	if(bIsNormalized && !bNormalizedData){
	if(bIsNormalized){
		normalizedPath.addVertex(point);
		unnormalizePoint(point);
		path.addVertex(point);
	}else{// if(!bIsNormalized && bNormalizedData){
		path.addVertex(point);
		normalizePoint(point);
		normalizedPath.addVertex(point);
	}
//	cout << point << endl;
//	path.addVertex(point);
	path.addColor(color);
	normalizedPath.addColor(color);
	
	
//	point_number = path.getNumVertices();
}


void padStringEnd(string& s){
	if(s.length() < 8){
		s += string(8-s.length(), '-');
//		cout << "padStringEnd: " << s << endl;
	}
}

//--------------------------------------------------------------
size_t ofxIlda::FileFrame::readHeader(ofBuffer& buffer, size_t i){
	char* b = buffer.getData();
	string bStr = buffer.getText();
	
	if(bStr.substr(i, 4) == "ILDA"){//bytes 0,1,2,3
		//bytes 4, 5 and 6 are reserved, these must be zero
		int fmt = b[i+7];
		if(!validateFormat(fmt)){
			ofLogError("ofxIlda::FileFrame::readHeader") << "invalid ilda frame format";
			return 0;
		}
		format =  (ofxIlda::FileFormat) fmt;
		size_t point_number = getShortFromChars(b, i+24);
		
		frame_name = bStr.substr(i+8, 8);
		company_name = bStr.substr(i+16, 8);
		
		frame_number=  getShortFromChars(b, i+26);//(((b[i+26] & 0xFF) << 8) | (b[i+27] & 0xFF));
		total_frame=  getShortFromChars(b, i+28);//(((b[i+28] & 0xFF) << 8) | (b[i+29] & 0xFF));
		scanner=  (b[i+30] & 0xFF);
		
		start_id=i;
		
		bFrameSet = true;
		return  point_number;
		
	}
	return false;
}
//--------------------------------------------------------------
void setFromString(const string & s, size_t start, std::vector<char> &b){
	
	for(size_t i = 0; i < s.size() && i + start < b.size(); i++){
		b[start+i] = s.at(i);
	}
}

//--------------------------------------------------------------
void ofxIlda::FileFrame::writeHeader(ofBuffer& buffer){
	std::vector<char> b;
	b.resize(32, 0);// the header is always 32 bytes long
	
	setFromString("ILDA", 0, b);

	b[7] = (char)format; // byte 7
	
	setFromString(frame_name, 8, b);
	setFromString(company_name, 16, b);
	setShortIntoChars(b, getNumPoints(), 24);
	setShortIntoChars(b, frame_number, 26);
	setShortIntoChars(b, total_frame,  28);
	b[30] = (scanner & 0xFF);
	
	buffer.append(b.data(), b.size());

}
//--------------------------------------------------------------
bool ofxIlda::FileFrame::readFromBuffer(ofBuffer& buffer, size_t startIndex){
	auto numPoints = readHeader(buffer, startIndex);
	if(numPoints){
//		decodeData(buffer.getData(), numPoints, buffer.size());
		decodeData(buffer, numPoints);
		return true;
	}
	return false;
}
//--------------------------------------------------------------
void ofxIlda::FileFrame::writeToBuffer(ofBuffer& buffer){
	writeHeader(buffer);
	encodeData(buffer);
}
#ifdef OFX_ILDA_FILE_FRAME_DEBUG
bool compVecAsShorts(const glm::vec3& v1, const glm::vec3& v2){
	return  ((short)v1.x == (short)v2.x) &&
			((short)v1.y == (short)v2.y) &&
			((short)v1.z == (short)v2.z) ;
}
#endif
//--------------------------------------------------------------
void ofxIlda::FileFrame::decodeData(ofBuffer& buffer, size_t num_points){
	resetPaths();	
	char * d = buffer.getData();
	
	auto stride = getNumDataBytesForFormat();
	size_t end = std::min(start_id + 32 + (num_points * stride), buffer.size());
	
#ifdef OFX_ILDA_FILE_FRAME_DEBUG
	size_t lastOff = 0;
#endif
	
	for(size_t i = start_id + 32;  i < end; i+= stride){
		
		glm::vec3 v ={getShortFromChars(d, i), getShortFromChars(d, i+2), 0};
		if(ifFormat3D(format)){
			v.z = getShortFromChars(d, i + 4);
		}
		ofColor  c;
		int colorOffset = getColorOffset();
		if(ifFormatIndexedColor(format)){
//			cout << "color index: " << (int)d[i+ colorOffset] <<endl;
			c = ilda_standard_color_palette()[d[i+ colorOffset]];
		}else{
			c.r = d[i+ colorOffset];
			c.g = d[i+ colorOffset + 1];
			c.b = d[i+ colorOffset + 2];
		}
//		readStatusCode(d, i);
		int statusOffset = getStatusCodeOffset();
		if(statusOffset >= 0){
			char status_code = d[i+statusOffset];
			if(((status_code >> 6) & 0x01) == 1){
				c.a = 0;
//				cout << "blanked " <<endl;
#ifndef OFX_ILDA_FILE_FRAME_DEBUG
			}
#else
				lastOff++;
			}
			else if(lastOff > 0){
//				cout << "lastOff  "<<lastOff <<  endl;
				endsMap[path.getNumVertices()] = lastOff;
				lastOff = 0;
			}
		}else {
//			cout << "lastOff __ "<<lastOff << endl;
			lastOff = 0;
#endif
		}
		
		addPoint(v, c, false);
	}
#ifdef OFX_ILDA_FILE_FRAME_DEBUG
	auto & v = path.getVertices();
	auto & c = path.getColors();
	for(size_t i = 0; i < v.size(); i ++){
		
		size_t n = 0;
		
		for(size_t j = 0; j < v.size(); j ++){
			if(i != j){
				if(compVecAsShorts(v[i], v[j]) && c[i].a > 0 ){
					n++;
				}
			}
		}
		if(n > 0){
			repVMap[i] = n;
		}
	}
#endif
}
//--------------------------------------------------------------
void ofxIlda::FileFrame::encodeData(ofBuffer& buffer){
	
	auto stride = getNumDataBytesForFormat();
//	size_t end = start_id + 32 + (point_number * stride);//, size);
	auto& verts = path.getVertices();
	auto& colors = path.getColors();
	if(verts.size() != colors.size()){
		ofLogWarning("ofxIlda::FileFrame::encodeData") << "vertex and colors numbers differ. These must be the same";
	}
	
	for(size_t i = 0 ;  i < verts.size(); i++){
		std::vector<char> d (stride, 0);
		glm::vec3 v = verts[i];
		ofColor  c = colors[i];
		
		setShortIntoChars(d, v.x, 0);
		setShortIntoChars(d, v.y, 2);
		
		if(ifFormat3D(format)){
			setShortIntoChars(d, v.z, 4);
		}
			
//		if(c.a != 0){
		int colorOffset = getColorOffset();
		
		if(ifFormatIndexedColor(format)){
			int ind = findColorInPalette(c);
			if(ind < 0) {
				ind =0;
				ofLogWarning("ofxIlda::FileFrame::encodeData")<< "indexed color " << c << ", not found in palette.";
			}
			d[colorOffset] = ind;
//			c = ilda_standard_color_palette()[d[i+ colorOffset]];
		}else{
			 d[colorOffset] = c.r;
			 d[colorOffset + 1] = c.g;
			 d[colorOffset + 2] = c.b;
		}
//		}
		int statusOffset = getStatusCodeOffset();
		if(statusOffset > 0){
			char status_code = 0;
#ifndef DISABLE_BLANKING
			if(c.a == 0){
//				cout << "disable blanking" <<endl;
				status_code |= (1 << 6) & 0xFF;
			}
#endif
			if(i == verts.size()-1){
				status_code |= (1 << 7) & 0xFF;
			}
			d[statusOffset] = status_code;
		}
		buffer.append(d.data(), d.size());
	}
}
//--------------------------------------------------------------
std::ostream&  ofxIlda:: operator << (std::ostream& os, const ofxIlda::FileFrame& f) {
	os << "format " << formatToString(f.format) <<"\n";
	os << "frame_name " << f.frame_name <<"\n";
	os << "company_name " << f.company_name <<"\n";
	os << "point_number " << f.getNumPoints() <<"\n";
	os << "frame_number " << f.frame_number <<"\n";
	os << "total_frame " << f.total_frame <<"\n";
	os << "scanner " << (int)f.scanner <<"\n";
	os << "start_id " << f.start_id <<"\n";
	//	os << "normalized points: " << std::boolalpha << f.bNormalizedData;
	return os;
}

//--------------------------------------------------------------
string ofxIlda::FileFrame::getAsString(){
	stringstream ss;
	ss << formatToString(format) << ", " ;
	ss << frame_name << ", " ;
	ss << company_name << ", " ;
	ss << getNumPoints() << ", " ;
	ss << frame_number << ", " ;
	ss << total_frame << ", " ;
	ss << (int)scanner << ", " ;
//	ss << bitset<8>(status_code);
//	ss << start_id ;
	return ss.str();
}
//--------------------------------------------------------------
ofxIlda::FileFrame ofxIlda::FileFrame::getEndFrame(const ofxIlda::FileFrame& refFrame){
	ofxIlda::FileFrame f;
	f.format = refFrame.getFormat();
	f.frame_name = "        ";
	f.company_name = "        ";
//	f.point_number = 0;
//	f.status_code =  0x11000000;
	f.frame_number = 0;
	f.total_frame = refFrame.getTotalFrames();
	f.scanner = 0;

	return f;
}
//--------------------------------------------------------------
const ofxIlda::FileFormat& ofxIlda::FileFrame::getFormat() const {
	return format; 
}
//--------------------------------------------------------------
const string& ofxIlda::FileFrame::getFrameName() const {
	return frame_name; 
}
//--------------------------------------------------------------
const string& ofxIlda::FileFrame::getCompanyName() const {
	return company_name; 
}
//--------------------------------------------------------------
 size_t ofxIlda::FileFrame::getNumPoints() const{
	return path.getVertices().size();
//	return point_number; 
}
//--------------------------------------------------------------
const size_t& ofxIlda::FileFrame::getFrameNumber() const {
	return frame_number; 
}
//--------------------------------------------------------------
const size_t& ofxIlda::FileFrame::getTotalFrames() const {
	return total_frame; 
}
//--------------------------------------------------------------
const char& ofxIlda::FileFrame::getScanner() const {
	return scanner; 
}
//--------------------------------------------------------------
const size_t& ofxIlda::FileFrame::getStartIndex() const {
	return start_id; 
}
//--------------------------------------------------------------
size_t ofxIlda::FileFrame::getDataSize(){
	return getNumDataBytesForFormat() * getNumPoints();
}
//--------------------------------------------------------------
int ofxIlda::FileFrame::getNumDataBytesForFormat(){
	switch(format){
		case ofxIlda::FILE_FORMAT_3D_INDEXED_COLOR: return 8;
		case ofxIlda::FILE_FORMAT_2D_INDEXED_COLOR: return 6;
		case ofxIlda::FILE_FORMAT_COLOR_PALETTE: return 3;
		case ofxIlda::FILE_FORMAT_3D_TRUE_COLOR: return 10;
		case ofxIlda::FILE_FORMAT_2D_TRUE_COLOR: return 8;
		case ofxIlda::FILE_FORMAT_INVALID: return 0;
	}
	return 0;
}
//--------------------------------------------------------------
int ofxIlda::FileFrame::getStatusCodeOffset(){
	if(ifFormat3D(format)){
		return 6;
	}else if(ifFormat2D(format)){
		return 4;
	}
	return -1;
}

//--------------------------------------------------------------
int ofxIlda::FileFrame::getColorOffset(){
	if(ifFormat3D(format)){
		return 7;
	}else if(ifFormat2D(format)){
		return 5;
	}
	return -1;
}
//--------------------------------------------------------------
void ofxIlda::FileFrame::resetPaths(){
	path.clear();
	path.setMode(OF_PRIMITIVE_LINE_STRIP);
	
	normalizedPath.clear();
	normalizedPath.setMode(OF_PRIMITIVE_LINE_STRIP);

}

//--------------------------------------------------------------
bool ofxIlda::FileFrame::validateFormat(const int& format){
	if (format == 3) return false;
	if (format >= 0 && format <= 5)return true;
	return false;
}
