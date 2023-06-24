#pragma once


//#define OFX_DEPTH_CAMERA_ASUS_PRO_V1


#include "ofMain.h"
#include "ofxDepthCamera.h"


class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void dragEvent(ofDragInfo dragInfo);

	ofxDepthCamera device;

};
