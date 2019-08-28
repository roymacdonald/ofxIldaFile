//
//  ofxIlda::FileDirectory.cpp
//  example
//
//  Created by Roy Macdonald on 7/21/19.
//
//

#include "ofxIldaFileDirectory.h"
//--------------------------------------------------------------
bool ofxIlda::FileDirectory::loadDialog(bool preloadAll){
	auto r = ofSystemLoadDialog("Select a folder that contains .ild files", true);
	if(r.bSuccess){
		return loadDir(r.getPath(), preloadAll);
	}
	return false;
}
//--------------------------------------------------------------
bool ofxIlda::FileDirectory::loadDir(const string& dirPath, bool preloadAll){
	ofFile d (dirPath);
	if(d.isDirectory()){
		if(findPrgFile(dirPath, prgMap) ){
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
						bLoadded &= loadFileAtIndex(i, dir.getPath(i));
					}
					dir.close();
					return bLoadded;// will return false if any file loaded incorrectly
				}else{
					return loadFileAtIndex(0);
				}
			}
		}else{
			ofLogWarning("ofxIlda::FileDirectory::loadDir") << "no .prg file in directory " << dirPath;
		}
	}else{
		ofLogWarning("ofxIlda::FileDirectory::loadDir") << dirPath << " is not a directory.";
	}
	return false;
}
//--------------------------------------------------------------
void ofxIlda::FileDirectory::saveDir(string dirPath){
	
	ofFile d (dirPath);
	if(d.isDirectory() && ildaFiles.size() > 0){
		
//		ofBuffer prgBuffer;
		dirPath = ofFilePath::getPathForDirectory(dirPath);
		for(size_t i = 0; i < ildaFiles.size(); i++){
			if(ildaFiles[i]){
				string validPath = ofxIlda::File::getValidPath(dirPath + ildaFiles[i]->getName() + ".ild");
				ildaFiles[i]->save(validPath);
			}
		}
		auto prg = makePrgMapFromIldaFiles(ildaFiles);
		createPrgFile(dirPath,prg);
		
	}else{
		ofLogWarning("ofxIlda::FileDirectory::saveDir") << dirPath << " is not a directory.";
	}
}

//--------------------------------------------------------------
void ofxIlda::FileDirectory::saveDialog(){
	auto r = ofSystemLoadDialog("Select a folder to save .ild files", true);
	if(r.bSuccess){
		return saveDir(r.getPath());
	}
	return false;
}

//--------------------------------------------------------------
void ofxIlda::FileDirectory::loadNextFile(){
	if(dir.size()){
		(++fileIndex) %= dir.size();
		//		ildaFile.load(dir.getPath(fileIndex));
		loadFileAtIndex(fileIndex);
	}
}
//--------------------------------------------------------------
void ofxIlda::FileDirectory::loadPrevFile(){
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
void ofxIlda::FileDirectory::close(){
	dir.close();
	ildaFiles.clear();
//	ildaFiles.resize(1);
	prgMap.clear();
	fileIndex = 0;
}
//--------------------------------------------------------------
size_t ofxIlda::FileDirectory::size(){
	if(bFilesPreloaded){
		return ildaFiles.size();
	}
	return dir.size();
}
//--------------------------------------------------------------
bool ofxIlda::FileDirectory::loadFileAtIndex(size_t index, string filepath){
	auto fIndex = index;
	if(!bFilesPreloaded){
		if(index >= dir.size()) return false;
		fIndex = 0;
	}
	if(fIndex >= ildaFiles.size()){
		ildaFiles.resize(fIndex+1);
	}
	if(!ildaFiles[fIndex]){
		ildaFiles[fIndex] = make_shared<ofxIlda::File>();
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
			if(ildaFiles[fIndex]->load(filepath)){
				auto prg = prgMap.find(ofFilePath::getFileName(filepath));
				if(prg != prgMap.end()){
					ildaFiles[fIndex]->setFrameDuration(prg->second.frameDuration);
					ildaFiles[fIndex]->setScanRate(prg->second.scanRate);
				}
				fileIndex = fIndex;
				std::cout << "loaded ilda file :" << filepath << std::endl;
				return true;
			}
//		}
	}
	return false;
}
//--------------------------------------------------------------
size_t ofxIlda::FileDirectory::getCurrentFileIndex(){
	return fileIndex;
}
//--------------------------------------------------------------
std::vector<std::shared_ptr<ofxIlda::File>>& ofxIlda::FileDirectory::getIldaFiles(){
	return ildaFiles;
}
//--------------------------------------------------------------
const std::vector<std::shared_ptr<ofxIlda::File>>& ofxIlda::FileDirectory::getIldaFiles() const{
	return ildaFiles;
}
//--------------------------------------------------------------
std::shared_ptr<ofxIlda::File>  ofxIlda::FileDirectory::getCurrentFile(){
	auto fIndex = bFilesPreloaded?fileIndex:0;
	if(fIndex < ildaFiles.size()){
		return ildaFiles[fIndex];
	}
	return nullptr;
}

//--------------------------------------------------------------
bool ofxIlda::FileDirectory::isFilesPreloaded(){
	return bFilesPreloaded;
}
//--------------------------------------------------------------
void ofxIlda::FileDirectory::drawCurrentFile(){
	auto current = getCurrentFile();
	if(current){
			current->draw();
	}else{
		ofDrawBitmapStringHighlight("ofxIlda::FileDirectory::draw -> can't draw. Current Ilda file is null", 20,20, ofColor(0, 120));
	}
	
}
//--------------------------------------------------------------
string ofxIlda::FileDirectory::getCurrentFileInfo(){
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
std::shared_ptr<ofxIlda::File> ofxIlda::FileDirectory::addNewFile(const string& name, float frameDuration, int scanrate){
	ildaFiles.push_back(make_shared<ofxIlda::File>(name, frameDuration, scanrate));
	return ildaFiles.back();
}
//--------------------------------------------------------------
std::map<string, ofxIlda::IldaPrgm> & ofxIlda::FileDirectory::getPrgMap(){
	return prgMap;
}
//--------------------------------------------------------------
const std::map<string, ofxIlda::IldaPrgm> & ofxIlda::FileDirectory::getPrgMap() const{
	return prgMap;
}
//--------------------------------------------------------------
bool ofxIlda::FileDirectory::findPrgFile(const string& dirPath, std::map<string, ofxIlda::IldaPrgm>& prgMap){
	ofDirectory d;
	d.allowExt("prg");
	d.listDir(dirPath);
	auto dirBaseName = ofFilePath::getBaseName(dirPath);
	if(d.size()){
		for(int i = 0; i < d.size(); i++){
			if(ofFilePath::getBaseName(d.getPath(i)) == dirBaseName){
				if(readPrgFile(d.getPath(i),prgMap))return true;
			}
		}
		return  readPrgFile(d.getPath(0),prgMap);
	}
	return false;
}
//--------------------------------------------------------------
bool ofxIlda::FileDirectory::readPrgFile(const string& filepath, std::map<string, ofxIlda::IldaPrgm>& prgMap){
	if(ofToLower(ofFilePath::getFileExt(filepath))=="prg"){
		auto buf = ofBufferFromFile(filepath, false);
		if(buf.size() == 0) return false;
		
		prgMap.clear();
		
		for(auto& l: buf.getLines()){
			auto s = ofSplitString(l, ",");
			if(s.size() >= 3){
				prgMap[ofTrim(s[0])] = IldaPrgm(ofToInt(ofTrim(s[1])), ofToFloat(ofTrim(s[2])));
			}else{
				ofLogWarning("ofxIlda::FileDirectory::readPrgFile") << "wrong line : " << l;
			}
		}
		return prgMap.size() > 0;
	}
	return false;
}
//--------------------------------------------------------------
void ofxIlda::FileDirectory::createPrgFile(string dirpath, std::map<string, ofxIlda::IldaPrgm>& prgMap){
	cout << "ofxIlda::FileDirectory::createPrgFile" << endl;
	cout << "dirpath: " << dirpath << endl;
	
	ofBuffer prgBuffer;
	dirpath = ofFilePath::getPathForDirectory(dirpath);
	cout << "dirpath: " << dirpath << endl;
	for(auto& p : prgMap){
		string filename = p.first;
		if(ofToLower(ofFilePath::getFileExt(filename)) != "ild"){
			filename += ".ild";
		}
		
			string prg = ofFilePath::getFileName(filename)+ "," + ofToString(p.second.scanRate)+ "," + ofToString(p.second.frameDuration, 1) + "\n";
			
			prgBuffer.append(prg);
			cout << prg;
	}
	
	string bufferPath = dirpath + ofFilePath::getBaseName(ofFilePath::removeTrailingSlash(dirpath))+".prg";
	cout << ofFilePath::getBaseName(dirpath) << endl;
	cout << bufferPath << endl;
	ofBufferToFile( bufferPath, prgBuffer, false);
}
//--------------------------------------------------------------
void ofxIlda::FileDirectory::updatePrgMap(std::string filename, std::map<string, ofxIlda::IldaPrgm>& prgMap, const size_t& scanRate, const float& frameDuration){
	filename = ofFilePath::getFileName(filename);// this is to make sure that the filename is properly formated
	prgMap[filename].frameDuration = frameDuration;
	prgMap[filename].scanRate = scanRate;
}
//--------------------------------------------------------------
std::map<string, ofxIlda::IldaPrgm> ofxIlda::FileDirectory::makePrgMapFromIldaFiles(const std::vector<std::shared_ptr<ofxIlda::File>>& ildaFiles){
	
	std::map<string, ofxIlda::IldaPrgm> prgMap;
	for(size_t i = 0; i < ildaFiles.size(); i++){
		if(ildaFiles[i]){
			updatePrgMap(ildaFiles[i]->getName() + ".ild", prgMap, ildaFiles[i]->getScanRate(), ildaFiles[i]->getFrameDuration());
		}
	}
	return prgMap;
}
