#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    motionSensor = new ofxPhidgetsInterface();
    motionSensor->setup(529937, true, 5000, 5, 0.2);

    ofAddListener(motionSensor->sensorTrigger, this, &ofApp::onReceivedMotion); 
}

//--------------------------------------------------------------
void ofApp::update(){
    motionSensor->update(); 
}

//--------------------------------------------------------------
void ofApp::draw(){

}

#pragma mark CALL BACKS

void ofApp::onReceivedMotion(double &data){
    ofLogNotice("ofApp::onReceivedMotion") << "data: " << data;
}

#pragma mark OF INTERACTIONS

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
