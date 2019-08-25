#include "ofxIldaFile.h"
#include "ofxSvg.h"


//--------------------------------------------------------------
ofxIlda::File::File(){
	cam.removeAllInteractions();
	cam.addInteraction(ofEasyCam::TRANSFORM_TRANSLATE_XY, OF_MOUSE_BUTTON_LEFT);
	cam.addInteraction(ofEasyCam::TRANSFORM_TRANSLATE_Z, OF_MOUSE_BUTTON_RIGHT);
	
	cam.enableOrtho();
	cam.setNearClip(-1000000);
	cam.setFarClip(1000000);
	cam.setVFlip(false);
	
//	ildaFrame.setup();
}
ofxIlda::File::File(const string& name, float frame_duration, int scan_rate):ofxIlda::File(){
	setup(name, frame_duration, scan_rate);
}
//--------------------------------------------------------------
void ofxIlda::File::setup(const string& name, float frame_duration, int scan_rate){
	this->name = name;
	frameduration = frame_duration;
	scanrate = scan_rate;
}
//--------------------------------------------------------------
bool ofxIlda::File::loadDialog(){
	auto r = ofSystemLoadDialog("Select an .ild file");
	if(r.bSuccess){
		return load(r.getPath());
	}
	return false;
}
//--------------------------------------------------------------
bool ofxIlda::File::load(const string& filepath){
	if( ofToLower(ofFilePath::getFileExt(filepath)) != "ild"){
		ofLogError("ofxIlda::File::load") << "Not a .ild file. Not loading";
		return false;
	}
	ofBuffer buffer = ofBufferFromFile(filepath);
	if(buffer.size() == 0) return false;

	reset();
	
	this->filepath = filepath;
	
	name = ofFilePath::getBaseName(filepath);
	
	for (size_t i=0 ; i< buffer.size() ; ){
		shared_ptr<ofxIlda::FileFrame> frame = make_shared<ofxIlda::FileFrame>();
		if(frame->readFromBuffer(buffer, i)){
			frames.push_back(frame);
			i+=32 + frame->getDataSize();
		} else {
			if (i >= (buffer.size() - 40) && frame->bFrameSet){
//				cout << "----------"<<endl;
//				if(frames.size()){
//				cout <<frames.back()->getAsString() << endl;
//				}
//				cout <<frame.getAsString() << endl;
			}
			i++;
		}
//		cout << ofToString(frame->path.getVertices())<<endl;
	}
//	for(auto&f: frames){
//		cout << "----------"<<endl;
//		cout << f;
//	}
	return frames.size() > 0;
}
//--------------------------------------------------------------
bool ofxIlda::File::isLoaded(){
	return frames.size() > 0;
}

//--------------------------------------------------------------
string ofxIlda::File::save(string filepath){
	ofBuffer buffer;

	for (size_t i=0 ; i< frames.size() ; i++){
		frames[i]->frame_number=i;
		frames[i]->total_frame = frames.size();
		frames[i]->writeToBuffer(buffer);
	}
//	for(auto&f: frames){
//		cout << "----------"<<endl;
//		cout << f;
//	}
	
	if(buffer.size() > 0 && frames.size() > 0) {
//		string path = filepath;
		filepath = getValidPath(filepath);
//		if( ofToLower(ofFilePath::getFileExt(filepath)) != "ild"){
//			filepath = ofFilePath::getPathForDirectory(ofFilePath::getEnclosingDirectory(filepath));
//			filepath += ofFilePath::getBaseName(filepath) + ".ild";
//			ofLogWarning("ofxIlda::File::save") << "file extension must be .ild! Automatically changed into it";
//		}
		
		ofxIlda::FileFrame::getEndFrame(*frames.back()).writeToBuffer(buffer);
		
		ofFilePath::createEnclosingDirectory(filepath);
		
		ofBufferToFile(filepath, buffer);
		return filepath;
	}else{
		ofLogWarning("ofxIlda::File::save") << "No data of file. Not writting";
	}
	return "";
}
//--------------------------------------------------------------
void ofxIlda::File::saveDialog(){
	auto r = ofSystemSaveDialog(name + ".ild", "Save to .ild file");
	if(r.bSuccess){
		save(r.getPath());
	}else{
		ofLogWarning("ofxIlda::File::saveDialog") << "save dialog canceled!";
	}
}

//--------------------------------------------------------------
void ofxIlda::File::draw(const ofRectangle & viewport, bool bDrawBounds){
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
		
		frames[currentFrame]->normalizedPath.draw();
		
		

		
//		ofSetColor(0);
//		for(size_t i = 1; i < svgPaths.size(); i++){
//			ofDrawLine(svgPaths[i].getOutline().front().getVertices().front(),
//					   svgPaths[i-1].getOutline().back().getVertices().back());
//		}

		
		
		
		
		
		auto& v = frames[currentFrame]->normalizedPath.getVertices();
		auto& c = frames[currentFrame]->normalizedPath.getColors();
		
		auto dc = cam.screenToWorld({1,1,0}) - cam.screenToWorld({0,0,0});
		float d = dc.x/(min(viewport.width, viewport.height)*0.5f);
		ofPushStyle();
		for(size_t i = 0; i < v.size();i++){
			if(ofIsFloatEqual(c[i].a, 0.0f)){
				ofSetColor(0);
				ofNoFill();
			}else{
				ofSetColor(c[i]);
				ofFill();
			}
			
			ofDrawCircle(v[i], d*2);
		}
		ofPopStyle();
		
		ofPushStyle();
		ofSetColor(ofColor::red);
		ofFill();
		for(auto & p: transformedSplitPoints){
			ofDrawCircle(p, d*3);
		}
		ofPopStyle();
		
		
//		ofSetColor(255);
//		for(auto& e:frames[currentFrame]->endsMap){
//			ofDrawBitmapString(ofToString(e.second),v[e.first] );
//		}
//		ofSetColor(0);
//		for(auto& r:frames[currentFrame]->repVMap){
//			
//			ofSetColor(c[r.first]);
//			ofDrawCircle(v[r.first], d*12);
//			ofSetColor(0);
//			ofDrawBitmapString(ofToString(r.second),v[r.first] );
//		}
		
		
		
//		frames[currentFrame]->path.draw();
		
		
//		auto& v = frames[currentFrame]->normalizedPath.getVertices();
//		auto& c = frames[currentFrame]->normalizedPath.getColors();
		
//		size_t accum = 0;
//		glm::vec3 lastV;
//		for(size_t i =0; i < v.size(); i++){
//			if(ofIsFloatEqual(c[i].a, 0.0f)){
//				accum++;
//				lastV = v[i];
//			}else{
//				accum =0;
//				ofDrawBitmapStringHighlight(ofToString(accum), lastV);
//			}
//		
		//		}
		
		ofPopMatrix();
		cam.end();
		if(!bPaused){
			if( ofGetElapsedTimef() - lastFrameTime > frameduration){
				if(lastFrameTime != 0){
					(++ currentFrame) %= frames.size();
				}
				lastFrameTime = ofGetElapsedTimef();
			}
		}
	}
}
//--------------------------------------------------------------
void ofxIlda::File::reset(){
	name = "";
	frameduration = 0;
	scanrate = 0;
	
	lastFrameTime = 0;
	currentFrame = 0;
	
	filepath = "";
	
	frames.clear();
	
}
//--------------------------------------------------------------
const string& ofxIlda::File::getFilepath(){
	return filepath;
}
//--------------------------------------------------------------
vector<shared_ptr<ofxIlda::FileFrame>>& ofxIlda::File::getFrames(){
	return frames;
}
//--------------------------------------------------------------
const vector<shared_ptr<ofxIlda::FileFrame>>& ofxIlda::File::getFrames() const {
	return frames;
}
//--------------------------------------------------------------
const string& ofxIlda::File::getName(){
	return name;
}
//--------------------------------------------------------------
float ofxIlda::File::getFrameDuration(){
	return frameduration;
}
//--------------------------------------------------------------
int ofxIlda::File::getScanRate(){
	return scanrate;
}
//--------------------------------------------------------------
void ofxIlda::File::setFrameDuration(float frameDuration){
	frameduration = frameDuration;
}
//--------------------------------------------------------------
void ofxIlda::File::setScanRate(int scanRate){
	scanrate = scanRate;
}
//--------------------------------------------------------------
string ofxIlda::File::getValidPath(const string& filepath){
	string dir =  ofFilePath::getPathForDirectory(ofFilePath::getEnclosingDirectory(filepath));
	string n = getValidName(ofFilePath::getBaseName(filepath));
	string fullpath = dir+ n + ".ild";
	
	for(size_t i =0; ofFile::doesFileExist(fullpath) && i < 1000000; i++ ){
		int numDigits = 1;//(int)(floor(log10(i)) +1);
		if(i > 0) numDigits += (int)(floor(log10(i)));
//		cout << "numDigits: " << numDigits << "  " << i <<endl;
		n = n.substr(0, 8 - numDigits) + ofToString(i);
		fullpath = dir+ n + ".ild";
	}
	return fullpath;
}
//--------------------------------------------------------------
string ofxIlda::File::getValidName(const string& _name){
	if(_name.size() >= 8)return _name;
	return _name.substr(0, 8);
}

//--------------------------------------------------------------
shared_ptr<ofxIlda::FileFrame> ofxIlda::File::addFrame(){
	frames.push_back(make_shared<ofxIlda::FileFrame>());
	return frames.back();
}
//--------------------------------------------------------------
shared_ptr<ofxIlda::FileFrame> ofxIlda::File::addFrame(const ofxIlda::FileFrame& f){
	frames.push_back(make_shared<ofxIlda::FileFrame>(f));
	return frames.back();
}
//--------------------------------------------------------------
shared_ptr<ofxIlda::FileFrame> ofxIlda::File::addFrame(shared_ptr<ofxIlda::FileFrame> f){
	frames.push_back(f);
	return frames.back();
}
//--------------------------------------------------------------
shared_ptr<ofxIlda::FileFrame> ofxIlda::File::getCurrentFrame(){
	if(currentFrame < frames.size()){
		return frames[currentFrame];
	}
	return nullptr;
}
//--------------------------------------------------------------
size_t ofxIlda::File::getCurrentFrameIndex(){
	return currentFrame;
}
//--------------------------------------------------------------
glm::vec3 growToFill(const glm::vec3& p, const glm::vec3 & from_min,const glm::vec3 & from_max,const glm::vec3 & to_min,const glm::vec3 & to_max, bool bDoYFlip ){
	glm::vec3 v;
	v.x = ofMap(p.x, from_min.x, from_max.x, to_min.x, to_max.x);
	v.y = p.y;
	if(bDoYFlip){
		v.y = from_max.y - (v.y - from_min.y);
	}
	v.y = ofMap(v.y, from_min.y, from_max.y, to_min.y, to_max.y);
	v.z =0;
	return v;
}
//--------------------------------------------------------------
void ofxIlda::File::setPaused(bool paused){
	bPaused = paused;
}
//--------------------------------------------------------------
bool ofxIlda::File::isPaused(){
	return bPaused;
}
//--------------------------------------------------------------
void ofxIlda::File::updateFromIldaFrame(){
//	cout << "ofxIlda::File::updateFromIldaFrame" << endl;
	if(frames.size()){
		ildaFrame->update();
		
		//check if the polyline optimization removed relevant vertices of the ofPath, so to be able to have sharp corners
		
		
		auto& points = ildaFrame->getPoints();
		frames.back()->resetPaths();
		for(auto & p : points){
			frames.back()->addPoint({p.x, p.y, 0}, ofColor(p.r, p.g, p.b, p.a), false);
		}
		
		transformedSplitPoints = splitPoints;
		for(auto& p: transformedSplitPoints){
//			ofxIlda::normalizePoint(p);
			p = ildaFrame->transformPoint(p);
		}
		
	}

}
//--------------------------------------------------------------
shared_ptr<ofxIlda::FrameSettings> ofxIlda::File::getFrameSettings(){
	if(frameSettings == nullptr) frameSettings = make_shared<FrameSettings>();
	return frameSettings;
}
//--------------------------------------------------------------
shared_ptr<ofxIlda::Frame> ofxIlda::File::getIldaFrame(){
	if(ildaFrame == nullptr){
		ildaFrame = make_shared<ofxIlda::Frame>(getFrameSettings());
		ildaFrame->setup();
	}
	return ildaFrame;
}
//--------------------------------------------------------------
shared_ptr<ofxIlda::FileFrame> ofxIlda::File::newFrameFromSVG(const string& filepath, ofxIlda::FileFormat format, bool bScaleToFill, const string& framename, const string& companyname ){
	if(ofToLower(ofFilePath::getFileExt(filepath)) != "svg"){
		ofLogWarning("ofxIlda::File::newFrameFromSVG") << "could not load. Not an svg file.";
		return nullptr;
	}
	ofxSVG svg;
	svg.load(filepath);
	svgPaths = svg.getPaths();
	if(svgPaths.size() == 0){
		ofLogWarning("ofxIlda::File::newFrameFromSVG") << "loaded svg file has no paths";
		return nullptr;
	}
//	auto file = ildaDir.addNewFile("SWISS", 2, 20);
	auto frame =  addFrame({format, framename, companyname});
	
#ifdef USE_OFX_ILDA
	

	ofRectangle bb = getBoundingBox(svgPaths);

	bb.scaleFromCenter(1.25);
	auto from_min = bb.getMin();
	auto from_max = bb.getMax();
		
	
	
	glm::vec3 to_min = { 0, 0,0};
	glm::vec3 to_max = { 1, 1,0};
	
	
	
	getIldaFrame()->clear();
//	svgPathsToPolyIndices.clear();
	
//	for(auto& p: svgPaths){
//	svgPathsStart.clear();
//	svgPathsEnd.clear();
	//		moveTo,
	//		lineTo,
	//		curveTo,
	//		bezierTo,
	//		quadBezierTo,
	//		arc,
	//		arcNegative,
	//		close
	
	
	auto getVerticesFromPath = [&](ofPath& path, const ofFloatColor& color ){
		if(path.getCommands().size()){
			auto ol =path.getOutline();
			for(auto& o: ol){
				auto& v = o.getVertices();
				for(size_t j = 0; j < v.size(); j++){
					v[j] = growToFill(v[j], from_min, from_max, to_min, to_max, true);
				}
				ildaFrame->addPoly(o, color);//svgPaths[i].getStrokeColor());
			}
			path.clear();
		}
	};
	
	
	
//#define SPLIT_VERTS
#ifdef SPLIT_VERTS
	vector<ofPath> splitPaths;
	
	enum SegmentType{
		SEGMENT_NONE,
		SEGMENT_LINES,
		SEGMENT_CURVE
	};
	
	splitPoints.clear();
	
	for(size_t i = 0; i < svgPaths.size();i++){
		auto& c = svgPaths[i].getCommands();
		auto currentSegmentType = SEGMENT_NONE;
		auto prevSegmentType = SEGMENT_NONE;
		
		for(size_t i = 0; i < c.size()-1; i++){
			if(c[i].type == ofPath::Command::lineTo ||
			   c[i].type == ofPath::Command::moveTo){

				currentSegmentType = SEGMENT_LINES;
				
			}else if(c[i].type == ofPath::Command::close){
				currentSegmentType = SEGMENT_NONE;
			}else{
				currentSegmentType = SEGMENT_CURVE;
			}
			
			if(currentSegmentType != prevSegmentType){
//				if(currentSegmentType != SEGMENT_NONE){
					splitPaths.push_back(ofPath());
					splitPaths.back().moveTo(c[i-1].to);
					splitPoints.push_back(growToFill(c[i-1].to, from_min, from_max, to_min, to_max, true));
//				}else{
			
//				}
			}
			
			prevSegmentType = currentSegmentType;
//			if(currentSegmentType != SEGMENT_NONE){
				splitPaths.back().addCommand(c[i]);
//			}
			//				path.addCommand(c[i]);
		}
	}
	svgPaths  = splitPaths;
	
#endif
	for(size_t i = 0; i < svgPaths.size();i++){
		auto ol = svgPaths[i].getOutline();
		
		for(auto& o: ol){
//			cout << "closed poly: " << boolalpha << o.isClosed() << endl;
			
			auto& v = o.getVertices();
			for(size_t j = 0; j < v.size(); j++){
				v[j] = growToFill(v[j], from_min, from_max, to_min, to_max, true);
//				if(j == 0){
////					svgPathsStart.push_back(v[j]);
//					
//				}
//				if(j == v.size() - 1) {
////					svgPathsEnd.push_back(v[j]);
//					
//				}
			}
			
 			ildaFrame->addPoly(o, svgPaths[i].getStrokeColor());
//			svgPathsToPolyIndices.push_back(i);
//			cout << "strokeColor: " << p.getStrokeColor() << "  fill color: " << p.getFillColor() <<endl;
		}
	}

	
	
	
	ildaFrameParamListener = getFrameSettings()->parameterChangedE().newListener([&](ofAbstractParameter&){
		updateFromIldaFrame();
	});
	
	updateFromIldaFrame();
	
	cout << "frame-> path:           " << getBoundingBox(frame->path) << endl;
	cout << "frame-> normalized path:" << getBoundingBox(frame->normalizedPath) << endl;
	//cout << "bb2 " << bb2 << endl;
	
//		frame->normalizedPath.clear();
//		frame->normalizedPath = frame->path;
//		for(auto& v: frame->normalizedPath.getVertices()){
//			ofxIlda::FileFrame::normalizePoint(v);
//		}
	
		cout << "frame from min " << from_min << endl;
		cout << "frame from max " << from_max << endl;
		cout << "frame to min " << to_min << endl;
		cout << "frame to max " << to_max << endl;
//	}
	
	
#else
//	if(bScaleToFill){
//		bool bFirst = true;
//		
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
//		}
//	}
//	auto mn = bb.getMin();
//	auto mx = bb.getMax();
	//		cout << "svg min" << mn << endl;
	//		cout << "svg max" << mx << endl;
	int startCount = 5;
	int endCount = 5;
	
	cout << "paths.size " << paths.size() << endl;
	for(size_t ind = 0; ind < paths.size(); ind++){

		auto& o = paths[ind].getOutline();
		for(auto& c: o){
			if(c.size() > 0){
				frame->addPoint(c[0], {0,0,0,0}, false);
//			}
				for(int i =0; i < startCount ; i++){
					frame->addPoint(c[0], ofColor::white, false);
				}
				for(int i =0; i < c.size() ; i++){
					frame->addPoint(c[i], ofColor::white, false);
				}
//			if(c.size() > 0){
				if(c.isClosed()){
					for(int i =0; i < endCount ; i++){
						frame->addPoint(c[0], ofColor::white, false);
					}
					frame->addPoint(c[0], ofColor::white, false);
					frame->addPoint(c[0], {0,0,0,0}, false);
				}else{
					for(int i =0; i < endCount ; i++){
						frame->addPoint(c[c.size() - 1], ofColor::white, false);
					}
					frame->addPoint(c[c.size() - 1], {0,0,0,0}, false);
				}
			}
		}
//		auto& c = paths[ind].getCommands();
//		cout << "path " << ind << " commands: " << c.size() << endl;
//		bool bWasClose = false;
//		if(c.size() > 0){
//			frame->addPoint(c[0].to, {0,0,0,0}, false);
//		}
//		for(int i =0; i < c.size() -1; i++){
//			frame->addPoint(c[i].to, ofColor::white, false);
//		}
//		if(c.size() > 2){
//			frame->addPoint(c[c.size() - 2].to, {0,0,0,0}, false);
//		}
	}
	if(bScaleToFill && frame->path.getNumVertices()){
		ofRectangle bb;
		bb.set(frame->path.getVertices()[0], 0,0);
		for(auto& v: frame->path.getVertices()){
			bb.growToInclude(v);
		}
		
		
		ofRectangle ildaArea;
		ildaArea.set(-32768, -32768, 65535, 65535);
		ofRectangle scaledRect = bb;
		scaledRect.scaleTo(ildaArea);
		scaledRect.scaleFromCenter(0.8);
		auto from_min = bb.getMin();
		auto from_max = bb.getMax();
		
		auto to_min = scaledRect.getMin();
		auto to_max = scaledRect.getMax();
		
		for(auto& v: frame->path.getVertices()){
			v = growToFill(v, from_min, from_max, to_min, to_max, true);
		}
		
		frame->normalizedPath.clear();
		frame->normalizedPath = frame->path;
		for(auto& v: frame->normalizedPath.getVertices()){
			ofxIlda::FileFrame::normalizePoint(v);
		}
		
		cout << "frame from min " << from_min << endl;
		cout << "frame from max " << from_max << endl;
		cout << "frame to min " << to_min << endl;
		cout << "frame to max " << to_max << endl;
	}
	
	
	

#endif
	return frame;
}
