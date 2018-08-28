#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetBackgroundColor(ofColor::black);
    
    
    
    ofxPhidgetsInterface * motionSensor = new ofxPhidgetsInterface();
    
    //int phidgetSerialNumber, bool isHubDevice, int timeoutDuration, int channel, double _notificationVal
    motionSensor->setup(529937, true, 5000, chanel1, 0.01);
    motionSensor->setUID(ofToString(chanel1));
    ofAddListener(motionSensor->sensorTrigger, this, &ofApp::onReceivedMotion);
    
    motionSensors.push_back(motionSensor);
    
    ofxPhidgetsInterface * motionSensor2 = new ofxPhidgetsInterface();
    
    //int phidgetSerialNumber, bool isHubDevice, int timeoutDuration, int channel, double _notificationVal
    motionSensor2->setup(529937, true, 5000, chanel2, 0.01);
    motionSensor2->setUID(ofToString(chanel2));
    ofAddListener(motionSensor2->sensorTrigger, this, &ofApp::onReceivedMotion);
    
    motionSensors.push_back(motionSensor2);
    
    ofxPhidgetsInterface * digitalOutput = new ofxPhidgetsInterface();
    //void setupDigital(int phidgetSerialNumber, bool isHubDevice, int timeoutDuration, int channel);
    digitalOutput->setupDigital(529937, true, 5000, chanel1_digital);
    digitalOutput->setUID(ofToString(chanel1_digital));
    
    ofxPhidgetsInterface * digitalOutput2 = new ofxPhidgetsInterface();
    //void setupDigital(int phidgetSerialNumber, bool isHubDevice, int timeoutDuration, int channel);
    digitalOutput2->setupDigital(529937, true, 5000, chanel2_digital);
    digitalOutput2->setUID(ofToString(chanel2_digital));
    
    digitalOutputs.push_back(digitalOutput);
    digitalOutputs.push_back(digitalOutput2);
    
}

//--------------------------------------------------------------
void ofApp::update(){

    for(auto & motionSensor: motionSensors)
    {
        motionSensor->update();
    }
    
    for(auto & digitalOutput: digitalOutputs)
    {
        digitalOutput->updateDigitalOutput();
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    float width = (ofGetWidth() - 100) / numSensors;
    for(int i = 0; i < motionSensors.size() ; i++)
    {
        
        motionSensors[i]->drawDebug(ofVec2f(width*i, ofGetHeight()/2));
    }
}

#pragma mark CALL BACKS

void ofApp::onReceivedMotion(ofxPhidgetsInterface::MotionData &data){
    ofLogNotice("ofApp::onReceivedMotion") << data.UID << ": " << data.val;
}

#pragma mark OF INTERACTIONS

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key)
    {
            case '1':
        {
            digitalOutputs[0]->turnDeviceOn(interval);
            break;
        }
            case '2':
        {
            digitalOutputs[1]->turnDeviceOn(interval);
            break;
        }
        default: break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
