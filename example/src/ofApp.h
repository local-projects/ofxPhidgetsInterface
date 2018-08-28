#pragma once

#include "ofMain.h"
#include "ofxPhidgetsInterface.h"

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
    
    vector<ofxPhidgetsInterface *> motionSensors;
    void onReceivedMotion(ofxPhidgetsInterface::MotionData &data);
    
    int chanel1 = 3;
    int chanel2 = 1;
    int numSensors = 2;
    
     vector<ofxPhidgetsInterface *> digitalOutputs;
    int chanel1_digital = 2;
    int chanel2_digital = 5;
    
    //float interval =
};
