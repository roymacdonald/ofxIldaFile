//
//  ofxIldaFileDirectory.hpp
//  example
//
//  Created by Roy Macdonald on 7/21/19.
//
//

#pragma once
#include "ofxIldaFile.h"
namespace ofxIlda{
	class IldaPrgm{
	public:
		IldaPrgm(){}
		IldaPrgm(const size_t& _scanRate, const float& _frameDuration):scanRate(_scanRate), frameDuration(_frameDuration){}
		
		size_t scanRate;
		float frameDuration;
	};
	
	class FileDirectory{
	public:
		FileDirectory(){}
		bool loadDir(const string& dirPath, bool preloadAll = true);
		bool loadDialog(bool preloadAll = true);
		
		void saveDir(string dirPath);
		void saveDialog();
		
		std::shared_ptr<ofxIlda::File> addNewFile(const string& name, float frameDuration, int scanrate);
		
		
		bool isFilesPreloaded();
		
		void close();
		
		void loadNextFile();
		void loadPrevFile();
		
		void drawCurrentFile();
		
		string getCurrentFileInfo();
		
		size_t size();
		bool loadFileAtIndex(size_t index, string filepath = "");
		
		size_t getCurrentFileIndex();
		
		
		std::shared_ptr<ofxIlda::File> getCurrentFile();
		
		std::vector<std::shared_ptr<ofxIlda::File>>& getIldaFiles();
		const std::vector<std::shared_ptr<ofxIlda::File>>& getIldaFiles() const;
		
		std::map<string, IldaPrgm> & getPrgMap();
		const std::map<string, IldaPrgm> & getPrgMap() const;
		
		static void updatePrgMap(std::string filename, std::map<string, IldaPrgm>& prgMap, const size_t& scanRate, const float& frameDuration);
		
		static bool findPrgFile(const string& dirpath, std::map<string, IldaPrgm>& prgMap);
		static bool readPrgFile(const string& filepath, std::map<string, IldaPrgm>& prgMap);
		static void createPrgFile(string dirpath, std::map<string, IldaPrgm>& prgMap);
		
		static std::map<string, IldaPrgm> makePrgMapFromIldaFiles(const std::vector<std::shared_ptr<ofxIlda::File>>& ildaFiles);
		
	protected:
		
		//	bool loadFile(ofxIldaFile& file, const string& filepath);
		
		std::vector<std::shared_ptr<ofxIlda::File>> ildaFiles;
		
		
		std::map<string, IldaPrgm> prgMap;
		
		ofDirectory dir;
		size_t fileIndex = 0;
		bool bFilesPreloaded  = false;
	};
}
