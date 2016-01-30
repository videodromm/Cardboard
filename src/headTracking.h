/*
 * headTracking.h
 *
 *  Created on: Feb 24, 2015
 *      Author: dantheman
 */

#pragma once
#include "ofMain.h"
#include "OrientationEKF.h"
#include "ofxAccelerometer.h"
//#include "GyroscopeBiasEstimator.h"
class headTracking {
public:
	headTracking();
	virtual ~headTracking();
	void setup();
	ofMatrix4x4 getLastHeadView(ofMatrix4x4 headView);
    void processSensorEvent(SensorEvent event);
//    void accelerationChanged(SensorEvent & event);
//    void gyroChanged(SensorEvent & event);
    void reset();
    void setGyroBias(ofVec3f bias);
    void setNeckModelEnabled(bool enable);
    OrientationEKF mTracker;
private:
    ofMatrix4x4 mEkfToHeadTracker;
    ofMatrix4x4 mSensorToDisplay;
    ofMatrix4x4 mNeckModelTranslation;
    ofMatrix4x4 mTmpHeadView;
    ofMatrix4x4 mTmpHeadView2;

    ofVec3f mTmpRotatedEvent;
    ofVec3f mLatestGyro;
    ofVec3f mLatestAcc;
    ofVec3f mGyroBias;

    ofOrientation mDisplayRotation;
    float DEFAULT_NECK_VERTICAL_OFFSET;
    unsigned long long mLastGyroEventTimeNanos;

    bool DEFAULT_NECK_MODEL_ENABLED;
    bool mNeckModelEnabled;
    bool mTracking;

    double currentRotation;
};

