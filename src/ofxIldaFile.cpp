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
ofxIldaFile::ofxIldaFile(const string& name, float frame_duration, int scan_rate):ofxIldaFile(){
	this->name = name;
	frameduration = frame_duration;
	scanrate = scan_rate;
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
	
	name = ofFilePath::getBaseName(filepath);
	
	for (size_t i=0 ; i< buffer.size() ; ){
		ofxIldaFileFrame frame;
		if(frame.readFromBuffer(buffer, i)){
			frames.push_back(frame);
			i+=32 + frame.getDataSize();
		} else {
			if (i >= (buffer.size() - 40) && frame.bFrameSet){
				cout << "----------"<<endl;
				if(frames.size()){
				cout <<frames.back().getAsString() << endl;
				}
				cout <<frame.getAsString() << endl;
			}
			i++;
		}
		cout << ofToString(frame.path.getVertices())<<endl;
	}
//	for(auto&f: frames){
//		cout << "----------"<<endl;
//		cout << f;
//	}
	return frames.size() > 0;
}
//--------------------------------------------------------------
bool ofxIldaFile::isLoaded(){
	return frames.size() > 0;
}
//--------------------------------------------------------------
void ofxIldaFile::save(const string& filepath){
	ofBuffer buffer;

	for (size_t i=0 ; i< frames.size() ; i++){
		frames[i].frame_number=i;
		frames[i].total_frame = frames.size();
		frames[i].writeToBuffer(buffer);
		

	}
	for(auto&f: frames){
		cout << "----------"<<endl;
		cout << f;
	}
	
	if(buffer.size() > 0 && frames.size() > 0) {
		
		ofxIldaFileFrame::getEndFrame(frames.back()).writeToBuffer(buffer);
		
		
		ofFilePath::createEnclosingDirectory(filepath);
		
		
		
		
		ofBufferToFile(filepath, buffer);
	}
}
//--------------------------------------------------------------
void ofxIldaFile::saveDialog(){
	auto r = ofSystemSaveDialog(name + ".ild", "Save to .ild file");
	if(r.bSuccess){
		string path = r.getPath();
		if( ofToLower(ofFilePath::getFileExt(r.getPath())) != "ild"){
			path = ofFilePath::getPathForDirectory(ofFilePath::getEnclosingDirectory(path));
			path += ofFilePath::getBaseName(path) + ".ild";
			ofLogWarning("ofxIldaFile::saveDialog") << "file extension must be .ild! Automatically changed into it";
		}
		save(path);
	}else{
		ofLogWarning("ofxIldaFile::saveDialog") << "save dialog canceled!";
	}
}
//--------------------------------------------------------------
void ofxIldaFile::draw(const ofRectangle & viewport, bool bDrawBounds){
	if(currentFrame < frames.size()){
		cam.begin();
		ofPushMatrix();
//		if(frames[currentFrame].isDataNormalized()){
			ofScale(min(viewport.width, viewport.height)*0.5f);
		
		//		}
		if(bDrawBounds){
			ofPushStyle();
			ofSetColor(255);
			ofNoFill();
			ofDrawRectangle(-1, -1, 2, 2);
			ofPopStyle();
		}
		
		frames[currentFrame].normalizedPath.draw(); // path.draw();
		
		ofPopMatrix();
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
	name = "";
	frameduration = 0;
	scanrate = 0;
	
	lastFrameTime = 0;
	currentFrame = 0;
	
	filepath = "";
	
	frames.clear();
	
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
//--------------------------------------------------------------
const string& ofxIldaFile::getName(){
	return name;
}
//--------------------------------------------------------------
float ofxIldaFile::getFrameDuration(){
	return frameduration;
}
//--------------------------------------------------------------
int ofxIldaFile::getScanRate(){
	return scanrate;
}
//--------------------------------------------------------------
string ofxIldaFile::getValidPath(const string& filepath){
	string dir =  ofFilePath::getPathForDirectory(ofFilePath::getEnclosingDirectory(filepath));
	string n = getValidName(ofFilePath::getBaseName(filepath));
	string fullpath = dir+ n + ".ild";
	
	for(size_t i =0; ofFile::doesFileExist(fullpath) && i < 1000000; i++ ){
		n = n.substr(0, 8 - (int)(floor(log10(i)) +1)) + ofToString(i);
		fullpath = dir+ n + ".ild";
	}
	return fullpath;
}
//--------------------------------------------------------------
string ofxIldaFile::getValidName(const string& _name){
	if(_name.size() >= 8)return _name;
	return _name.substr(0, 8);
}

//--------------------------------------------------------------
ofxIldaFileFrame& ofxIldaFile::addFrame(){
	frames.push_back(ofxIldaFileFrame());
	return frames.back();
}
//--------------------------------------------------------------
ofxIldaFileFrame& ofxIldaFile::addFrame(const ofxIldaFileFrame& f){
	frames.push_back(f);
	return frames.back();
}
//--------------------------------------------------------------
