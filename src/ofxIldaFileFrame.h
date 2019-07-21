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
	
	bool readFromBuffer(ofBuffer& buffer, size_t startIndex);
	
	const int& getFormat() const;
	const string& getFrameName() const;
	const string& getCompanyName() const;
	const size_t& getPointNumber() const;
	const size_t& getFrameNumber() const;
	const size_t& getTotalFrames() const;
	const char& getStatusCode() const;
	const char& getScanner() const;
	const size_t& getStartIndex() const;
	
	size_t getDataSize();
	
	int getNumDataBytesForFormat();
	
	

	
	friend std::ostream& operator << (std::ostream& os, const ofxIldaFileFrame& f);
	
	
	ofMesh path;
	
protected:
	
	bool readHeader(ofBuffer& buffer, size_t startIndex);
	void decodeData(char * d, size_t size, bool bNormalize = true);	
	
	void readStatusCode(char * d, size_t i);
	int getColorOffset();
	
	int format;
	string frame_name;
	string company_name;
	size_t point_number;
	size_t frame_number;
	size_t total_frame;
	char status_code;
	char scanner;
	size_t start_id;
	
};
