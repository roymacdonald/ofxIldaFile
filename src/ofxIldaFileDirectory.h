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
	ofxIldaFileDirectory();
	bool loadDir(const string& dirPath, bool preloadAll = false);
	bool loadDialog(bool preloadAll = false);
	
	void saveDir(string dirPath);
	void saveDialog();
	
	std::shared_ptr<ofxIldaFile> addNewFile(const string& name, float frameDuration, int scanrate);
	
	
	bool isFilesPreloaded();
	
	void close();
	
	void loadNextFile();
	void loadPrevFile();
	
	void drawCurrentFile();
	
	string getCurrentFileInfo();
	
	size_t size();
	bool loadFileAtIndex(size_t index);
	
	size_t getCurrentFileIndex();
	
	
	std::shared_ptr<ofxIldaFile> & getCurrentFile();
	const std::shared_ptr<ofxIldaFile> & getCurrentFile() const;
	
	
	std::vector<std::shared_ptr<ofxIldaFile>>& getIldaFiles();
	const std::vector<std::shared_ptr<ofxIldaFile>>& getIldaFiles() const;
	
//	bool loadFileByName(const string& name);
	
protected:
	
	bool loadFile(ofxIldaFile& file, const string& filepath);
	
	std::vector<std::shared_ptr<ofxIldaFile>> ildaFiles;
	
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
	bool bFilesPreloaded  = false;
};
