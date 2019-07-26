//
//  ofxIldaFileFrame.hpp
//  example
//
//  Created by Roy Macdonald on 7/20/19.
//
//

#pragma once
#include "ofMain.h"
#include "ofxIldaFileUtils.h"
#include "ofxIldaFileColorPalette.h"

class ofxIldaFileFrame{
public:
	friend class ofxIldaFile;
	ofxIldaFileFrame(){}
	ofxIldaFileFrame(const int& format, const string& frameName, const string& companyName);
	
	void setup(const int& format, const string& frameName, const string& companyName);
	
	void addPoint(glm::vec3 point, const ofColor& color, bool bIsNormalized );
	
	bool readFromBuffer(ofBuffer& buffer, size_t startIndex);
	
	void writeToBuffer(ofBuffer& buffer);
	
	const int& getFormat() const;
	const string& getFrameName() const;
	const string& getCompanyName() const;
		  size_t  getNumPoints()  const;
	const size_t& getFrameNumber() const;
	const size_t& getTotalFrames() const;
	
	const char& getScanner() const;
	const size_t& getStartIndex() const;
	
	size_t getDataSize();
	
	int getNumDataBytesForFormat();
	
//	bool isDataNormalized();
	
	friend std::ostream& operator << (std::ostream& os, const ofxIldaFileFrame& f);
	
	static void normalizePoint(glm::vec3& point);
	static void unnormalizePoint(glm::vec3& point);
	
	
	string getAsString();
	bool bFrameSet = false;
	
	static ofxIldaFileFrame getEndFrame(const ofxIldaFileFrame& refFrame);
	
	ofMesh path, normalizedPath;
	
	
	void resetPaths();
	
protected:

	
	
	
	size_t readHeader(ofBuffer& buffer, size_t startIndex);
//	void decodeData(char * d, size_t num_points, size_t size, bool bNormalize = true);	
	void decodeData(ofBuffer& buffer, size_t num_points);
					
	void writeHeader(ofBuffer& buffer);
	void encodeData(ofBuffer& buffer);
	
	
	
//	void readStatusCode(char * d, size_t i);
	int getColorOffset();
	int getStatusCodeOffset();
	
	int format;
	string frame_name;
	string company_name;
//	size_t point_number;
	size_t frame_number = 0;
	size_t total_frame = 0;
	
	char scanner = 0;
	size_t start_id = 0;
	
	
//	bool bNormalizedData;
	
};
