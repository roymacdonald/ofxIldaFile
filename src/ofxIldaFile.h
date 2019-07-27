#pragma once
#include "ofxIldaFileFrame.h"


class ofxIldaFile {
public:
	ofxIldaFile();
	ofxIldaFile(const string& name, float frame_duration, int scan_rate);
	
	void setup(const string& name, float frame_duration, int scan_rate);
	
	friend class ofxIldaFileDirectory;
	
	bool load(const string& filepath);
	
	bool loadDialog();
	
	void save(string filepath);
	
	void saveDialog();
	
	void draw(const ofRectangle & viewport = ofGetCurrentViewport(), bool bDrawBounds = true);
	
	
	/// \brief Creates a new frame from an SVG file.
	/// params:
	/// filepath : the path to the svg file
	/// format:  the ilda file format. It can be:
	///        OFX_ILDAFILE_FORMAT_3D_INDEXED_COLOR // 3D Coordinates with Indexed Color
	///        OFX_ILDAFILE_FORMAT_2D_INDEXED_COLOR // 2D Coordinates with Indexed Color
	///        OFX_ILDAFILE_FORMAT_COLOR_PALETTE // Color Palette for Indexed Color Frames
	///        OFX_ILDAFILE_FORMAT_3D_TRUE_COLOR // 3D Coordinates with True Color
	///        OFX_ILDAFILE_FORMAT_2D_TRUE_COLOR // 2D Coordinates with True Color
	/// bScaleToFill: if true it will scale all the points so these use the whole available area. set to false if you're loadding an animation
	/// framename: each ILDA frame has a name, you can add it or not.
	/// companyname: each ILDA frame has a "company name" too which you can add it or not.
	
	/// returns bool: true in case of successfully loading the svg file
	shared_ptr<ofxIldaFileFrame> newFrameFromSVG(const string& filepath, ofxIldaFileFormat format, bool bScaleToFill, const string& framename = "", const string& companyname = "");
	
	
	void reset();
	vector<shared_ptr<ofxIldaFileFrame>>& getFrames();
	const vector<shared_ptr<ofxIldaFileFrame>>& getFrames() const;
	const string& getFilepath();
	
	bool isLoaded();
	
	const string& getName();
	
	float getFrameDuration();
	int getScanRate();
	
	
	static string getValidPath(const string& filepath);
	static string getValidName(const string& _name);
	
	shared_ptr<ofxIldaFileFrame> addFrame();
	shared_ptr<ofxIldaFileFrame> addFrame(shared_ptr<ofxIldaFileFrame> f);
	shared_ptr<ofxIldaFileFrame> addFrame(const ofxIldaFileFrame& f);
	
protected:
	string name = "";
	float frameduration = 0;
	int scanrate = 0;
	
	float lastFrameTime = 0;
	
	size_t currentFrame = 0;
	
	vector<shared_ptr<ofxIldaFileFrame> > frames;
	
	string filepath ="";
	ofEasyCam cam;

	
	
//	std::shared_ptr<ofxIldaFileRenderer> renderer;
//	void createRenderer();
};

