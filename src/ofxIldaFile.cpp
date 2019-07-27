#include "ofxIldaFile.h"
#include "ofxSvg.h"

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
	setup(name, frame_duration, scan_rate);
}
//--------------------------------------------------------------
void ofxIldaFile::setup(const string& name, float frame_duration, int scan_rate){
	this->name = name;
	frameduration = frame_duration;
	scanrate = scan_rate;
}
//--------------------------------------------------------------
bool ofxIldaFile::loadDialog(){
	auto r = ofSystemLoadDialog("Select an .ild file");
	if(r.bSuccess){
		return load(r.getPath());
	}
	return false;
}
//--------------------------------------------------------------
bool ofxIldaFile::load(const string& filepath){
	if( ofToLower(ofFilePath::getFileExt(filepath)) != "ild"){
		ofLogError("ofxIldaFile::load") << "Not a .ild file. Not loading";
		return false;
	}
	ofBuffer buffer = ofBufferFromFile(filepath);
	if(buffer.size() == 0) return false;

	reset();
	
	this->filepath = filepath;
	
	name = ofFilePath::getBaseName(filepath);
	
	for (size_t i=0 ; i< buffer.size() ; ){
		shared_ptr<ofxIldaFileFrame> frame = make_shared<ofxIldaFileFrame>();
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
bool ofxIldaFile::isLoaded(){
	return frames.size() > 0;
}
//--------------------------------------------------------------
void ofxIldaFile::save(string filepath){
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
//			ofLogWarning("ofxIldaFile::save") << "file extension must be .ild! Automatically changed into it";
//		}
		
		ofxIldaFileFrame::getEndFrame(*frames.back()).writeToBuffer(buffer);
		
		ofFilePath::createEnclosingDirectory(filepath);
		
		ofBufferToFile(filepath, buffer);
	}else{
		ofLogWarning("ofxIldaFile::save") << "No data of file. Not writting";
	}
}
//--------------------------------------------------------------
void ofxIldaFile::saveDialog(){
	auto r = ofSystemSaveDialog(name + ".ild", "Save to .ild file");
	if(r.bSuccess){
		save(r.getPath());
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
		
		frames[currentFrame]->normalizedPath.draw(); // path.draw();
		
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
vector<shared_ptr<ofxIldaFileFrame>>& ofxIldaFile::getFrames(){
	return frames;
}
//--------------------------------------------------------------
const vector<shared_ptr<ofxIldaFileFrame>>& ofxIldaFile::getFrames() const {
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
		int numDigits = 1;//(int)(floor(log10(i)) +1);
		if(i > 0) numDigits += (int)(floor(log10(i)));
		cout << "numDigits: " << numDigits << "  " << i <<endl;
		n = n.substr(0, 8 - numDigits) + ofToString(i);
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
shared_ptr<ofxIldaFileFrame> ofxIldaFile::addFrame(){
	frames.push_back(make_shared<ofxIldaFileFrame>());
	return frames.back();
}
//--------------------------------------------------------------
shared_ptr<ofxIldaFileFrame> ofxIldaFile::addFrame(const ofxIldaFileFrame& f){
	frames.push_back(make_shared<ofxIldaFileFrame>(f));
	return frames.back();
}
//--------------------------------------------------------------
shared_ptr<ofxIldaFileFrame> ofxIldaFile::addFrame(shared_ptr<ofxIldaFileFrame> f){
	frames.push_back(f);
	return frames.back();
}
//--------------------------------------------------------------
glm::vec3 growToFill(const glm::vec3& p, const glm::vec3 & mn,const glm::vec3 & mx, bool bDoYFlip ){
	glm::vec3 v;
	v.x = ofMap(p.x, mn.x, mx.x,  -32768, 32767);
	v.y = p.y;
	if(bDoYFlip){
		v.y = mx.y - (v.y - mn.y);
	}
	v.y = ofMap(v.y, mn.y, mx.y,  -32768, 32767);
	
	v.z =0;
	return v;
}
//--------------------------------------------------------------
shared_ptr<ofxIldaFileFrame> ofxIldaFile::newFrameFromSVG(const string& filepath, ofxIldaFileFormat format, bool bScaleToFill, const string& framename, const string& companyname ){
	if(ofToLower(ofFilePath::getFileExt(filepath)) != "svg"){
		ofLogWarning("ofxIldaFile::newFrameFromSVG") << "could not load. Not an svg file.";
		return nullptr;
	}
	ofxSVG svg;
	svg.load(filepath);
	auto& paths = svg.getPaths();
	if(paths.size() == 0){
		ofLogWarning("ofxIldaFile::newFrameFromSVG") << "loaded svg file has no paths";
		return nullptr;
	}
//	auto file = ildaDir.addNewFile("SWISS", 2, 20);
	auto frame =  addFrame({format, framename, companyname});
	
	ofRectangle bb;
	if(bScaleToFill){
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
	}
	auto mn = bb.getMin();
	auto mx = bb.getMax();
	//		cout << "svg min" << mn << endl;
	//		cout << "svg max" << mx << endl;
	
	for(size_t ind = 0; ind < paths.size(); ind++){
		auto& c = paths[ind].getCommands();
		bool bWasClose = false;
		if(c.size() > 0){
			frame->addPoint(bScaleToFill?growToFill(c[0].to, mn, mx, true):c[0].to, {0,0,0,0}, false);
		}
		for(int i =0; i < c.size() -1; i++){
			frame->addPoint(bScaleToFill?growToFill(c[i].to, mn, mx, true):c[i].to, ofColor::white, false);
		}
		if(c.size() > 1){
			frame->addPoint(bScaleToFill?growToFill(c[c.size() - 2].to, mn, mx, true):c[c.size() - 2].to, {0,0,0,0}, false);
		}
	}
	return frame;
}
