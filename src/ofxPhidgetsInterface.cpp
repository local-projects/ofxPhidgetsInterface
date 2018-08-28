//
//  ofxPhidgetsInterface.h
//  example
//
//  Created by Nicole Messier on 6/21/18.
//
//

#include "ofxPhidgetsInterface.h"

// -------------------- Event Functions ---------------------------------------

ofxPhidgetsInterface::ofxPhidgetsInterface(){
    
}

ofxPhidgetsInterface::~ofxPhidgetsInterface(){
    
}

void ofxPhidgetsInterface::setup(int phidgetSerialNumber, bool isHubDevice, int timeoutDuration, int channel, double _notificationVal){
    
    notificationVal = _notificationVal;
    

    /*
     * Allocate a new Phidget Channel object
     */
    
    PhidgetVoltageRatioInput_create(&ch);
    
    /*
     * Opening a VINT Hub Port as a Channel
     */
    
    Phidget_setDeviceSerialNumber((PhidgetHandle)ch, phidgetSerialNumber);
    Phidget_setIsHubPortDevice((PhidgetHandle)ch, isHubDevice);
    Phidget_setHubPort((PhidgetHandle)ch, channel);
    Phidget_openWaitForAttachment((PhidgetHandle)ch, timeoutDuration);

    
    /*
     * Listen to channel
     */
    Phidget_setOnAttachHandler((PhidgetHandle)ch, onAttachHandler, NULL);
    PhidgetVoltageRatioInput_setOnVoltageRatioChangeHandler(ch, onVoltageChangeHandler, NULL);
    //Phidget_setOnDetachHandler((PhidgetHandle)ch, onDetachHandler, NULL);
    
    digitalControl = false;
}

void ofxPhidgetsInterface::setupDigital(int phidgetSerialNumber, bool isHubDevice, int timeoutDuration, int channel){
    
    /*
     * Allocate a new Phidget Channel object
     */
    
    PhidgetDigitalOutput_create(&dig);
    
    /*
     * Opening a VINT Hub Port as a Channel
     */
    
    Phidget_setDeviceSerialNumber((PhidgetHandle)dig, phidgetSerialNumber);
    Phidget_setIsHubPortDevice((PhidgetHandle)dig, isHubDevice);
    Phidget_setHubPort((PhidgetHandle)dig, channel);
    Phidget_openWaitForAttachment((PhidgetHandle)dig, timeoutDuration);
    
    
    /*
     * Listen to channel
     */
    Phidget_setOnAttachHandler((PhidgetHandle)dig, onAttachHandler, NULL);
    //Phidget_setOnDetachHandler((PhidgetHandle)dig, onDetachHandler, NULL);
    double onOff = 0.0;
    PhidgetDigitalOutput_setDutyCycle(dig, onOff);

    digitalControl = true;
    
}

void ofxPhidgetsInterface::update(){
    //double val;
    PhidgetVoltageRatioInput_getVoltageRatio(ch, &val);
    //PhidgetVoltageRatioInput_getSensorValue(ch, &val);
    
    if(val<notificationVal && val != 0)
    {
        //ofLogNotice("ofxPhidgetsInterface::update") << "val: " << val;
        MotionData data;
        data.val = val;
        data.UID = UID;
        ofNotifyEvent(sensorTrigger, data, this);
    }
}

void ofxPhidgetsInterface::updateDigitalOutput()
{
    float timeElapsed = ofGetElapsedTimef() - startTime;
    
    if(deviceIsOn &&
       timeElapsed > interval)
    {
        ofLogNotice() << "timeElapsed: " << timeElapsed; 
        double onOff = 0.0;
        PhidgetDigitalOutput_setDutyCycle(dig, onOff);
        deviceIsOn = false;
    }
    
    if(deviceIsOn)
    {
         ofLogNotice() << "timeElapsed: " << timeElapsed;
    }
}

void ofxPhidgetsInterface::drawDebug(ofVec2f pos)
{
    ofSetColor(255, 0, 0);
    ofDrawBitmapString(UID + ": " + ofToString(val), pos.x, pos.y);
    ofSetColor(0, 0, 0); 
}


#pragma mark DIGITAL CONTROL 

void ofxPhidgetsInterface::turnDeviceOn(float _interval)
{
    double onOff = 1.0;
    PhidgetDigitalOutput_setDutyCycle(dig, onOff);
    deviceIsOn = true;
    interval = _interval;
    startTime = ofGetElapsedTimef(); 
}

void ofxPhidgetsInterface::turnDeviceOff()
{
    double onOff = 0.0;
    PhidgetDigitalOutput_setDutyCycle(dig, onOff);
    deviceIsOn = false;
}

#pragma mark UID
string ofxPhidgetsInterface::getUID(){
    return UID;
}

void ofxPhidgetsInterface::setUID(string _uid){
    UID = _uid; 
}

#pragma mark NOTIFICATIONVAL

void ofxPhidgetsInterface::setNotificationVal(double _notificationVal){
    notificationVal = _notificationVal;
}

#pragma mark PHIDGETS

/**
 * Configures the device's DataInterval and ChangeTrigger.
 * Displays info about the attached phidget channel.
 * Fired when a Phidget channel with onAttachHandler registered attaches
 *
 * @param ph The Phidget channel that fired the attach event
 * @param *ctx Context pointer
 */
void CCONV ofxPhidgetsInterface::onAttachHandler(PhidgetHandle ph, void *ctx) {
    Phidget_ChannelSubclass channelSubclass;
    PhidgetReturnCode prc;
    
    printf("\nAttach Event: ");

    
}

/**
 * Displays info about the detached phidget channel.
 * Fired when a Phidget channel with onDetachHandler registered detaches
 *
 * @param ph The Phidget channel that fired the detach event
 * @param *ctx Context pointer
 */
void CCONV ofxPhidgetsInterface::onDetachHandler(PhidgetHandle ph, void *ctx) {
    printf("\nDetach Event: ");
    PrintChannelInformaiton(ph);
}

/**
 * Writes phidget error info to stderr.
 * Fired when a Phidget channel with onErrorHandler registered encounters an error in the library
 *
 * @param ph The Phidget channel that fired the error event
 * @param *ctx Context pointer
 * @param errorCode the code associated with the error of enum type Phidget_ErrorEventCode
 * @param *errorString string containing the description of the error fired
 */
void CCONV ofxPhidgetsInterface::onErrorHandler(PhidgetHandle phid, void *ctx, Phidget_ErrorEventCode errorCode, const char *errorString) {
    
    fprintf(stderr, "[Phidget Error Event] -> %s (%d)\n", errorString, errorCode);
}

/**
 * Outputs the VoltageRatioInput's most recently reported voltage.
 * Fired when a VoltageRatioInput channel with onVoltageRatioChangeHandler registered meets DataInterval and ChangeTrigger criteria
 *
 * @param pvih The VoltageRatioInput channel that fired the VoltageRatioChange event
 * @param *ctx Context pointer
 * @param voltage The reported voltage from the VoltageRatioInput channel
 */
void CCONV ofxPhidgetsInterface::onVoltageRatioChangeHandler(PhidgetVoltageRatioInputHandle pvih, void *ctx, double voltage) {
    
    printf("[VoltageRatio Event] -> VoltageRatio: %.4f\n", voltage);
}

/**
 * Outputs the VoltageRatioInput's most recently reported sensor value.
 * Fired when a VoltageRatioInput channel with onSensorChangeHandler registered meets DataInterval and ChangeTrigger criteria
 *
 * @param pvih The VoltageRatioInput channel that fired the SensorChange event
 * @param *ctx Context pointer
 * @param sensorValue The reported sensor value from the VoltageRatioInput channel
 */
void CCONV ofxPhidgetsInterface::onSensorChangeHandler(PhidgetVoltageRatioInputHandle pvih, void *ctx, double sensorValue, Phidget_UnitInfo *unitInfo) {
    
    printf("[Sensor Event] -> Sensor Value: %.4f %s\n", sensorValue, unitInfo->symbol);
}

/**
 * Prints descriptions of the available events for this class
 */
void ofxPhidgetsInterface::PrintEventDescriptions() {
    
    printf("\n--------------------\n"
           "\n  | VoltageRatio change events will call their associated function every time new voltage data is received from the device.\n"
           "  | The rate of these events can be set by adjusting the DataInterval for the channel.\n");
    
    printf(
           "\n  | Sensor change events contain the most recent sensor value received from the device.\n"
           "  | Sensor change events will occur instead of VoltageRatio change events if the SensorType is changed from the default.\n"
           "  | Press ENTER once you have read this message.");
    getchar();
    
    printf("\n--------------------\n");
}

void CCONV ofxPhidgetsInterface::onVoltageChangeHandler(PhidgetVoltageRatioInputHandle voltageInput, void *ctx, double voltage){
    //printf("Voltage: %lf V\n", voltage);

}
