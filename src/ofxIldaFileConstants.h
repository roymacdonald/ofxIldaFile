//
//  ofxIldaFileConstants.h
//  example-ofxSvg
//
//  Created by Roy Macdonald on 7/26/19.
//
//

#pragma once
//ILDA Image Data Transfer Format Specification
#include <string>
namespace ofxIlda{
	enum FileFormat{
		
		FILE_FORMAT_3D_INDEXED_COLOR = 0,// 3D Coordinates with Indexed Color
		FILE_FORMAT_2D_INDEXED_COLOR = 1,// 2D Coordinates with Indexed Color
		FILE_FORMAT_COLOR_PALETTE = 2,// Color Palette for Indexed Color Frames
		FILE_FORMAT_3D_TRUE_COLOR = 4,// 3D Coordinates with True Color
		FILE_FORMAT_2D_TRUE_COLOR = 5,// 2D Coordinates with True Color
		FILE_FORMAT_INVALID=3
		
	};
	
	
	static std::string formatToString(const ofxIlda::FileFormat& format){
		switch(format){
			case ofxIlda::FILE_FORMAT_3D_INDEXED_COLOR: return "3d Indexed Color";
			case ofxIlda::FILE_FORMAT_2D_INDEXED_COLOR: return "2d Indexed Color";
			case ofxIlda::FILE_FORMAT_COLOR_PALETTE: return "Color Palette";
			case ofxIlda::FILE_FORMAT_3D_TRUE_COLOR: return "3d Truecolor";
			case ofxIlda::FILE_FORMAT_2D_TRUE_COLOR: return "2d Truecolor";
			case ofxIlda::FILE_FORMAT_INVALID: return "Invalid";
		}
	}
}
