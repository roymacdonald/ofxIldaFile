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
//	ildaFiles.resize(1);
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
//						ildaFiles[i] = make_shared<ofxIldaFile>();
						bLoadded &= loadFileAtIndex(i, dir.getPath(i));
					}
					dir.close();
					return bLoadded;// will return false if any file loaded incorrectly
				}else{
//					ildaFiles.resize(1);
//					ildaFiles[0] = make_shared<ofxIldaFile>();
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
			
				string prg = ofFilePath::getFileName(validPath)+ ", " + ofToString(ildaFiles[i]->getScanRate())+ ", " + ofToString(ildaFiles[i]->getFrameDuration()) + "\n";
				
				prgBuffer.append(prg);
				cout << prg;
			}
		}
		
		string bufferPath = dirPath + ofFilePath::getBaseName(ofFilePath::removeTrailingSlash(dirPath))+".prg";
		cout << ofFilePath::getBaseName(dirPath) << endl;
		cout << bufferPath << endl;
		ofBufferToFile( bufferPath, prgBuffer, false);
		
		
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
//	if(dir.size()){
	decrementAndWrap(fileIndex, size());
//		if(fileIndex == 0){
//			fileIndex = dir.size() - 1;
//		}else{
//			fileIndex -- ;
//		}
	loadFileAtIndex(fileIndex);
		//ildaFile.load(dir.getPath(fileIndex));
//	}
	
}
//--------------------------------------------------------------
void ofxIldaFileDirectory::close(){
	dir.close();
	ildaFiles.clear();
//	ildaFiles.resize(1);
	prgMap.clear();
	fileIndex = 0;
}
//--------------------------------------------------------------
size_t ofxIldaFileDirectory::size(){
	if(bFilesPreloaded){
		return ildaFiles.size();
	}
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
////--------------------------------------------------------------
//bool ofxIldaFileDirectory::loadFile(ofxIldaFile& file, const string& filepath){
////	cout << __PRETTY_FUNCTION__ << endl;
//	if(file.load(filepath)){
//		auto prg = prgMap.find(ofFilePath::getFileName(filepath));
//		if(prg != prgMap.end()){
//			file.frameduration = prg->second.frameDuration;
//			file.scanrate =  prg->second.scanRate;
//		}
//		return true;
//	}
//	return false;
//}
//--------------------------------------------------------------
bool ofxIldaFileDirectory::loadFileAtIndex(size_t index, string filepath){
	auto fIndex = index;
	if(!bFilesPreloaded){
		if(index >= dir.size()) return false;
		fIndex = 0;
	}
	if(fIndex >= ildaFiles.size()){
		ildaFiles.resize(fIndex+1);
	}
	if(!ildaFiles[fIndex]){
		ildaFiles[fIndex] = make_shared<ofxIldaFile>();
	}
	
	if(filepath.empty()){
		if(!bFilesPreloaded){
			filepath = dir.getPath(index);
		}else if(ildaFiles[fIndex]){
			filepath = ildaFiles[fIndex]->getFilepath();
		}
		if(filepath.empty()){
			return false;
		}
	}

	if(ildaFiles[fIndex]){
//		if(ildaFiles[fIndex]->isLoaded()){
//			fileIndex = fIndex;
//			return true;
//		}else
//		if(index < dir.size()){
//			if(loadFile(*ildaFiles[fIndex], dir.getPath(index))){
//			auto fPath = dir.getPath(index);
			if(ildaFiles[fIndex]->load(filepath)){
				auto prg = prgMap.find(ofFilePath::getFileName(filepath));
				if(prg != prgMap.end()){
					ildaFiles[fIndex]->frameduration = prg->second.frameDuration;
					ildaFiles[fIndex]->scanrate =  prg->second.scanRate;
				}
				fileIndex = fIndex;
				return true;
			}
//		}
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
std::shared_ptr<ofxIldaFile>  ofxIldaFileDirectory::getCurrentFile(){
	auto fIndex = bFilesPreloaded?fileIndex:0;
	if(fIndex < ildaFiles.size()){
		return ildaFiles[fIndex];
	}
	return nullptr;
}

//--------------------------------------------------------------
bool ofxIldaFileDirectory::isFilesPreloaded(){
	return bFilesPreloaded;
}
//--------------------------------------------------------------
void ofxIldaFileDirectory::drawCurrentFile(){
	auto current = getCurrentFile();
	if(current){
			current->draw();
	}else{
		ofDrawBitmapStringHighlight("ofxIldaFileDirectory::draw -> can't draw. Current Ilda file is null", 20,20, ofColor(0, 120));
	}
	
}
//--------------------------------------------------------------
string ofxIldaFileDirectory::getCurrentFileInfo(){
	stringstream ss;
	auto current = getCurrentFile();
	if(current){
		string path = current->getFilepath();
		
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
