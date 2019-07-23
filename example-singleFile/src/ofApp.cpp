#include "ofApp.h"
//--------------------------------------------------------------
void ofApp::setup(){
	ildaFile.loadDialog();
}

//--------------------------------------------------------------
void ofApp::update(){
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(60);
	ofSetColor(255);
	ildaFile.draw();
	
	stringstream ss;
	ss << "Press [ key ] for:\n";
	ss << " [ l ] : load a single .ild file.\n";
	ss << " [ s ] : save a single .ild file.\n";
	ss << endl;
	ss << "Current file : " << ildaFile.getFilepath() << endl;
	
	ofBitmapFont bf;
	auto bb = bf.getBoundingBox(ss.str(), 0, 0);
	ofDrawBitmapStringHighlight(ss.str(), 20, ofGetHeight() - 20 - bb.height, ofColor(40, 120), ofColor(255));
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if(key == 'l'){
		ildaFile.loadDialog();
	}else if(key == 's'){
		ildaFile.saveDialog();
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
