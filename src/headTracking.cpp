/*
 * headTracking.cpp
 *
 *  Created on: Feb 24, 2015
 *      Author: dantheman
 */

#include "headTracking.h"

headTracking::headTracking() {

}

headTracking::~headTracking() {

}

void headTracking::setup() {

	mNeckModelTranslation.makeIdentityMatrix();
	mNeckModelTranslation.makeTranslationMatrix(ofVec3f(0.0, -0.075, 0.08));

	mNeckModelEnabled = false;
	reset();
}

ofMatrix4x4 headTracking::getLastHeadView(ofMatrix4x4 headView) {
	if (!mTracker.isReady()) {
		return headView;
	}
	ofOrientation fooRot = ofGetOrientation();
	double rotation = 0.0;
	if (fooRot == OF_ORIENTATION_DEFAULT) {
		rotation = 0.0;
	} else if (fooRot == OF_ORIENTATION_90_LEFT) {
		rotation = 90.0;
	} else if (fooRot == OF_ORIENTATION_90_RIGHT) {
		rotation = 180.0;
	} else {
		rotation = 270.0;
	}

	if (fooRot != mDisplayRotation) {
		mDisplayRotation = fooRot;

		mSensorToDisplay.makeRotationMatrix(
				ofQuaternion(0.0, ofVec3f(1, 0, 0), -rotation, ofVec3f(0, 0, 1),
						0.0, ofVec3f(0, 1, 0)));
		mEkfToHeadTracker.makeRotationMatrix(
				ofQuaternion(0.0, ofVec3f(1, 0, 0), rotation, ofVec3f(0, 0, 1),
						0.0, ofVec3f(0, 1, 0)));
	}
	double secondsSinceLastGyroEvent = (ofGetElapsedTimeMicros() - mLastGyroEventTimeNanos)*1E-6;


	double secondsToPredictForward = secondsSinceLastGyroEvent + 0.0166666666;
	mTmpHeadView = mTracker.getPredictedGLMatrix(secondsToPredictForward);
	mTmpHeadView2.makeFromMultiplicationOf(mSensorToDisplay, mTmpHeadView);
	headView.makeFromMultiplicationOf(mTmpHeadView2, mEkfToHeadTracker);

	if (mNeckModelEnabled) {
		mTmpHeadView.makeFromMultiplicationOf(mNeckModelTranslation, headView);
		mTmpHeadView.translate(ofVec3f(0, 0.075, 0.0));
		headView = mTmpHeadView;
	}
	return headView;
}

void headTracking::reset() {
	mTracker.reset();
}

void headTracking::processSensorEvent(SensorEvent event) {
	if (event.type == ACCEL) {
		mLatestAcc = event.reading;
		mTracker.processAcceleration(mLatestAcc, event.timestamp);
	} else if (event.type == GYRO) {
		mLastGyroEventTimeNanos = event.timestamp;
		mLatestGyro = event.reading;
		mTracker.processGyro(mLatestGyro, event.timestamp);
	}
}
