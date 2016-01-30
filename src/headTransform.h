/*
 * headTransform.h
 *
 *  Created on: Feb 24, 2015
 *      Author: dantheman
 */

#pragma once
#include "ofMain.h"

class headTransform {
public:
	headTransform();
	virtual ~headTransform();
	ofMatrix4x4 getHeadView();
	void setMatrix(ofMatrix4x4 mat);
	void getTranslation(vector<float>& translation, int offset);
	void getForwardVector(vector<float>& forward, int offset);
	void getUpVector(vector<float>& up, int offset);
	void getRightVector(vector<float> &right, int offset);
	ofQuaternion getQuaternion();
	ofVec3f getEulerAngles();
private:
	ofMatrix4x4 mHeadView;
    ofQuaternion mQuaternion;
};


