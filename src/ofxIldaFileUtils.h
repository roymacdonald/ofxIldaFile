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
inline void decrementAndWrap(size_t& i, const size_t& limit){
	if(i == 0){
		i = limit - 1;
	}else{
		i -- ;
	}
}

