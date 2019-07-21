//
//  ofxIldaFileDirectory.hpp
//  example
//
//  Created by Roy Macdonald on 7/21/19.
//
//

#pragma once
#include "ofxIldaFile.h"

class ofxIldaFileDirectory{
public:
	
	bool loadDir(const string& dirPath);
	
	bool loadDialog();
	
	void close();
	
	void loadNextFile();
	void loadPrevFile();
	
	ofxIldaFile ildaFile;
	
	size_t size();
	bool loadFileAtIndex(size_t index);
	
	size_t getCurrentFileIndex();
	
protected:
	
	bool findPrgFile(const string& dirpath);
	void readPrgFile(const string& filepath);
	
	class IldaPrgm{
	public:
		IldaPrgm(){}
		IldaPrgm(const size_t& _scanRate, const float& _frameDuration):scanRate(_scanRate), frameDuration(_frameDuration){}
		
		size_t scanRate;
		float frameDuration;
	};
	std::map<string, IldaPrgm> prgMap;
	
	ofDirectory dir;
	size_t fileIndex = 0;
};
