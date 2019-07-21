//
//  ofxIldaFileDirectory.cpp
//  example
//
//  Created by Roy Macdonald on 7/21/19.
//
//

#include "ofxIldaFileDirectory.h"
//--------------------------------------------------------------
bool ofxIldaFileDirectory::loadDialog(){
	auto r = ofSystemLoadDialog("Select a folder that contains .ild files", true);
	if(r.bSuccess){
		return loadDir(r.getPath());
	}
	return false;
}
//--------------------------------------------------------------
bool ofxIldaFileDirectory::loadDir(const string& dirPath){
	ofFile d (dirPath);
	if(d.isDirectory()){
		if(findPrgFile(dirPath)){
		dir.close();
		dir.allowExt("ild");
		dir.listDir(dirPath);
		
		fileIndex = 0;
		if(dir.size()){
			return ildaFile.load(dir.getPath(0));
		}
		}else{
		ofLogWarning("ofxIldaFileDirectory::loadDir") << "no .prg file in directory " << dirPath;
		}
	}else{
		ofLogWarning("ofxIldaFileDirectory::loadDir") << dirPath << " is not a directory.";
	}
	return false;
}

//--------------------------------------------------------------
bool ofxIldaFileDirectory::findPrgFile(const string& dirPath){
	ofDirectory d;
	d.allowExt("prg");
	d.listDir(dirPath);
	auto dirBaseName = ofFilePath::getBaseName(dirPath);
	if(d.size()){
		for(int i = 0; i < d.size(); i++){
			if(ofFilePath::getBaseName(d.getPath(i)) == dirBaseName){
				readPrgFile(d.getPath(i));
				return true;
			}
		}
		readPrgFile(d.getPath(0));
		return true;
	}
	return false;
}
//--------------------------------------------------------------
void ofxIldaFileDirectory::readPrgFile(const string& filepath){
	if(ofFilePath::getFileExt(filepath)=="prg"){
		auto buf = ofBufferFromFile(filepath, false);
		if(buf.size() == 0) return;
		prgMap.clear();
	
		for(auto& l: buf.getLines()){
			auto s = ofSplitString(l, ",");
			if(s.size() >= 3){
				prgMap[ofTrim(s[0])] = IldaPrgm(ofToInt(ofTrim(s[1])), ofToFloat(ofTrim(s[2])));
			}else{
				ofLogWarning("ofxIldaFileDirectory::readPrgFile") << "wrong line : " << l;
			}
		}
	}
}
//--------------------------------------------------------------
void ofxIldaFileDirectory::loadNextFile(){
	if(dir.size()){
		(++fileIndex) %= dir.size();
//		ildaFile.load(dir.getPath(fileIndex));
		loadFileAtIndex(fileIndex);
	}
}
//--------------------------------------------------------------
void ofxIldaFileDirectory::loadPrevFile(){
	if(dir.size()){
		if(fileIndex == 0){
			fileIndex = dir.size() - 1;
		}else{
			fileIndex -- ;
		}
		loadFileAtIndex(fileIndex);
		//ildaFile.load(dir.getPath(fileIndex));
	}

}
//--------------------------------------------------------------
void ofxIldaFileDirectory::close(){
	dir.close();
	ildaFile.reset();
	prgMap.clear();
	fileIndex = 0;
}
//--------------------------------------------------------------
size_t ofxIldaFileDirectory::size(){
	return dir.size();
}
//--------------------------------------------------------------
bool ofxIldaFileDirectory::loadFileAtIndex(size_t index){
	if(ildaFile.load(dir.getPath(index))){
		auto prg = prgMap.find(dir.getPath(index));
		if(prg != prgMap.end()){
			ildaFile.frameduration = prg->second.frameDuration;
			ildaFile.scanrate =  prg->second.scanRate;
		}
		fileIndex = index;
		return true;
	}
	return false;
}
//--------------------------------------------------------------
size_t ofxIldaFileDirectory::getCurrentFileIndex(){
	return fileIndex;
}
