//
//  ofxIldaFileDirectory.cpp
//  example
//
//  Created by Roy Macdonald on 7/21/19.
//
//

#include "ofxIldaFileDirectory.h"
//--------------------------------------------------------------
ofxIldaFileDirectory::ofxIldaFileDirectory(){
	ildaFiles.resize(1);
}
//--------------------------------------------------------------
bool ofxIldaFileDirectory::loadDialog(bool preloadAll){
	auto r = ofSystemLoadDialog("Select a folder that contains .ild files", true);
	if(r.bSuccess){
		return loadDir(r.getPath(), preloadAll);
	}
	return false;
}
//--------------------------------------------------------------
bool ofxIldaFileDirectory::loadDir(const string& dirPath, bool preloadAll){
	ofFile d (dirPath);
	if(d.isDirectory()){
		if(findPrgFile(dirPath)){
			dir.close();
			dir.allowExt("ild");
			dir.listDir(dirPath);
			
			fileIndex = 0;
			if(dir.size()){
				bFilesPreloaded = preloadAll;
				if(preloadAll){
					ildaFiles.resize(dir.size());
					bool bLoadded = true;
					for(size_t i = 0; i < ildaFiles.size(); i++){
						ildaFiles[i] = make_shared<ofxIldaFile>();
						bLoadded &= loadFileAtIndex(i);
					}
					dir.close();
					return bLoadded;// will return false if any file loaded incorrectly
				}else{
					ildaFiles.resize(1);
					ildaFiles[0] = make_shared<ofxIldaFile>();
					return loadFileAtIndex(0);
				}
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
void ofxIldaFileDirectory::saveDir(string dirPath){
	
	ofFile d (dirPath);
	if(d.isDirectory() && ildaFiles.size() > 0){
		
		ofBuffer prgBuffer;
		dirPath = ofFilePath::getPathForDirectory(dirPath);
		for(size_t i = 0; i < ildaFiles.size(); i++){
			if(ildaFiles[i]){
			string validPath = ofxIldaFile::getValidPath(dirPath + ildaFiles[i]->getName() + ".ild");
			
			ildaFiles[i]->save(validPath);
			
			prgBuffer.append(ofFilePath::getFileName(validPath)+ ", " + ofToString(ildaFiles[i]->getScanRate())+ ", " + ofToString(ildaFiles[i]->getFrameDuration()) + "\n");
			}
		}
		
		ofBufferToFile( dirPath + ofFilePath::getBaseName(dirPath)+".prg", prgBuffer, false);
		
		
	}else{
		ofLogWarning("ofxIldaFileDirectory::saveDir") << dirPath << " is not a directory.";
	}
}

//--------------------------------------------------------------
void ofxIldaFileDirectory::saveDialog(){
	auto r = ofSystemLoadDialog("Select a folder to save .ild files", true);
	if(r.bSuccess){
		return saveDir(r.getPath());
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
	ildaFiles.clear();
	ildaFiles.resize(1);
	prgMap.clear();
	fileIndex = 0;
}
//--------------------------------------------------------------
size_t ofxIldaFileDirectory::size(){
	return dir.size();
}
//--------------------------------------------------------------
//bool ofxIldaFileDirectory::loadFileByName(const string& name){
//	size_t n = (bFilesPreloaded? ildaFiles.size() : dir.size());
//	for(int i = 0; i < n; i++){
//		if(bFilesPreloaded){
//			if(ildaFiles[i].getName() == name){
//
//			}
//		}
//	}
//}
//--------------------------------------------------------------
bool ofxIldaFileDirectory::loadFile(ofxIldaFile& file, const string& filepath){
	if(file.load(filepath)){
		auto prg = prgMap.find(filepath);
		if(prg != prgMap.end()){
			file.frameduration = prg->second.frameDuration;
			file.scanrate =  prg->second.scanRate;
		}
		return true;
	}
	return false;
}
//--------------------------------------------------------------
bool ofxIldaFileDirectory::loadFileAtIndex(size_t index){
	if(bFilesPreloaded){
		if(index < ildaFiles.size()){
			if(ildaFiles[index]){
				if(ildaFiles[index]->isLoaded()){
					fileIndex = index;
					return true;
				}else if(index < dir.size()){
					if(loadFile(*ildaFiles[index], dir.getPath(index))){
						fileIndex = index;
						return true;
					}
				}
			}
			return false;
		}
	}else{
		if(loadFile(*ildaFiles[0], dir.getPath(index))){
			fileIndex = index;
			return true;
		}
	}
	return false;
}
//--------------------------------------------------------------
size_t ofxIldaFileDirectory::getCurrentFileIndex(){
	return fileIndex;
}
//--------------------------------------------------------------
std::vector<std::shared_ptr<ofxIldaFile>>& ofxIldaFileDirectory::getIldaFiles(){
	return ildaFiles;
}
//--------------------------------------------------------------
const std::vector<std::shared_ptr<ofxIldaFile>>& ofxIldaFileDirectory::getIldaFiles() const{
	return ildaFiles;
}
//--------------------------------------------------------------
std::shared_ptr<ofxIldaFile> & ofxIldaFileDirectory::getCurrentFile(){
	
	if(bFilesPreloaded && fileIndex < ildaFiles.size()){
		return ildaFiles[fileIndex];
	}else if(ildaFiles.size()){
		return ildaFiles[0];
	}
	
}
//--------------------------------------------------------------
const std::shared_ptr<ofxIldaFile> & ofxIldaFileDirectory::getCurrentFile() const{
	if(bFilesPreloaded && fileIndex < ildaFiles.size()){
		return ildaFiles[fileIndex];
	}else if(ildaFiles.size()){
		return ildaFiles[0];
	}
}
//--------------------------------------------------------------
bool ofxIldaFileDirectory::isFilesPreloaded(){
	return bFilesPreloaded;
}
//--------------------------------------------------------------
void ofxIldaFileDirectory::drawCurrentFile(){
	auto & current = getCurrentFile();
	if(current){
			current->draw();
	}else{
		ofDrawBitmapStringHighlight("ofxIldaFileDirectory::draw -> can't draw. Current Ilda file is null", 20,20, ofColor(0, 120));
	}
	
}
//--------------------------------------------------------------
string ofxIldaFileDirectory::getCurrentFileInfo(){
	stringstream ss;
	if(getCurrentFile()){
		string path = getCurrentFile()->getFilepath();
		
		ss << "Current file : " << ofFilePath::getFileName(path) << endl;

		ss << "Current folder : " << ofFilePath::getEnclosingDirectory(path) << endl;
		ss << "Current file index: " << fileIndex ;
		
	}else{
		ss << "Current file is null";
	}
	return ss.str();
}
//--------------------------------------------------------------
std::shared_ptr<ofxIldaFile> ofxIldaFileDirectory::addNewFile(const string& name, float frameDuration, int scanrate){
	ildaFiles.push_back(make_shared<ofxIldaFile>(name, frameDuration, scanrate));
	return ildaFiles.back();
}
