//
//  ildaFileUtils.h
//  ildaFileDecode
//
//  Created by Roy Macdonald on 7/20/19.
//
//

#pragma once
#include "ofxIldaFileConstants.h"
#include "ofxIldaPoint.h"
namespace ofxIlda{
	
	//--------------------------------------------------------------
	static void normalizePoint(glm::vec3& point){
		point.x = ofMap(point.x, -32768, 32767, -1, 1);
		point.y = ofMap(point.y, -32768, 32767, -1, 1);
		point.z = ofMap(point.z, -32768, 32767, -1, 1);
		
	}
	//--------------------------------------------------------------
	static void unnormalizePoint(glm::vec3& point){
		point.x = ofMap(point.x, -1, 1, -32768, 32767);
		point.y = ofMap(point.y, -1, 1, -32768, 32767);
		point.z = ofMap(point.z, -1, 1, -32768, 32767);
		
	}
	//--------------------------------------------------------------
	inline short getShortFromChars(char* b, size_t index){
		return ((b[index] & 0xFF) << 8) | (b[index+1] & 0xFF);
	}
	//--------------------------------------------------------------
	inline void setShortIntoChars(vector<char>& b, short s, size_t index){
		b[index] = ((s >> 8) & 0xFF);
		b[index+1] = (s & 0xFF);
	}
	inline void incrementAndWrap(size_t& index,  const size_t& limit, int step = 1){
		if(limit == 0) return;
		index = (index+step)%limit;
	}
	inline void decrementAndWrap(size_t& index, const size_t& limit, int step = 1){
		if(step < limit){
			if(index == 0){
				index= limit - step;
			}else{
				index -= step ;
			}
		}
	}
	
	inline bool ifFormat3D(const ofxIlda::FileFormat& format){
		return (format == ofxIlda::FILE_FORMAT_3D_INDEXED_COLOR || format == ofxIlda::FILE_FORMAT_3D_TRUE_COLOR);
	}
	inline bool ifFormat2D(const ofxIlda::FileFormat& format){
		return (format == ofxIlda::FILE_FORMAT_2D_INDEXED_COLOR || format == ofxIlda::FILE_FORMAT_2D_INDEXED_COLOR);
	}
	
	inline bool ifFormatTrueColor(const ofxIlda::FileFormat& format){
		return (format == ofxIlda::FILE_FORMAT_3D_TRUE_COLOR || format == ofxIlda::FILE_FORMAT_2D_TRUE_COLOR);
	}
	inline bool ifFormatIndexedColor(const ofxIlda::FileFormat& format){
		return (format == ofxIlda::FILE_FORMAT_3D_INDEXED_COLOR || format == ofxIlda::FILE_FORMAT_2D_INDEXED_COLOR);
	}
	
	static ofRectangle getBoundingBox(const std::vector<ofPath>& paths){
		ofRectangle bb;
		bool bFirst = true;
		for(auto& p: paths){
			auto& ol = p.getOutline();
			for(auto& o: ol){
				auto& vt = o.getVertices();
				for(auto& v: vt){
					if(bFirst){
						bb.set(v, 0,0);
						bFirst = false;
					}else{
						bb.growToInclude(v);
					}
				}
			}
		}
		return bb;
	}
	static ofRectangle getBoundingBox(const ofPath & path){
		ofRectangle bb;
		bool bFirst = true;
		auto& ol = path.getOutline();
		for(auto& o: ol){
			auto& vt = o.getVertices();
			for(auto& v: vt){
				if(bFirst){
					bb.set(v, 0,0);
					bFirst = false;
				}else{
					bb.growToInclude(v);
				}
			}
		}
		
		return bb;
	}
	static ofRectangle getBoundingBox(const std::vector<ofPolyline> & polys){
		ofRectangle bb;
		bool bFirst = true;
		//	auto& ol = path.getOutline();
		for(auto& o: polys){
			auto& vt = o.getVertices();
			for(auto& v: vt){
				if(bFirst){
					bb.set(v, 0,0);
					bFirst = false;
				}else{
					bb.growToInclude(v);
				}
			}
		}
		
		return bb;
	}
	static ofRectangle getBoundingBox(const ofPolyline & poly){
		ofRectangle bb;
		bool bFirst = true;
		auto& vt = poly.getVertices();
		for(auto& v: vt){
			if(bFirst){
				bb.set(v, 0,0);
				bFirst = false;
			}else{
				bb.growToInclude(v);
			}
		}
		return bb;
	}
	static ofRectangle getBoundingBox(const ofMesh & mesh){
		ofRectangle bb;
		bool bFirst = true;
		auto& vt = mesh.getVertices();
		for(auto& v: vt){
			if(bFirst){
				bb.set(v, 0,0);
				bFirst = false;
			}else{
				bb.growToInclude(v);
			}
		}
		return bb;
	}
	static ofRectangle getBoundingBox(const std::vector<ofxIlda::Point> & points){
		ofRectangle bb;
		if(points.size()){
			bb.set(points[0].x,points[0].y,0,0);
			for(auto & p : points){
				bb.growToInclude(p.x, p.y);
			}
		}
		return bb;
	}
}
