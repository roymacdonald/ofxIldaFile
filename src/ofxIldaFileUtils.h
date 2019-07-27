//
//  ildaFileUtils.h
//  ildaFileDecode
//
//  Created by Roy Macdonald on 7/20/19.
//
//

#pragma once
#include "ofxIldaFileConstants.h"
inline short getShortFromChars(char* b, size_t index){
	return ((b[index] & 0xFF) << 8) | (b[index+1] & 0xFF);
}

inline void setShortIntoChars(vector<char>& b, short s, size_t index){
	b[index] = ((s >> 8) & 0xFF);
	b[index+1] = (s & 0xFF);
}
inline void decrementAndWrap(size_t& i, const size_t& limit){
	if(i == 0){
		i = limit - 1;
	}else{
		i -- ;
	}
}

inline bool ifFormat3D(const ofxIldaFileFormat& format){
	return (format == OFX_ILDAFILE_FORMAT_3D_INDEXED_COLOR || format == OFX_ILDAFILE_FORMAT_3D_TRUE_COLOR);
}
inline bool ifFormat2D(const ofxIldaFileFormat& format){
	return (format == OFX_ILDAFILE_FORMAT_2D_INDEXED_COLOR || format == OFX_ILDAFILE_FORMAT_2D_INDEXED_COLOR);
}

inline bool ifFormatTrueColor(const ofxIldaFileFormat& format){
	return (format == OFX_ILDAFILE_FORMAT_3D_TRUE_COLOR || format == OFX_ILDAFILE_FORMAT_2D_TRUE_COLOR);
}
inline bool ifFormatIndexedColor(const ofxIldaFileFormat& format){
	return (format == OFX_ILDAFILE_FORMAT_3D_INDEXED_COLOR || format == OFX_ILDAFILE_FORMAT_2D_INDEXED_COLOR);
}
