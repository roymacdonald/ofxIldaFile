//
//  ofxIldaFileFrame.cpp
//  example
//
//  Created by Roy Macdonald on 7/20/19.
//
//

#include "ofxIldaFileFrame.h"
//--------------------------------------------------------------
bool ofxIldaFileFrame::readHeader(ofBuffer& buffer, size_t i){
	char* b = buffer.getData();
	string bStr = buffer.getText();
	
	if(bStr.substr(i, 4) == "ILDA"){//bytes 0,1,2,3
		//bytes 4, 5 and 6 are reserved, these must be zero
		format =  b[i+7];// byte 7
		if ( format >=0  && format <= 5 && format != 3){
			point_number = getShort(b, i+24);
			if ( point_number > 0 ){
				frame_name = bStr.substr(i+8, 8);
				company_name = bStr.substr(i+16, 8);
				
				frame_number=  getShort(b, i+26);//(((b[i+26] & 0xFF) << 8) | (b[i+27] & 0xFF));
				total_frame=  getShort(b, i+28);//(((b[i+28] & 0xFF) << 8) | (b[i+29] & 0xFF));
				scanner=  (b[i+30] & 0xFF);

				start_id=i;
				return true;
			}
		} else{
			ofLogError("ofxIldaFileFrame::readHeader") << "invalid ilda frame format";
		}
	}
	return false;
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
void ofxIldaFileFrame::decodeData(char * d, size_t size, bool bNormalize){
	path.clear();
	path.setMode(OF_PRIMITIVE_LINE_STRIP);
	auto stride = getNumDataBytesForFormat();
	size_t end = std::min(start_id + 32 + (point_number * stride), size);
	
	for(size_t i = start_id + 32;  i < end; i+= stride){
		
		glm::vec3 v ={getShort(d, i), getShort(d, i+2), 0};
		if(format == 0 || format == 4){
			v.z = getShort(d, i + 4);
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
		readStatusCode(d, i);
		if(((status_code >> 6) & 0x01) == 1){
			c.a = 0;
		}
		path.addColor(c);
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
void ofxIldaFileFrame::readStatusCode(char * d, size_t i){
	if(format == 0 || format == 4){
		status_code = d[i+ 6];
	}else if(format == 1 || format == 5){
		status_code = d[i+ 4];
	}
}
//--------------------------------------------------------------
int ofxIldaFileFrame::getColorOffset(){
	if(format == 0 || format == 4){
		return 7;
	}else if(format == 1 || format == 5){
		return 5;
	}
	return 0;
}
