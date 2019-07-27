//
//  ofxIldaFileConstants.h
//  example-ofxSvg
//
//  Created by Roy Macdonald on 7/26/19.
//
//

#pragma once
//ILDA Image Data Transfer Format Specification
enum ofxIldaFileFormat{
	
	OFX_ILDAFILE_FORMAT_3D_INDEXED_COLOR = 0,// 3D Coordinates with Indexed Color
	OFX_ILDAFILE_FORMAT_2D_INDEXED_COLOR = 1,// 2D Coordinates with Indexed Color
	OFX_ILDAFILE_FORMAT_COLOR_PALETTE = 2,// Color Palette for Indexed Color Frames
	OFX_ILDAFILE_FORMAT_3D_TRUE_COLOR = 4,// 3D Coordinates with True Color
	OFX_ILDAFILE_FORMAT_2D_TRUE_COLOR = 5,// 2D Coordinates with True Color
	OFX_ILDAFILE_FORMAT_INVALID=3

};

