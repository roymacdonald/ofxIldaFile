//
//  ildaFileUtils.h
//  ildaFileDecode
//
//  Created by Roy Macdonald on 7/20/19.
//
//

#pragma once
inline short getShortFromChars(char* b, size_t index){
	return ((b[index] & 0xFF) << 8) | (b[index+1] & 0xFF);
}

inline void setShortIntoChars(vector<char>& b, short s, size_t index){
	b[index] = ((s >> 8) & 0xFF);
	b[index+1] = (s & 0xFF);
}
