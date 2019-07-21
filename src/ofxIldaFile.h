#pragma once
#include "ofxIldaFileFrame.h"
//class ofxIldaFileRenderer;
class ofxIldaFile {
public:
	ofxIldaFile();
	friend class ofxIldaFileDirectory;
	
	bool load(const string& filepath);
	
	bool loadDialog();
	
	void draw(const ofRectangle & viewport = ofGetCurrentViewport(), bool bDrawBounds = true);
	
	void reset();
	vector<ofxIldaFileFrame>& getFrames();
	const vector<ofxIldaFileFrame>& getFrames() const;
	const string& getFilepath();
protected:
	float frameduration = 0;
	int scanrate = 0;
	
	float lastFrameTime = 0;
	
	size_t currentFrame = 0;
	
	vector<ofxIldaFileFrame> frames;
	
	string filepath;
	ofEasyCam cam;
	
//	std::shared_ptr<ofxIldaFileRenderer> renderer;
//	void createRenderer();
};

