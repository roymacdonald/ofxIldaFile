#pragma once
#include "ofxIldaFileFrame.h"
#define USE_OFX_ILDA
#ifdef USE_OFX_ILDA
#include "ofxIldaFrame.h"
#endif
namespace ofxIlda{
class File {
public:
	File();
	
	File(const string& name, float frame_duration, int scan_rate);
	
	
	/// \brief
	/// \param name 
	/// \param frame_duration
	/// \param scan_rate
	
	void setup(const string& name, float frame_duration, int scan_rate);
	
	friend class ofxIldaFileDirectory;
	
	bool load(const string& filepath);
	
	bool loadDialog();
	
	/// as the file path needs to be validated it will return the validated and formated filepath; the actual file path where the file got saved.
	string save(string filepath);
	
	void saveDialog();
	
	void draw(const ofRectangle & viewport = ofGetCurrentViewport(), bool bDrawBounds = true);
	
	void setPaused(bool paused);
	bool isPaused();
	/// \brief Creates a new frame from an SVG file.
	///
	/// \param filepath  the path to the svg file
	/// \param format  the ilda file format. It can be any of ofxIlda::FileFormat.
	/// \param bScaleToFill if true it will scale all the points so these use the whole available area. set to false if you're loadding an animation
	/// \param framename each ILDA frame has a name, you can add it or not.
	/// \param companyname each ILDA frame has a "company name" too which you can add it or not.
	
	/// \returns a shared pointer of the newly created frame if everything went ok, otherwise returns a nullptr.
	shared_ptr<ofxIlda::FileFrame> newFrameFromSVG(const string& filepath, ofxIlda::FileFormat format, bool bScaleToFill, const string& framename = "", const string& companyname = "");
	
	
	void reset();
	vector<shared_ptr<ofxIlda::FileFrame>>& getFrames();
	const vector<shared_ptr<ofxIlda::FileFrame>>& getFrames() const;
	const string& getFilepath();
	
	bool isLoaded();
	
	const string& getName();
	
	float getFrameDuration();
	int getScanRate();
	
	void setFrameDuration(float frameDuration);
	void setScanRate(int scanRate);
	
	
	
	static string getValidPath(const string& filepath);
	static string getValidName(const string& _name);
	
	shared_ptr<ofxIlda::FileFrame> addFrame();
	shared_ptr<ofxIlda::FileFrame> addFrame(shared_ptr<ofxIlda::FileFrame> f);
	shared_ptr<ofxIlda::FileFrame> addFrame(const ofxIlda::FileFrame& f);
	
	shared_ptr<ofxIlda::FileFrame> getCurrentFrame();
	size_t getCurrentFrameIndex();

	
	
	
	ofEasyCam& getCamera(){return cam;}
	vector<ofPath> svgPaths;
//	vector<glm::vec3> svgPathsStart, svgPathsStartProcessed;
//	vector<glm::vec3> svgPathsEnd, svgPathsEndProcessed;
	
	
	shared_ptr<FrameSettings> getFrameSettings();
	shared_ptr<ofxIlda::Frame> getIldaFrame();
	
	
	vector <glm::vec3> splitPoints, transformedSplitPoints;
	
	void nextFrame();
	void prevFrame();
protected:

	
	shared_ptr<ofxIlda::Frame> ildaFrame = nullptr;
	shared_ptr<FrameSettings> frameSettings = nullptr;
//	vector<size_t> svgPathsToPolyIndices;
	ofEventListener ildaFrameParamListener;
	void updateFromIldaFrame();
	string name = "";
	float frameduration = 0;
	int scanrate = 0;
	
	float lastFrameTime = 0;
	
	size_t currentFrame = 0;
	
	vector<shared_ptr<ofxIlda::FileFrame> > frames;
	
	string filepath ="";
	ofEasyCam cam;
	
	bool bPaused = false;
	
	
//	std::shared_ptr<ofxIldaFileRenderer> renderer;
//	void createRenderer();
};

}
