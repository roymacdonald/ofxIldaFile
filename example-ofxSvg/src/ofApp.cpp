#include "ofApp.h"

//glm::vec3 growToFill(const glm::vec3& p, const glm::vec3 & mn,const glm::vec3 & mx, bool bDoYFlip ){
//	glm::vec3 v;
//	v.x = ofMap(p.x, mn.x, mx.x,  -32768, 32767);
//	v.y = p.y;
//	if(bDoYFlip){
//		v.y = mx.y - (v.y - mn.y);
//	}
//	v.y = ofMap(v.y, mn.y, mx.y,  -32768, 32767);
//	
//	v.z =0;
//	return v;
//}
//void printIfZero(const glm::vec3& v, const size_t& pathIndex, const size_t& vertexIndex, const size_t& vertSize){
//	if(ofIsFloatEqual(v.x, 0.0f) &&
//	   ofIsFloatEqual(v.y, 0.0f) &&
//	   ofIsFloatEqual(v.z, 0.0f) ){
//		cout << "point is zero. pathIndex: " << pathIndex << "  vertexIndex: " << vertexIndex << " vertSize: " << vertSize << endl;
//	}
////}
////--------------------------------------------------------------
//void ofApp::loadSvg(){
//	auto r = ofSystemLoadDialog();
//	if(r.bSuccess){
//		svg.load(r.getPath());
//		paths = svg.getPaths();
//		auto file = ildaDir.addNewFile("SWISS", 2, 20);
//		auto& frame =  file->addFrame({4, "suiz", "umwlt"});
//		
//		ofRectangle bb;
//		bool bFirst = true;
//		for(size_t ind = 0; ind < paths.size(); ind++){
//			auto& c = paths[ind].getCommands();
//			
//			for(size_t i = 0; i < c.size()-1; i++){
//				if(bFirst && c[i].type != ofPath::Command::close ){
//					bb.set(c[i].to, 0,0);
//					bFirst = false;
//				}else{
//					bb.growToInclude(c[i].to);
//				}
//			}
//			
//		}
//		auto mn = bb.getMin();
//		auto mx = bb.getMax();
//		//		cout << "svg min" << mn << endl;
//		//		cout << "svg max" << mx << endl;
//		closePoints.clear();
//		openPoints.clear();
//		for(size_t ind = 0; ind < paths.size(); ind++){
//			auto& c = paths[ind].getCommands();
//			bool bWasClose = false;
//			if(c.size() > 0){
//				openPoints.push_back(c[0].to);
//				
//				printIfZero(c[0].to, ind, 0, c.size());
//				
//				frame.addPoint(growToFill(c[0].to, mn, mx, true), {0,0,0,0}, false);
//			}
//			for(int i =0; i < c.size() -1; i++){
//				frame.addPoint(growToFill(c[i].to, mn, mx, true), ofColor::white, false);
//			}
//			if(c.size() > 1){
//				auto & last = c[c.size() - 2].to;
//				frame.addPoint(growToFill(last, mn, mx, true), {0,0,0,0}, false);
//				printIfZero(last, ind, c.size() -2, c.size());
//				closePoints.push_back(last);
//			}
//		}
//		ildaDir.saveDialog();
//		
//		for(auto&p :paths){
//			p.setFilled(false);
//			p.setStrokeWidth(1);
//			p.setStrokeColor(ofColor(0));
//		}
//		
//		
//		
//		
//		if(paths.size()){
//			polys = paths[0].getOutline();
//		}
//	}
//}
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
	
	file.setup("ILDAFILE", 2, 20);
	auto r =ofSystemLoadDialog("Select SVG file...", false, "", {"svg", "SVG"});
	if(r.bSuccess){
		auto frame =  file.newFrameFromSVG(r.getPath(),
										   // define the format in which you want to have the ilda frame.
										   // look in ofxIldaFileConstants.h file for other options
										   ofxIlda::FILE_FORMAT_3D_INDEXED_COLOR,
//										   ofxIlda::FILE_FORMAT_3D_TRUE_COLOR,
										   // if true it will scale everything so it fills the drawable area.
										   true);
	}


	gui.setup("ILDA SETTINGS", "ILDA_FILE_SETTINGS.xml");
	gui.add(*file.getFrameSettings());
	
	gui.loadFromFile("ILDA_FILE_SETTINGS.xml");
	
	file.getFrameSettings()->output.blankCount = 0;
	
	
	
	
//	file.saveDialog();
}

//--------------------------------------------------------------
void ofApp::update(){
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	ofBackground(60);
//	cam.begin();
	file.draw();
	
	
	auto currentFrame = file.getCurrentFrame();
	
	stringstream ss;
	
	if(currentFrame){
		
		auto& v = currentFrame->normalizedPath.getVertices();
		auto& c = currentFrame->normalizedPath.getColors();
		
		auto & cam = file.getCamera();
		auto dc = cam.screenToWorld({1,1,0}) - cam.screenToWorld({0,0,0});
		float d = dc.x/(min(ofGetWidth(), ofGetHeight())*0.5f);
		
		
		cam.begin();
		ofPushMatrix();
		//		if(frames[currentFrame].isDataNormalized()){
		ofScale(min(ofGetWidth(), ofGetHeight())*0.5f);
		
//		for(size_t i = 0; i < v.size();i++){
//			ofSetColor(c[i]);
//			ofDrawCircle(v[i], d*3);
//		}
//		
//
		
		
//		
//		for(auto & p: file.ildaFrame.getProcessedPolys()){
//			auto & v = p.getVertices();
//			if(v.size()){
//				ofSetColor(ofColor::yellow);
//				ofDrawRectangle(v[0], -d*4, -d*4);
//				if(v.size() > 1){
//					ofSetColor(ofColor::red);
//					ofDrawRectangle(v.back(), d*4, d*4);
//				}
//			}
//		}
//		
//		
//		
		
		
		
//		for(auto & p: file.svgPaths){
//			auto & o = p.getOutline();
//			if(o.size()){
//				auto& v = o[0].getVertices();
//				if(v.size()){
//					ofSetColor(ofColor::yellow);
//					ss << v[0] << endl;
//					ofDrawCircle(v[0], d*4);
//					if(v.size() > 1){
//						ofSetColor(ofColor::red);
//						ofDrawCircle(v.back(), d*6);
//						ss << v.back() << endl;
//					}
////					ofDrawRectangle(v[0], -d*4, -d*4);
//				}else{
//					ss << "no vertices in outlines "<<endl;
//				}
//			}else{
//				ss << "no outlines in svgpath"<<endl;
//			}
//			//					   svgPaths[i-1].getOutline().back().getVertices().back());
//		}
		
//		ofSetColor(ofColor::magenta);
//		for(size_t i = 0; i < file.svgPaths.size(); i++){
//			
//			ofDrawRectangle(file.svgPaths[i].getOutline().back().getVertices().back(), d*4, d*4);
//			//					   svgPaths[i-1].getOutline().back().getVertices().back());
//		}

		
		ofPopMatrix();
		cam.end();
		
	}else{
	
		ofDrawBitmapString("Current Frame is null", 20, 20);
	}
	
	
	
	
	
	
	
	gui.draw();
	
//	auto& c = paths[index].getCommands();
//	if(!ofGetKeyPressed(' ')){
//		svg.draw();
//		ofSetColor(0);
//		paths[index].draw();
		
		
//			polys.draw();
//		ofSetColor(0);
//		if(polys.size()){
//			if(vertIndex < polys[polyIndex].getVertices().size()){
//				ofDrawCircle(polys[polyIndex].getVertices()[vertIndex], 10);
//			}
//		}
//		ofSetColor(ofColor::black);
//		
//		for(auto& cc: c){
//			ofDrawCircle(cc.to, 5);
//		}
		//	if(c.size()){
		//		ofDrawCircle(c[vertIndex% c.size() ].to, 10);
		//	}
		
		
		
//	}else{
//		ildaDir.drawCurrentFile();
//	}
//	
//	ofSetColor(ofColor::magenta);
//	for(auto& o: openPoints){
//		ofDrawCircle(o, 9);
//	}
//	
//	ofSetColor(ofColor::limeGreen);
//	for(auto& c: closePoints){
//		ofDrawCircle(c, 5);
//	}
	
//	cam.end();
	
	
	
	
//	stringstream ss;
//	ss << file.ildaFrame.getString();
//	ss << "paths index: " << index << endl;
//	ss << "polys index: " << polyIndex << endl;
//	ss << "vert  index: " << vertIndex << endl;
//	ss << endl;
//	ss << "num paths: " << paths.size() << endl;
//	ss << "num polys: " << polys.size() << endl;
	//	ss << "num verts polys: ";
	
//	ss << endl;
//	ss << "opening Points Num: " << openPoints.size() <<endl;
//	ss << "closing Points Num: " << closePoints.size() <<endl;
//	
//	if(c.size()){
//		ss << "currentCommand type: " << getPathCommandAsString(c[vertIndex% c.size() ].type) << endl;
//	}
	
	
//	if(polyIndex < polys.size()){
//		ss << polys[polyIndex].getVertices().size();
//	}else{
//		ss << "0";
//	}
//	ss << endl;
	
	ofBitmapFont bf;
	
	auto r = bf.getBoundingBox(ss.str(), 0, 0);
	
	
	ofDrawBitmapStringHighlight(ss.str(), 20,ofGetHeight() - r.height - 20);
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
//	if(key == OF_KEY_DOWN){
//		index = (++index) % paths.size();
//		vertIndex = 0;
//	}else if(key == OF_KEY_UP){
//		if(index == 0){
//			index = paths.size() - 1;
//		}else{
//			index -- ;
//		}
//		vertIndex = 0;
//		polyIndex = 0;
//	}else if(key == OF_KEY_LEFT){
//		if(vertIndex == 0){
//			if(polyIndex < polys.size()){
//				vertIndex = polys[polyIndex].getVertices().size() - 1;
//			}
//		}else{
//			vertIndex--;
//		}
//	}else if(key == OF_KEY_RIGHT){
//		if(polys[polyIndex].getVertices().size() > 0){
//			vertIndex = (++vertIndex) % polys[polyIndex].getVertices().size();
//		}
//	}else if(key == ','){
//		if(polys.size()){
//			if(polyIndex == 0){
//				polyIndex = polys.size()-1;
//			}else{
//				polyIndex --;
//			}
//		}
//	}else if(key == '.'){
//		if(polys.size()){
//			
//			(++polyIndex) %= polys.size();
//			
//		}
//	}

	if(key == 's'){
		auto r = ofSystemSaveDialog("ILDAFILE.ild", "");
		if(r.bSuccess){
			string folder = ofFilePath::getPathForDirectory(ofFilePath::getEnclosingDirectory(r.getPath()));
			int scanRate = 15;
			float frameDuration = 1;
			
			ofBuffer prgBuffer;
			for(int i = 0; i < 40; i+=5){
				for(int j = 0; j < 40; j+=5){
					file.getFrameSettings()->output.blankCount = i;
					file.getFrameSettings()->output.endCount = j;
					auto filepath = file.save(folder + "LO"+ofToString(i,2)+"GO"+ofToString(j,2)+".ild");
					
					string prg = ofFilePath::getFileName(filepath)+ "," + ofToString(scanRate)+ "," + ofToString(frameDuration, 1) + "\n";
					prgBuffer.append(prg);				
				}
			}
			string bufferPath = folder + ofFilePath::getBaseName(ofFilePath::removeTrailingSlash(folder))+".prg";
			cout << ofFilePath::getBaseName(bufferPath) << endl;
			cout << bufferPath << endl;
			ofBufferToFile( bufferPath, prgBuffer, false);


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
