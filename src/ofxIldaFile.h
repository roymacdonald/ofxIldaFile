#pragma once
#include "ofxIldaFileFrame.h"
//class ofxIldaFileRenderer;
class ofxIldaFile {
public:
	ofxIldaFile();
	ofxIldaFile(const string& name, float frame_duration, int scan_rate);
	friend class ofxIldaFileDirectory;
	
	bool load(const string& filepath);
	
	bool loadDialog();
	
	void save(const string& filepath);
	
	void saveDialog();
	
	void draw(const ofRectangle & viewport = ofGetCurrentViewport(), bool bDrawBounds = true);
	
	void reset();
	vector<ofxIldaFileFrame>& getFrames();
	const vector<ofxIldaFileFrame>& getFrames() const;
	const string& getFilepath();
	
	bool isLoaded();
	
	const string& getName();
	
	float getFrameDuration();
	int getScanRate();
	
	
	static string getValidPath(const string& filepath);
	static string getValidName(const string& _name);
	
protected:
	string name = "";
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

