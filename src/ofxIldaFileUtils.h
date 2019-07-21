//
//  ildaFileUtils.h
//  ildaFileDecode
//
//  Created by Roy Macdonald on 7/20/19.
//
//

#pragma once
inline short getShort(char* b, size_t index){
	return ((b[index] & 0xFF) << 8) | (b[index+1] & 0xFF);
}
