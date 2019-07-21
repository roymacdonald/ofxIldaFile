#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ildaDir.loadDialog();
}

//--------------------------------------------------------------
void ofApp::update(){
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(60);
	ofSetColor(255);
	ildaDir.ildaFile.draw();
	
	stringstream ss;
	ss << "Press [ key ] for:\n";
	ss << " [ d ] : load directory with .ild files and browse these.\n";
	ss << endl;
	string path = ildaDir.ildaFile.getFilepath();
	ss << "Current file : " << ofFilePath::getFileName(path) << endl;
	
	ss << "Current folder : " << ofFilePath::getEnclosingDirectory(path) << endl;
	ss << "Current file index: " << ildaDir.getCurrentFileIndex() << endl;
	
	ofBitmapFont bf;
	auto bb = bf.getBoundingBox(ss.str(), 0, 0);
	ofDrawBitmapStringHighlight(ss.str(), 20, ofGetHeight() - 20 - bb.height, ofColor(40, 120), ofColor(255));
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if(key == 'd'){
		ildaDir.loadDialog();
	}else if(key == OF_KEY_DOWN){
		ildaDir.loadNextFile();
	}else if(key == OF_KEY_UP){
		ildaDir.loadPrevFile();
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
	
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
	
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
	
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
	
}
