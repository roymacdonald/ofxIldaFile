#pragma once

#include "ofMain.h"
#include "ofxIldaFileDirectory.h"
#include "ofxSvg.h"
class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
	
		ofxIldaFileDirectory ildaDir;
			ofxSVG svg;
	void loadSvg();
	
	
	size_t index = 0, vertIndex = 0, polyIndex = 0;
	
	std::vector <ofPath> paths;

	vector<ofPolyline> polys;
	vector<glm::vec3> closePoints, openPoints;
	ofEasyCam cam;
};
