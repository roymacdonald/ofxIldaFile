#include "ofApp.h"
//--------------------------------------------------------------
void ofApp::setup(){
	ildaFile.loadDialog();
	ildaFile.setPaused(true);
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
	ss << "Press [ key ] to:\n";
	ss << " [ l ] : load a single .ild file.\n";
	ss << " [ s ] : save a single .ild file.\n";
	ss << endl;
	ss << "Current file : " << ildaFile.getFilepath() << endl;
	
	
	auto currentFrame = ildaFile.getCurrentFrame();
	if(currentFrame){
		
		auto& v = currentFrame->normalizedPath.getVertices();
		auto& c = currentFrame->normalizedPath.getColors();
		
		auto & cam = ildaFile.getCamera();
		auto dc = cam.screenToWorld({1,1,0}) - cam.screenToWorld({0,0,0});
		float d = dc.x/(min(ofGetWidth(), ofGetHeight())*0.5f);
		
		
		cam.begin();
		ofPushMatrix();
		//		if(frames[currentFrame].isDataNormalized()){
		ofScale(min(ofGetWidth(), ofGetHeight())*0.5f);
		
		for(size_t i = 0; i < v.size();i++){
			ofSetColor(c[i]);
			ofDrawCircle(v[i], d*3);
		}
		
		ss << "vertIndex : " << vertIndex <<endl;
		if(v.size() > 0){
		
			ofPushStyle();
			//			ofSetColor(c[vertIndex]);
			
			ofSetColor(0);
			//			ofNoFill();
			//			ofSetLineWidth(2);
			ofDrawCircle(v[vertIndex], d*4);
			
			ofPopStyle();
			ss << "vert Pos : " << v[vertIndex] <<endl;
			ss << "vert Col : " << c[vertIndex] <<endl;
		}
		
		ofPopMatrix();
		cam.end();
		
	}
	
	
	if(svgPathIndex < ildaFile.svgPaths.size()){
		ildaFile.svgPaths[svgPathIndex].draw();
	}
	
	//	ofSetColor(255);
	//	for(auto& e: currentFrame->endsMap){
	//		ofDrawBitmapString(ofToString(e.second),v[e.first] );
	//	}
	//	ofSetColor(0);
	//	for(auto& r:currentFrame->repVMap){
	//
	//		ofSetColor(c[r.first]);
	//		ofDrawCircle(v[r.first], d*12);
	//		ofSetColor(0);
	//		ofDrawBitmapString(ofToString(r.second),v[r.first] );
	//	}
	//
	//
	//
	
	
	


	
	if(currentFrame){
		ss << *currentFrame;
	}
	
	ofBitmapFont bf;
	auto bb = bf.getBoundingBox(ss.str(), 0, 0);
	ofDrawBitmapStringHighlight(ss.str(), 20, ofGetHeight() - 20 - bb.height, ofColor(40, 120), ofColor(255));
	
	
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	auto currentFrame = ildaFile.getCurrentFrame();
	if(currentFrame){

	int step = ofGetKeyPressed(OF_KEY_SHIFT)?10:1;

	if(key == OF_KEY_LEFT){
		ofxIlda::decrementAndWrap(vertIndex,currentFrame->normalizedPath.getVertices().size(), step);
//		if(vertIndex == 0){
//				vertIndex = currentFrame->normalizedPath.getVertices().size() - 1;
//			}else{
//				vertIndex-= inc;
//			}
	}else if(key == OF_KEY_RIGHT){
		ofxIlda::incrementAndWrap(vertIndex,currentFrame->normalizedPath.getVertices().size(), step);
//			if(currentFrame->normalizedPath.getVertices().size() > 0){
//				vertIndex = (vertIndex + inc) % currentFrame->normalizedPath.getVertices().size();
//			}
	}else if(key == OF_KEY_DOWN){
			ofxIlda::incrementAndWrap(svgPathIndex,ildaFile.svgPaths.size(), step);
			printCurrentSvgPath();
//			svgPathIndex = (svgPathIndex) % paths.size();
//			vertIndex = 0;
		}else if(key == OF_KEY_UP){
			ofxIlda::decrementAndWrap(svgPathIndex,ildaFile.svgPaths.size(), step);
			printCurrentSvgPath();
		}
	}
	
}
//--------------------------------------------------------------
void ofApp::printCurrentSvgPath(){
	auto& p = ildaFile.svgPaths;
	
	if(svgPathIndex < p.size()){
//		cout << p[svgPathIndex] << endl;
	}
}
//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if(key == 'l'){
		ildaFile.loadDialog();
	}else if(key == 'L'){
		auto r =ofSystemLoadDialog("Select SVG file...", false, "", {"svg", "SVG"});
		if(r.bSuccess){
			ildaFile.reset();
			auto frame =  ildaFile.newFrameFromSVG(r.getPath(),
												   // define the format in which you want to have the ilda frame.
												   // look in ofxIldaFileConstants.h file for other options
												   ofxIlda::FILE_FORMAT_3D_INDEXED_COLOR,
												   // if true it will scale everything so it fills the drawable area.
												   true);
		}
	}else if(key == 's'){
		ildaFile.saveDialog();
	}else if(key == '.'){
		ildaFile.setPaused(true);
		ildaFile.nextFrame();
	}else if(key == ','){
		ildaFile.setPaused(true);
		ildaFile.prevFrame();
	}else if(key == ' '){
		ildaFile.setPaused(!ildaFile.isPaused());
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
