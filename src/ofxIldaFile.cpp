#include "ofxIldaFile.h"

//--------------------------------------------------------------
ofxIldaFile::ofxIldaFile(){
	cam.removeAllInteractions();
	cam.addInteraction(ofEasyCam::TRANSFORM_TRANSLATE_XY, OF_MOUSE_BUTTON_LEFT);
	cam.addInteraction(ofEasyCam::TRANSFORM_TRANSLATE_Z, OF_MOUSE_BUTTON_RIGHT);
	
	cam.enableOrtho();
	cam.setNearClip(-1000000);
	cam.setFarClip(1000000);
	cam.setVFlip(false);
}
//--------------------------------------------------------------
bool ofxIldaFile::loadDialog(){
	auto r = ofSystemLoadDialog("Select an .ild file");
	if(r.bSuccess){
		if( ofToLower(ofFilePath::getFileExt(r.getPath())) == "ild"){
			return load(r.getPath());
		}
	}
	return false;
}
//--------------------------------------------------------------
bool ofxIldaFile::load(const string& filepath){
	
	ofBuffer buffer = ofBufferFromFile(filepath);
	if(buffer.size() == 0) return false;

	reset();
	
	this->filepath = filepath;
	
	for (size_t i=0 ; i< buffer.size() ; ){
		ofxIldaFileFrame frame;
		if(frame.readFromBuffer(buffer, i)){
			frames.push_back(frame);
			
			i+=32 + frame.getDataSize();
		} else {
			i++;
		}
	}
	for(auto&f: frames){
		cout << "----------"<<endl;
		cout << f;
	}
	return frames.size() > 0;
}
//--------------------------------------------------------------
void ofxIldaFile::draw(const ofRectangle & viewport, bool bDrawBounds){
	if(currentFrame < frames.size()){
		cam.begin();
		ofScale(min(viewport.width, viewport.height)*0.5f);
		if(bDrawBounds){
		ofPushStyle();
		ofSetColor(255);
		ofNoFill();
		ofDrawRectangle(-1, -1, 2, 2);
		ofPopStyle();
		}
		frames[currentFrame].path.draw();
		cam.end();
		if( ofGetElapsedTimef() - lastFrameTime > frameduration){
			if(lastFrameTime != 0){
				(++ currentFrame) %= frames.size();
			}
			lastFrameTime = ofGetElapsedTimef();
		}
	}
}
//--------------------------------------------------------------
void ofxIldaFile::reset(){
	filepath = "";
	frames.clear();
	frameduration = 0;
	scanrate = 0;

	currentFrame = 0;
}
//--------------------------------------------------------------
const string& ofxIldaFile::getFilepath(){
	return filepath;
}
//--------------------------------------------------------------
vector<ofxIldaFileFrame>& ofxIldaFile::getFrames(){
	return frames;
}
//--------------------------------------------------------------
const vector<ofxIldaFileFrame>& ofxIldaFile::getFrames() const {
	return frames;
}
