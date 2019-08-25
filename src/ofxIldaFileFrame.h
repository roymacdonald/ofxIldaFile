//
//  ofxIlda::FileFrame.hpp
//  example
//
//  Created by Roy Macdonald on 7/20/19.
//
//

#pragma once
#include "ofMain.h"
#include "ofxIldaFileUtils.h"
#include "ofxIldaFileColorPalette.h"
#include "ofxIldaFileConstants.h"
#define OFX_ILDA_FILE_FRAME_DEBUG

namespace ofxIlda{
	class FileFrame{
	public:
		friend class File;
		FileFrame(){}
		FileFrame(const ofxIlda::FileFormat& format, const string& frameName, const string& companyName);
		
		void setup(const ofxIlda::FileFormat& format, const string& frameName, const string& companyName);
		
		void addPoint(glm::vec3 point, const ofColor& color, bool bIsNormalized );
		
		bool readFromBuffer(ofBuffer& buffer, size_t startIndex);
		
		void writeToBuffer(ofBuffer& buffer);
		
		const ofxIlda::FileFormat& getFormat() const;
		const string& getFrameName() const;
		const string& getCompanyName() const;
		size_t  getNumPoints()  const;
		const size_t& getFrameNumber() const;
		const size_t& getTotalFrames() const;
		
		const char& getScanner() const;
		const size_t& getStartIndex() const;
		
		size_t getDataSize();
		
		int getNumDataBytesForFormat();
		
		//	bool isDataNormalized();
		
		friend std::ostream& operator << (std::ostream& os, const ofxIlda::FileFrame& f);
		
//		static void normalizePoint(glm::vec3& point);
//		static void unnormalizePoint(glm::vec3& point);
//		
//		
		string getAsString();
		bool bFrameSet = false;
		
		static ofxIlda::FileFrame getEndFrame(const ofxIlda::FileFrame& refFrame);
		
		ofMesh path, normalizedPath;
		
		
		void resetPaths();
		
		static bool validateFormat(const int& format);
		
#ifdef OFX_ILDA_FILE_FRAME_DEBUG
		std::map<size_t, size_t > endsMap;
		std::map<size_t, size_t > repVMap;
#endif
		
	protected:
		
		
		
		
		size_t readHeader(ofBuffer& buffer, size_t startIndex);
		//	void decodeData(char * d, size_t num_points, size_t size, bool bNormalize = true);
		void decodeData(ofBuffer& buffer, size_t num_points);
		
		void writeHeader(ofBuffer& buffer);
		void encodeData(ofBuffer& buffer);
		
		
		
		//	void readStatusCode(char * d, size_t i);
		int getColorOffset();
		int getStatusCodeOffset();
		
		ofxIlda::FileFormat format;
		string frame_name;
		string company_name;
		//	size_t point_number;
		size_t frame_number = 0;
		size_t total_frame = 0;
		
		char scanner = 0;
		size_t start_id = 0;
		
		
		//	bool bNormalizedData;
		
	};
}
