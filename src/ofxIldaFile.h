#pragma once
#include "ofxIldaFileFrame.h"
//class ofxIldaFileRenderer;
class ofxIldaFile {
public:
	ofxIldaFile();
	
	bool load(const string& filepath);
	
	void draw(const ofRectangle & viewport = ofGetCurrentViewport(), bool bDrawBounds = true);
	
	void reset();
	vector<ofxIldaFileFrame>& getFrames();
	const vector<ofxIldaFileFrame>& getFrames() const;
	const string& getFilepath();
protected:
	int frameRate = 1;
	size_t currentFrame = 0;
	
	vector<ofxIldaFileFrame> frames;
	
	string filepath;
	ofEasyCam cam;
	
//	std::shared_ptr<ofxIldaFileRenderer> renderer;
//	void createRenderer();
};

