//
//  ofxPhidgetsInterface.cpp
//  example
//
//  Created by Nicole Messier on 6/21/18.
//
//

#include "ofMain.h"
#include <phidget22.h>
#include <Common/PhidgetHelperFunctions.h>

class ofxPhidgetsInterface{
protected:
    /*
     SOME NOTES ON PHIDGETS:
     
     * Helpful link: https://www.phidgets.com/docs/Phidget_Programming_Basics
     
     * CCONV stands for "Calling Convention", and it's just a defined term in our libraries that makes sure the function is called with the proper prefix for the compiler that's being used. You can find CCONV defined in phidget22.h
     
     */
    static void CCONV onAttachHandler(PhidgetHandle ph, void *ctx);
    static void CCONV onDetachHandler(PhidgetHandle ph, void *ctx);
    static void CCONV onErrorHandler(PhidgetHandle phid, void *ctx, Phidget_ErrorEventCode errorCode, const char *errorString);
    static void CCONV onVoltageRatioChangeHandler(PhidgetVoltageRatioInputHandle pvih, void *ctx, double voltage);
    static void CCONV onSensorChangeHandler(PhidgetVoltageRatioInputHandle pvih, void *ctx, double sensorValue, Phidget_UnitInfo *unitInfo);
    void PrintEventDescriptions();
    static void CCONV onVoltageChangeHandler(PhidgetVoltageRatioInputHandle voltageInput, void *ctx, double voltage);
    
public:
    ofxPhidgetsInterface();
    ~ofxPhidgetsInterface();
    
    void setup(int phidgetSerialNumber, bool isHubDevice, int timeoutDuration, int channel, double _notificationVal);
    void update();
    
    //UID
    string getUID();
    void setUID(string _uid);
    
    struct MotionData{
        double val;
        string UID;
    };
    
    ofEvent<MotionData> sensorTrigger;
    
private:
    PhidgetVoltageRatioInputHandle ch = NULL;
    double notificationVal; //any val below this will send a notification
    
     //UID
    string UID = "";
};