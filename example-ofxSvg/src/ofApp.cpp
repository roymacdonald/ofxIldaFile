#include "ofApp.h"

glm::vec3 growToFill(const glm::vec3& p, const glm::vec3 & mn,const glm::vec3 & mx ){
	return {ofMap(p.x, mn.x, mx.x,  -32768, 32767), ofMap(p.y, mn.y, mx.y,  -32768, 32767), 0};
}
void printIfZero(const glm::vec3& v, const size_t& pathIndex, const size_t& vertexIndex, const size_t& vertSize){
	if(ofIsFloatEqual(v.x, 0.0f) &&
	   ofIsFloatEqual(v.y, 0.0f) &&
	   ofIsFloatEqual(v.z, 0.0f) ){
		cout << "point is zero. pathIndex: " << pathIndex << "  vertexIndex: " << vertexIndex << " vertSize: " << vertSize << endl;
	}
}
//--------------------------------------------------------------
void ofApp::loadSvg(){
	auto r = ofSystemLoadDialog();
	if(r.bSuccess){
		//		ofxSVG svg;
		svg.load(r.getPath());
		paths = svg.getPaths();
		auto file = ildaDir.addNewFile("SWISS", 2, 20);
		auto& frame =  file->addFrame({4, "suiz", "umwlt"});
//		const int& format, const string& frameName, const string& companyName, bool bNormalizedData
		
		ofRectangle bb;
		bool bFirst = true;
		for(size_t ind = 0; ind < paths.size(); ind++){
			auto& c = paths[ind].getCommands();
			
				for(size_t i = 0; i < c.size()-1; i++){
					if(bFirst && c[i].type != ofPath::Command::close ){
						bb.set(c[i].to, 0,0);
						bFirst = false;
					}else{
						bb.growToInclude(c[i].to);
					}
				}
			
		}
		auto mn = bb.getMin();
		auto mx = bb.getMax();
		cout << "svg min" << mn << endl;
		cout << "svg max" << mx << endl;
		closePoints.clear();
		openPoints.clear();
		for(size_t ind = 0; ind < paths.size(); ind++){
			auto& c = paths[ind].getCommands();
				bool bWasClose = false;
			if(c.size() > 0){
				openPoints.push_back(c[0].to);
				
				printIfZero(c[0].to, ind, 0, c.size());
				
				frame.addPoint(growToFill(c[0].to, mn, mx), {0,0,0,0}, false);
			}
			for(int i =0; i < c.size() -1; i++){
//				if(c[i].type == ofPath::Command::close ){
//					
//					if(i < 0){
//						closePoints.push_back(c[i-1].to);
//						printIfZero(c[i-1].to, ind, i-1, c.size());
//						frame.addPoint(growToFill(c[i-1].to, mn, mx), {0,0,0,0}, false);
//						bWasClose = true;
////						frame.addPoint(c[i-1].to, {0,0,0,0}, false);
//					}
//				}else{
//					cout << c[i].to << endl;
//					if(bWasClose){
//						frame.addPoint(growToFill(c[i].to, mn, mx), {0,0,0,0}, false);
//						printIfZero(c[i].to, ind, i, c.size());
//						openPoints.push_back(c[i].to);
//						bWasClose = false;
//					}
					frame.addPoint(growToFill(c[i].to, mn, mx), ofColor::white, false);
//					frame.addPoint(c[i].to, ofColor::white, false);
//				}
			}
			if(c.size() > 1){
				auto & last = c[c.size() - 2].to;
				frame.addPoint(growToFill(last, mn, mx), {0,0,0,0}, false);
				printIfZero(last, ind, c.size() -2, c.size());
				closePoints.push_back(last);
			}
		}
		ildaDir.saveDialog();
		
		for(auto&p :paths){
			p.setFilled(false);
			p.setStrokeWidth(1);
			p.setStrokeColor(ofColor(0));
		}
		
		
		
		
		if(paths.size()){
			polys = paths[0].getOutline();
		}
	}
}
string getPathCommandAsString(const ofPath::Command::Type & t){
	switch(t){
	case ofPath::Command::moveTo: return "moveTo";
	case ofPath::Command::lineTo: return "lineTo";
	case ofPath::Command::curveTo: return "curveTo";
	case ofPath::Command::bezierTo: return "bezierTo";
	case ofPath::Command::quadBezierTo: return "quadBezierTo";
	case ofPath::Command::arc: return "arc";
	case ofPath::Command::arcNegative: return "arcNegative";
	case ofPath::Command::close: return "close";
	}
	return "";
}

//--------------------------------------------------------------
void ofApp::setup(){
	
	cam.removeAllInteractions();
	cam.addInteraction(ofEasyCam::TRANSFORM_TRANSLATE_XY, OF_MOUSE_BUTTON_LEFT);
	cam.addInteraction(ofEasyCam::TRANSFORM_TRANSLATE_Z, OF_MOUSE_BUTTON_RIGHT);
	
	cam.enableOrtho();
	cam.setNearClip(-1000000);
	cam.setFarClip(1000000);
	cam.setVFlip(true);
	
	loadSvg();
}

//--------------------------------------------------------------
void ofApp::update(){
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	ofBackground(60);
	cam.begin();
	auto& c = paths[index].getCommands();
	if(!ofGetKeyPressed(' ')){
		svg.draw();
		ofSetColor(0);
		paths[index].draw();
	
		
		//	polys.draw();
		ofSetColor(0);
		if(polys.size()){
			if(vertIndex < polys[polyIndex].getVertices().size()){
				ofDrawCircle(polys[polyIndex].getVertices()[vertIndex], 10);
			}
		}
	ofSetColor(ofColor::magenta);
	
	if(c.size()){
		ofDrawCircle(c[vertIndex% c.size() ].to, 10);
	}
	}else{
		ildaDir.drawCurrentFile();
	}
	
	ofSetColor(ofColor::magenta);
	for(auto& o: openPoints){
		ofDrawCircle(o, 9);
	}
	
	ofSetColor(ofColor::limeGreen);
	for(auto& c: closePoints){
		ofDrawCircle(c, 5);
	}
	
	cam.end();
	stringstream ss;
	ss << "paths index: " << index << endl;
	ss << "polys index: " << polyIndex << endl;
	ss << "vert  index: " << vertIndex << endl;
	ss << endl;
	ss << "num paths: " << paths.size() << endl;
	ss << "num polys: " << polys.size() << endl;
//	ss << "num verts polys: ";
	
	ss << endl;
	ss << "opening Points Num: " << openPoints.size() <<endl;
	ss << "closing Points Num: " << closePoints.size() <<endl;
	
	if(c.size()){
		ss << "currentCommand type: " << getPathCommandAsString(c[vertIndex% c.size() ].type) << endl;
	}
	
	
	if(polyIndex < polys.size()){
		ss << polys[polyIndex].getVertices().size();
	}else{
		ss << "0";
	}
	ss << endl;
	
	ofDrawBitmapStringHighlight(ss.str(), 20,20);
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if(key == OF_KEY_DOWN){
		index = (++index) % paths.size();
		vertIndex = 0;
	}else if(key == OF_KEY_UP){
		if(index == 0){
			index = paths.size() - 1;
		}else{
			index -- ;
		}
		vertIndex = 0;
		polyIndex = 0;
	}else if(key == OF_KEY_LEFT){
		if(vertIndex == 0){
			if(polyIndex < polys.size()){
				vertIndex = polys[polyIndex].getVertices().size() - 1;
			}
		}else{
			vertIndex--;
		}
	}else if(key == OF_KEY_RIGHT){
		if(polys[polyIndex].getVertices().size() > 0){
			vertIndex = (++vertIndex) % polys[polyIndex].getVertices().size();
		}
	}else if(key == ','){
		if(polys.size()){
			if(polyIndex == 0){
				polyIndex = polys.size()-1;
			}else{
				polyIndex --;
			}
		}
	}else if(key == '.'){
		if(polys.size()){
			
			(++polyIndex) %= polys.size();
			
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
