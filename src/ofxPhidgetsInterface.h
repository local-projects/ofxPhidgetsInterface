//
//  ofxPhidgetsInterface.cpp
//  example
//
//  Created by Nicole Messier on 6/21/18.
//
//

#include "ofMain.h"
#include <phidget22.h>
#include <PhidgetHelperFunctions.h>

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
    void setupDigital(int phidgetSerialNumber, bool isHubDevice, int timeoutDuration, int channel);
    void update();
    void drawDebug(ofVec2f pos);
    
    //UID
    string getUID();
    void setUID(string _uid);
    
    struct MotionData{
        double val;
        string UID;
    };
    
    ofEvent<ofxPhidgetsInterface::MotionData> sensorTrigger;
    
    // NOTIFICATION VAL
    void setNotificationVal(double _notificationVal);
    double getNotificationVal();
    
    //Digital control
    void updateDigitalOutput();
    void turnDeviceOn(float _interval);
    void turnDeviceOff();
    ofEvent<ofxPhidgetsInterface::MotionData> turnOffTrigger;
    bool getDeviceIsOn();
    // END DIGITAL Digital control
    
    // DATA ///////////
    
    void setDataInterval(int interval);
    
    //raw data
    /*
     returns the single raw data value
     */
    double getRawData();
    void storeRawDataPoints();
    
    //average
    double getAverageValue();
    void setNumAverageDataPoints(int _numAverageDataPoints);
    void calculateAverage();
    
    // filtered based on moving average
    void calculateMovingAverage();
    double getSensorValFromMovingAverage();
    void setSpikeAmp(double _spikeAmplitude);
    
    // number of data points for filtering and averages
    void setNumRawDataPoints(int _numRawDataPoints);
    
private:
    PhidgetVoltageRatioInputHandle ch = NULL;
    PhidgetDigitalOutputHandle dig = NULL;
    
    double notificationVal; //any val below this will send a notification
    
     //UID
    string UID = "";
    
    //value
    double val;
    
    // is this a digital control
    bool digitalControl = false;
    bool deviceIsOn = false;
    float startTime = 0.0f;
    float interval  = 1.0f;
    
    // DATA ///////////
    
    //raw data
    vector<double> storedRawData;
    int dataPointCounter = 0; //this is to keep track of where to store the next raw data point
    
    //average
    double averageVal = 0;
    int numAverageDataPoints = 10;
    vector<double> storedRawData_average;
    int dataPointCounter_average = 0;
    
    // filtered based on moving average
    double spikeAmplitude = 0.3;
    double sensorVal_movingData = 0;
    
    // number of data points for filtering and averages
    int numRawDataPoints = 10;

};