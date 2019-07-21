#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::openIldaDir(){
	auto r = ofSystemLoadDialog("Select a folder that contains .ild files", true);
	if(r.bSuccess){
		dir.close();
		dir.allowExt("ild");
		dir.listDir(r.getPath());
		fileIndex = 0;
		currentFolder = "";
		if(dir.size()){
			currentFolder = r.getPath();
			ildaFile.load(dir.getPath(0));
		}
	}
}
//--------------------------------------------------------------
void ofApp::openIldaFile(){
	auto r = ofSystemLoadDialog("Select an .ild file");
	if(r.bSuccess){
		dir.close();
		fileIndex = 0;
		currentFolder = "";
		if( ofToLower(ofFilePath::getFileExt(r.getPath())) == "ild"){
			ildaFile.load(r.getPath());
		}
	}
}
//--------------------------------------------------------------
void ofApp::setup(){
	
	openIldaDir();
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
	ss << " [ d ] : load directory with .ild files and browse these.\n";
	ss << " [ d ] : load a single .ild file.\n";
	ss << endl;
	ss << "Current file : " << currentFileName << endl;
	if(!currentFolder.empty()){
		ss << "Current folder : " << currentFolder << endl;
		ss << "Current file index: " << fileIndex << endl;
	}
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
		openIldaFile();
	}else if(key == 'd'){
		openIldaDir();
	}
	
	if(dir.size()){
	if(key == OF_KEY_DOWN){
		(++fileIndex) %= dir.size();
		ildaFile.load(dir.getPath(fileIndex));
	}else if(key == OF_KEY_UP){
			if(fileIndex == 0){
				fileIndex = dir.size() - 1;
			}else{
				fileIndex -- ;
			}
			
			ildaFile.load(dir.getPath(fileIndex));
		}
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
