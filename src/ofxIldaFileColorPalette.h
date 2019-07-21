//
//  ildaColorPalette.h
//  ildaFileDecode
//
//  Created by Roy Macdonald on 7/20/19.
//
//

#pragma once
#include "ofMain.h"
static vector<ofColor>& ilda_standard_color_palette(){
	static std::unique_ptr<vector<ofColor>> p;
	if(!p){
		p = std::make_unique< vector<ofColor> >();
		
		p->push_back({   255,     0,   0 }); // #0
		p->push_back({   255,    16,   0 });
		p->push_back({   255,    32,   0 });
		p->push_back({   255,    48,   0 });
		p->push_back({   255,    64,   0 });
		p->push_back({   255,    80,   0 });
		p->push_back({   255,    96,   0 });
		p->push_back({   255,   112,   0 });
		p->push_back({   255,   128,   0 });
		p->push_back({   255,   144,   0 });
		p->push_back({   255,   160,   0 });
		p->push_back({   255,   176,   0 });
		p->push_back({   255,   192,   0 });
		p->push_back({   255,   208,   0 });
		p->push_back({   255,   224,   0 });
		p->push_back({   255,   240,   0 });
		p->push_back({   255,   255,   0 }); // #16
		p->push_back({   224,   255,   0 });
		p->push_back({   192,   255,   0 });
		p->push_back({   160,   255,   0 });
		p->push_back({   128,   255,   0 });
		p->push_back({    96,   255,   0 });
		p->push_back({    64,   255,   0 });
		p->push_back({    32,   255,   0 });
		p->push_back({     0,   255,   0 }); // #24
		p->push_back({     0,   255,  32 });
		p->push_back({     0,   255,  64 });
		p->push_back({     0,   255,  96 });
		p->push_back({     0,   255, 128 });
		p->push_back({     0,   255, 160 });
		p->push_back({     0,   255, 192 });
		p->push_back({     0,   255, 224 });
		p->push_back({     0,   130, 255 }); // #32
		p->push_back({     0,   114, 255 });
		p->push_back({     0,   104, 255 });
		p->push_back({    10,    96, 255 });
		p->push_back({     0,    82, 255 });
		p->push_back({     0,    74, 255 });
		p->push_back({     0,    64, 255 });
		p->push_back({     0,    32, 255 });
		p->push_back({     0,     0, 255 }); // #40
		p->push_back({    32,     0, 255 });
		p->push_back({    64,     0, 255 });
		p->push_back({    96,     0, 255 });
		p->push_back({   128,     0, 255 });
		p->push_back({   160,     0, 255 });
		p->push_back({   192,     0, 255 });
		p->push_back({   224,     0, 255 });
		p->push_back({   255,     0, 255 }); // #48
		p->push_back({   255,    32, 255 });
		p->push_back({   255,    64, 255 });
		p->push_back({   255,    96, 255 });
		p->push_back({   255,   128, 255 });
		p->push_back({   255,   160, 255 });
		p->push_back({   255,   192, 255 });
		p->push_back({   255,   224, 255 });
		p->push_back({   255,   255, 255 }); // #56
		p->push_back({   255,   224, 224 });
		p->push_back({   255,   255, 255 });
		p->push_back({   255,   160, 160 });
		p->push_back({   255,   128, 128 });
		p->push_back({   255,    96,  96 });
		p->push_back({   255,    64,  64 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 }); // #64
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 }); // #96
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 }); // #128
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 }); // #160
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 }); // #192
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 }); // #224
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
		p->push_back({   255,    32,  32 });
	}
	return *p;
}
static vector<ofColor>& ilda_alt_color_palette(){
	static std::unique_ptr<vector<ofColor>> p;
	if(!p){
		p = std::make_unique< vector<ofColor> >();
		
		p->push_back({   0,   0,   0 });	// Black/blanked (fixed)
		p->push_back({ 255, 255, 255 });	// White (fixed)
		p->push_back({ 255,   0,   0 });  // Red (fixed)
		p->push_back({ 255, 255,   0 });  // Yellow (fixed)
		p->push_back({   0, 255,   0 });  // Green (fixed)
		p->push_back({   0, 255, 255 });  // Cyan (fixed)
		p->push_back({   0,   0, 255 });  // Blue (fixed)
		p->push_back({ 255,   0, 255 });  // Magenta (fixed)
		p->push_back({ 255, 128, 128 });  // Light red
		p->push_back({ 255, 140, 128 });
		p->push_back({ 255, 151, 128 });
		p->push_back({ 255, 163, 128 });
		p->push_back({ 255, 174, 128 });
		p->push_back({ 255, 186, 128 });
		p->push_back({ 255, 197, 128 });
		p->push_back({ 255, 209, 128 });
		p->push_back({ 255, 220, 128 });
		p->push_back({ 255, 232, 128 });
		p->push_back({ 255, 243, 128 });
		p->push_back({ 255, 255, 128 });	// Light yellow
		p->push_back({ 243, 255, 128 });
		p->push_back({ 232, 255, 128 });
		p->push_back({ 220, 255, 128 });
		p->push_back({ 209, 255, 128 });
		p->push_back({ 197, 255, 128 });
		p->push_back({ 186, 255, 128 });
		p->push_back({ 174, 255, 128 });
		p->push_back({ 163, 255, 128 });
		p->push_back({ 151, 255, 128 });
		p->push_back({ 140, 255, 128 });
		p->push_back({ 128, 255, 128 });	// Light green
		p->push_back({ 128, 255, 140 });
		p->push_back({ 128, 255, 151 });
		p->push_back({ 128, 255, 163 });
		p->push_back({ 128, 255, 174 });
		p->push_back({ 128, 255, 186 });
		p->push_back({ 128, 255, 197 });
		p->push_back({ 128, 255, 209 });
		p->push_back({ 128, 255, 220 });
		p->push_back({ 128, 255, 232 });
		p->push_back({ 128, 255, 243 });
		p->push_back({ 128, 255, 255 });	// Light cyan
		p->push_back({ 128, 243, 255 });
		p->push_back({ 128, 232, 255 });
		p->push_back({ 128, 220, 255 });
		p->push_back({ 128, 209, 255 });
		p->push_back({ 128, 197, 255 });
		p->push_back({ 128, 186, 255 });
		p->push_back({ 128, 174, 255 });
		p->push_back({ 128, 163, 255 });
		p->push_back({ 128, 151, 255 });
		p->push_back({ 128, 140, 255 });
		p->push_back({ 128, 128, 255 });	// Light blue
		p->push_back({ 140, 128, 255 });
		p->push_back({ 151, 128, 255 });
		p->push_back({ 163, 128, 255 });
		p->push_back({ 174, 128, 255 });
		p->push_back({ 186, 128, 255 });
		p->push_back({ 197, 128, 255 });
		p->push_back({ 209, 128, 255 });
		p->push_back({ 220, 128, 255 });
		p->push_back({ 232, 128, 255 });
		p->push_back({ 243, 128, 255 });
		p->push_back({ 255, 128, 255 }); // Light magenta
		p->push_back({ 255, 128, 243 });
		p->push_back({ 255, 128, 232 });
		p->push_back({ 255, 128, 220 });
		p->push_back({ 255, 128, 209 });
		p->push_back({ 255, 128, 197 });
		p->push_back({ 255, 128, 186 });
		p->push_back({ 255, 128, 174 });
		p->push_back({ 255, 128, 163 });
		p->push_back({ 255, 128, 151 });
		p->push_back({ 255, 128, 140 });
		p->push_back({ 255,   0,   0 });	// Red (cycleable)
		p->push_back({ 255,  23,   0 });
		p->push_back({ 255,  46,   0 });
		p->push_back({ 255,  70,   0 });
		p->push_back({ 255,  93,   0 });
		p->push_back({ 255, 116,   0 });
		p->push_back({ 255, 139,   0 });
		p->push_back({ 255, 162,   0 });
		p->push_back({ 255, 185,   0 });
		p->push_back({ 255, 209,   0 });
		p->push_back({ 255, 232,   0 });
		p->push_back({ 255, 255,   0 });	//Yellow (cycleable)
		p->push_back({ 232, 255,   0 });
		p->push_back({ 209, 255,   0 });
		p->push_back({ 185, 255,   0 });
		p->push_back({ 162, 255,   0 });
		p->push_back({ 139, 255,   0 });
		p->push_back({ 116, 255,   0 });
		p->push_back({  93, 255,   0 });
		p->push_back({  70, 255,   0 });
		p->push_back({  46, 255,   0 });
		p->push_back({  23, 255,   0 });
		p->push_back({   0, 255,   0 });	// Green (cycleable)
		p->push_back({   0, 255,  23 });
		p->push_back({   0, 255,  46 });
		p->push_back({   0, 255,  70 });
		p->push_back({   0, 255,  93 });
		p->push_back({   0, 255, 116 });
		p->push_back({   0, 255, 139 });
		p->push_back({   0, 255, 162 });
		p->push_back({   0, 255, 185 });
		p->push_back({   0, 255, 209 });
		p->push_back({   0, 255, 232 });
		p->push_back({   0, 255, 255 });	// Cyan (cycleable)
		p->push_back({   0, 232, 255 });
		p->push_back({   0, 209, 255 });
		p->push_back({   0, 185, 255 });
		p->push_back({   0, 162, 255 });
		p->push_back({   0, 139, 255 });
		p->push_back({   0, 116, 255 });
		p->push_back({   0,  93, 255 });
		p->push_back({   0,  70, 255 });
		p->push_back({   0,  46, 255 });
		p->push_back({   0,  23, 255 });
		p->push_back({   0,   0, 255 });	// Blue (cycleable)
		p->push_back({  23,   0, 255 });
		p->push_back({  46,   0, 255 });
		p->push_back({  70,   0, 255 });
		p->push_back({  93,   0, 255 });
		p->push_back({ 116,   0, 255 });
		p->push_back({ 139,   0, 255 });
		p->push_back({ 162,   0, 255 });
		p->push_back({ 185,   0, 255 });
		p->push_back({ 209,   0, 255 });
		p->push_back({ 232,   0, 255 });
		p->push_back({ 255,   0, 255 });	// Magenta (cycleable)
		p->push_back({ 255,   0, 232 });
		p->push_back({ 255,   0, 209 });
		p->push_back({ 255,   0, 185 });
		p->push_back({ 255,   0, 162 });
		p->push_back({ 255,   0, 139 });
		p->push_back({ 255,   0, 116 });
		p->push_back({ 255,   0,  93 });
		p->push_back({ 255,   0,  70 });
		p->push_back({ 255,   0,  46 });
		p->push_back({ 255,   0,  23 });
		p->push_back({ 128,   0,   0 });	// Dark red
		p->push_back({ 128,  12,   0 });
		p->push_back({ 128,  23,   0 });
		p->push_back({ 128,  35,   0 });
		p->push_back({ 128,  47,   0 });
		p->push_back({ 128,  58,   0 });
		p->push_back({ 128,  70,   0 });
		p->push_back({ 128,  81,   0 });
		p->push_back({ 128,  93,   0 });
		p->push_back({ 128, 105,   0 });
		p->push_back({ 128, 116,   0 });
		p->push_back({ 128, 128,   0 });	// Dark yellow
		p->push_back({ 116, 128,   0 });
		p->push_back({ 105, 128,   0 });
		p->push_back({  93, 128,   0 });
		p->push_back({  81, 128,   0 });
		p->push_back({  70, 128,   0 });
		p->push_back({  58, 128,   0 });
		p->push_back({  47, 128,   0 });
		p->push_back({  35, 128,   0 });
		p->push_back({  23, 128,   0 });
		p->push_back({  12, 128,   0 });
		p->push_back({   0, 128,   0 });	// Dark green
		p->push_back({   0, 128,  12 });
		p->push_back({   0, 128,  23 });
		p->push_back({   0, 128,  35 });
		p->push_back({   0, 128,  47 });
		p->push_back({   0, 128,  58 });
		p->push_back({   0, 128,  70 });
		p->push_back({   0, 128,  81 });
		p->push_back({   0, 128,  93 });
		p->push_back({   0, 128, 105 });
		p->push_back({   0, 128, 116 });
		p->push_back({   0, 128, 128 });	// Dark cyan
		p->push_back({   0, 116, 128 });
		p->push_back({   0, 105, 128 });
		p->push_back({   0,  93, 128 });
		p->push_back({   0,  81, 128 });
		p->push_back({   0,  70, 128 });
		p->push_back({   0,  58, 128 });
		p->push_back({   0,  47, 128 });
		p->push_back({   0,  35, 128 });
		p->push_back({   0,  23, 128 });
		p->push_back({   0,  12, 128 });
		p->push_back({   0,   0, 128 });	// Dark blue
		p->push_back({  12,   0, 128 });
		p->push_back({  23,   0, 128 });
		p->push_back({  35,   0, 128 });
		p->push_back({  47,   0, 128 });
		p->push_back({  58,   0, 128 });
		p->push_back({  70,   0, 128 });
		p->push_back({  81,   0, 128 });
		p->push_back({  93,   0, 128 });
		p->push_back({ 105,   0, 128 });
		p->push_back({ 116,   0, 128 });
		p->push_back({ 128,   0, 128 });	// Dark magenta
		p->push_back({ 128,   0, 116 });
		p->push_back({ 128,   0, 105 });
		p->push_back({ 128,   0,  93 });
		p->push_back({ 128,   0,  81 });
		p->push_back({ 128,   0,  70 });
		p->push_back({ 128,   0,  58 });
		p->push_back({ 128,   0,  47 });
		p->push_back({ 128,   0,  35 });
		p->push_back({ 128,   0,  23 });
		p->push_back({ 128,   0,  12 });
		p->push_back({ 255, 192, 192 });	// Very light red
		p->push_back({ 255,  64,  64 });	// Light-medium red
		p->push_back({ 192,   0,   0 });	// Medium-dark red
		p->push_back({  64,   0,   0 });	// Very dark red
		p->push_back({ 255, 255, 192 });	// Very light yellow
		p->push_back({ 255, 255,  64 });	// Light-medium yellow
		p->push_back({ 192, 192,   0 });	// Medium-dark yellow
		p->push_back({  64,  64,   0 });	// Very dark yellow
		p->push_back({ 192, 255, 192 });	// Very light green
		p->push_back({  64, 255,  64 });	// Light-medium green
		p->push_back({   0, 192,   0 });	// Medium-dark green
		p->push_back({   0,  64,   0 });	// Very dark green
		p->push_back({ 192, 255, 255 });	// Very light cyan
		p->push_back({  64, 255, 255 });	// Light-medium cyan
		p->push_back({   0, 192, 192 });	// Medium-dark cyan
		p->push_back({   0,  64,  64 });	// Very dark cyan
		p->push_back({ 192, 192, 255 });	// Very light blue
		p->push_back({  64,  64, 255 });	// Light-medium blue
		p->push_back({   0,   0, 192 });	// Medium-dark blue
		p->push_back({   0,   0,  64 });	// Very dark blue
		p->push_back({ 255, 192, 255 });	// Very light magenta
		p->push_back({ 255,  64, 255 });	// Light-medium magenta
		p->push_back({ 192,   0, 192 });	// Medium-dark magenta
		p->push_back({  64,   0,  64 });	// Very dark magenta
		p->push_back({ 255,  96,  96 });	// Medium skin tone
		p->push_back({ 255, 255, 255 });	// White (cycleable)
		p->push_back({ 245, 245, 245 });
		p->push_back({ 235, 235, 235 });
		p->push_back({ 224, 224, 224 });	// Very light gray (7/8 intensity)
		p->push_back({ 213, 213, 213 });
		p->push_back({ 203, 203, 203 });
		p->push_back({ 192, 192, 192 });	// Light gray (3/4 intensity)
		p->push_back({ 181, 181, 181 });
		p->push_back({ 171, 171, 171 });
		p->push_back({ 160, 160, 160 });	// Medium-light gray (5/8 int.)
		p->push_back({ 149, 149, 149 });
		p->push_back({ 139, 139, 139 });
		p->push_back({ 128, 128, 128 });	// Medium gray (1/2 intensity)
		p->push_back({ 117, 117, 117 });
		p->push_back({ 107, 107, 107 });
		p->push_back({  96,  96,  96 });	// Medium-dark gray (3/8 int.)
		p->push_back({  85,  85,  85 });
		p->push_back({  75,  75,  75 });
		p->push_back({  64,  64,  64 });	// Dark gray (1/4 intensity)
		p->push_back({  53,  53,  53 });
		p->push_back({  43,  43,  43 });
		p->push_back({  32,  32,  32 });	// Very dark gray (1/8 intensity)
		p->push_back({  21,  21,  21 });
		p->push_back({  11,  11,  11 });
		p->push_back({   0,   0,   0 });	// Black
	}
	return *p;
}
	
