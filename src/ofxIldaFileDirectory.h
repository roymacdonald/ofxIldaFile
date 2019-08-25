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
		
		//	bool loadFileByName(const string& name);
		
	protected:
		
		//	bool loadFile(ofxIldaFile& file, const string& filepath);
		
		std::vector<std::shared_ptr<ofxIlda::File>> ildaFiles;
		
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
}
