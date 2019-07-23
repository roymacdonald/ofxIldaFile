//
//  ofxIldaFileFrame.cpp
//  example
//
//  Created by Roy Macdonald on 7/20/19.
//
//

#include "ofxIldaFileFrame.h"

void padStringEnd(string& s){
	if(s.length() < 8){
		s += string(8-s.length(), '-');
//		cout << "padStringEnd: " << s << endl;
	}
}

//--------------------------------------------------------------
bool ofxIldaFileFrame::readHeader(ofBuffer& buffer, size_t i){
	char* b = buffer.getData();
	string bStr = buffer.getText();
	
	if(bStr.substr(i, 4) == "ILDA"){//bytes 0,1,2,3
		//bytes 4, 5 and 6 are reserved, these must be zero
		format =  b[i+7];// byte 7
		if ( format >=0  && format <= 5 && format != 3){
			point_number = getShortFromChars(b, i+24);
//			if ( point_number > 0 ){
				frame_name = bStr.substr(i+8, 8);
				company_name = bStr.substr(i+16, 8);
			
				frame_number=  getShortFromChars(b, i+26);//(((b[i+26] & 0xFF) << 8) | (b[i+27] & 0xFF));
				total_frame=  getShortFromChars(b, i+28);//(((b[i+28] & 0xFF) << 8) | (b[i+29] & 0xFF));
				scanner=  (b[i+30] & 0xFF);

				start_id=i;
//				return true;
				bFrameSet = true;
			return  point_number > 0;
//			}
		} else{
			ofLogError("ofxIldaFileFrame::readHeader") << "invalid ilda frame format";
		}
	}
	return false;
}

void setFromString(const string & s, size_t start, std::vector<char> &b){
	
	for(size_t i = 0; i < s.size() && i + start < b.size(); i++){
		b[start+i] = s.at(i);
	}
}

//--------------------------------------------------------------
void ofxIldaFileFrame::writeHeader(ofBuffer& buffer){
	std::vector<char> b;
	b.resize(32, 0);// the header is always 32 bytes long
	
	setFromString("ILDA", 0, b);

	b[7] = format; // byte 7
	
	setFromString(frame_name, 8, b);
	setFromString(company_name, 16, b);
	setShortIntoChars(b, point_number, 24);
	setShortIntoChars(b, frame_number, 26);
	setShortIntoChars(b, total_frame,  28);
	b[30] = (scanner & 0xFF);
	
	buffer.append(b.data(), b.size());

}
//--------------------------------------------------------------
bool ofxIldaFileFrame::readFromBuffer(ofBuffer& buffer, size_t startIndex){
	if(readHeader(buffer, startIndex)){
		decodeData(buffer.getData(), buffer.size());
		return true;
	}
	return false;
}
//--------------------------------------------------------------
void ofxIldaFileFrame::writeToBuffer(ofBuffer& buffer){
	writeHeader(buffer);
	encodeData(buffer);
}
//--------------------------------------------------------------
void ofxIldaFileFrame::decodeData(char * d, size_t size, bool bNormalize){
	path.clear();
	path.setMode(OF_PRIMITIVE_LINE_STRIP);
	
	bNormalizedData = bNormalize;
	
	auto stride = getNumDataBytesForFormat();
	size_t end = std::min(start_id + 32 + (point_number * stride), size);
	
	for(size_t i = start_id + 32;  i < end; i+= stride){
		
		glm::vec3 v ={getShortFromChars(d, i), getShortFromChars(d, i+2), 0};
		if(format == 0 || format == 4){
			v.z = getShortFromChars(d, i + 4);
		}
		if(bNormalize){
			v.x = ofMap(v.x, -32768, 32767, -1, 1);
			v.y = ofMap(v.y, -32768, 32767, -1, 1);
			if(format == 0 || format == 4){
				v.z = ofMap(v.z, -32768, 32767, -1, 1);
			}
		}
		path.addVertex(v);
		ofColor  c;
		int colorOffset = getColorOffset();
		if(format == 0 || format == 1){
			c = ilda_standard_color_palette()[d[i+ colorOffset]];
		}else{
			c.r = d[i+ colorOffset];
			c.g = d[i+ colorOffset + 1];
			c.b = d[i+ colorOffset + 2];
		}
//		readStatusCode(d, i);
		int statusOffset = getStatusCodeOffset();
		if(statusOffset < 0){
			status_code = 0;
		}else{
			status_code = d[i+statusOffset];
			if(((status_code >> 6) & 0x01) == 1){
				c.a = 0;
			}
		}
		path.addColor(c);
	}	
}
//--------------------------------------------------------------
void ofxIldaFileFrame::encodeData(ofBuffer& buffer){
	
	auto stride = getNumDataBytesForFormat();
//	size_t end = start_id + 32 + (point_number * stride);//, size);
	auto& verts = path.getVertices();
	auto& colors = path.getColors();
	if(verts.size() != colors.size()){
		ofLogWarning("ofxIldaFileFrame::encodeData") << "vertex and colors numbers differ. These must be the same";
	}
	
	for(size_t i = 0 ;  i < verts.size(); i++){
		std::vector<char> d (stride, 0);
		glm::vec3 v = verts[i];
		ofColor  c = colors[i];
		
		
		if(bNormalizedData){
			v.x = ofMap(v.x, -1, 1, -32768, 32767);
			v.y = ofMap(v.y, -1, 1, -32768, 32767);
			if(format == 0 || format == 4){
				v.z = ofMap(v.z, -1, 1, -32768, 32767);
			}
		}
		
		setShortIntoChars(d, v.x, 0);
		setShortIntoChars(d, v.y, 2);
		if(format == 0 || format == 4){
			setShortIntoChars(d, v.z, 4);
		}
			
		if(c.a != 0){
		int colorOffset = getColorOffset();
		
		if(format == 0 || format == 1){
			int ind = findColorInPalette(c);
			if(ind < 0) {
				ind =0;
				ofLogWarning("ofxIldaFileFrame::encodeData")<< "indexed color " << c << ", not found in palette.";
			}
			d[colorOffset] = ind;
//			c = ilda_standard_color_palette()[d[i+ colorOffset]];
		}else{
			 d[colorOffset] = c.r;
			 d[colorOffset + 1] = c.g;
			 d[colorOffset + 2] = c.b;
		}
		}
		int statusOffset = getStatusCodeOffset();
		if(statusOffset > 0){
			status_code = 0;
			if(c.a == 0){
				status_code |= (1 << 6) & 0xFF;
			}
			if(i == verts.size()-1){
				status_code |= (1 << 7) & 0xFF;
			}
			d[statusOffset] = status_code;
		}
		buffer.append(d.data(), d.size());
	}
}
//--------------------------------------------------------------
std::ostream& operator << (std::ostream& os, const ofxIldaFileFrame& f) {
	os << "format " << f.format <<"\n";
	os << "frame_name " << f.frame_name <<"\n";
	os << "company_name " << f.company_name <<"\n";
	os << "point_number " << f.point_number <<"\n";
	os << "frame_number " << f.frame_number <<"\n";
	os << "total_frame " << f.total_frame <<"\n";
	os << "scanner " << (int)f.scanner <<"\n";
	os << "start_id " << f.start_id <<"\n";
	return os;
}
string ofxIldaFileFrame::getAsString(){
	stringstream ss;
	ss << format << ", " ;
	ss << frame_name << ", " ;
	ss << company_name << ", " ;
	ss << " p - "<<point_number << ", " ;
	ss << frame_number << ", " ;
	ss << total_frame << ", " ;
	ss << (int)scanner << ", " ;
	ss << bitset<8>(status_code);
//	ss << start_id ;
	return ss.str();
}
ofxIldaFileFrame ofxIldaFileFrame::getEndFrame(const ofxIldaFileFrame& refFrame){
	ofxIldaFileFrame f;
	f.format = refFrame.getFormat();
	f.frame_name = "";
	f.company_name = refFrame.getCompanyName();
	f.point_number = 0;
	f.status_code =  0x11000000;
	f.frame_number = 0;
	f.total_frame = refFrame.getTotalFrames();
	f.scanner = 0;

	return f;
}
//--------------------------------------------------------------
const int& ofxIldaFileFrame::getFormat() const {
	return format; 
}
//--------------------------------------------------------------
const string& ofxIldaFileFrame::getFrameName() const {
	return frame_name; 
}
//--------------------------------------------------------------
const string& ofxIldaFileFrame::getCompanyName() const {
	return company_name; 
}
//--------------------------------------------------------------
const size_t& ofxIldaFileFrame::getPointNumber() const {
	return point_number; 
}
//--------------------------------------------------------------
const size_t& ofxIldaFileFrame::getFrameNumber() const {
	return frame_number; 
}
//--------------------------------------------------------------
const size_t& ofxIldaFileFrame::getTotalFrames() const {
	return total_frame; 
}
//--------------------------------------------------------------
const char& ofxIldaFileFrame::getStatusCode() const {
	return status_code; 
}
//--------------------------------------------------------------
const char& ofxIldaFileFrame::getScanner() const {
	return scanner; 
}
//--------------------------------------------------------------
const size_t& ofxIldaFileFrame::getStartIndex() const {
	return start_id; 
}
//--------------------------------------------------------------
size_t ofxIldaFileFrame::getDataSize(){
	return getNumDataBytesForFormat() * point_number;
}
//--------------------------------------------------------------
int ofxIldaFileFrame::getNumDataBytesForFormat(){
	switch(format){
		case 0: return 8;
		case 1: return 6;
		case 2: return 3;
		case 4: return 10;
		case 5: return 8;
	}
	return 0;
}
//--------------------------------------------------------------
int ofxIldaFileFrame::getStatusCodeOffset(){
	if(format == 0 || format == 4){
		return 6;
	}else if(format == 1 || format == 5){
		return 4;
	}
	return -1;
}

//--------------------------------------------------------------
int ofxIldaFileFrame::getColorOffset(){
	if(format == 0 || format == 4){
		return 7;
	}else if(format == 1 || format == 5){
		return 5;
	}
	return -1;
}
//--------------------------------------------------------------
bool ofxIldaFileFrame::isDataNormalized(){
	return bNormalizedData;
}
