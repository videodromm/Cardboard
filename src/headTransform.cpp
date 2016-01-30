/*
 * headTransform.cpp
 *
 *  Created on: Feb 24, 2015
 *      Author: dantheman
 */

#include "headTransform.h"
float GIMBAL_LOCK_EPSILON = 0.01F;
headTransform::~headTransform() {
	// TODO Auto-generated destructor stub
}

headTransform::headTransform() {
    mHeadView.makeIdentityMatrix();
}

void headTransform::setMatrix(ofMatrix4x4 mat){
    mHeadView = mat;
}

ofMatrix4x4 headTransform::getHeadView()
{
	return mHeadView;
}

void headTransform::getTranslation(vector<float>& translation, int offset)
{
	for (int i = 0; i < 3; i++){
		translation[(i + offset)] = mHeadView.getPtr()[(12 + i)];
	}
}

void headTransform::getForwardVector(vector<float>& forward, int offset)
{
	for (int i = 0; i < 3; i++){
		forward[(i + offset)] = (-mHeadView.getPtr()[(8 + i)]);
	}
}

void headTransform::getUpVector(vector<float>& up, int offset)
{
	for (int i = 0; i < 3; i++)
	up[(i + offset)] = mHeadView.getPtr()[(4 + i)];
}

void headTransform::getRightVector(vector<float> &right, int offset)
{


	for (int i = 0; i < 3; i++)
	right[(i + offset)] = mHeadView.getPtr()[i];
}

ofQuaternion headTransform::getQuaternion()
{
    mQuaternion.set(mHeadView);
//    float * ptr = mat.getPtr();
//	float * m = mHeadView.getPtr();
//	float t = m[0] + m[5] + m[10];
//	float s, w, x, y, z;
//	if (t >= 0.0F) {
//		s = sqrt(t + 1.0F);
//		w = 0.5F * s;
//		s = 0.5F / s;
//		x = (m[9] - m[6]) * s;
//		y = (m[2] - m[8]) * s;
//		z = (m[4] - m[1]) * s;
//	}
//	else
//	{
//		if ((m[0] > m[5]) && (m[0] > m[10])) {
//			s = sqrt(1.0F + m[0] - m[5] - m[10]);
//			x = s * 0.5F;
//			s = 0.5F / s;
//			y = (m[4] + m[1]) * s;
//			z = (m[2] + m[8]) * s;
//			w = (m[9] - m[6]) * s;
//		}
//		else
//		{
//			if (m[5] > m[10]) {
//				s = sqrt(1.0F + m[5] - m[0] - m[10]);
//				y = s * 0.5F;
//				s = 0.5F / s;
//				x = (m[4] + m[1]) * s;
//				z = (m[9] + m[6]) * s;
//				w = (m[2] - m[8]) * s;
//			}
//			else {
//				s = sqrt(1.0F + m[10] - m[0] - m[5]);
//				z = s * 0.5F;
//				s = 0.5F / s;
//				x = (m[2] + m[8]) * s;
//				y = (m[9] + m[6]) * s;
//				w = (m[4] - m[1]) * s;
//			}
//		}
//	}
//	ptr[(offset + 0)] = x;
//	ptr[(offset + 1)] = y;
//	ptr[(offset + 2)] = z;
//	ptr[(offset + 3)] = w;
//    
//    quaternion.set(mat);
    
    return mQuaternion;
}

ofVec3f headTransform::getEulerAngles()
{
//	float yaw, roll, pitch = (float)asin(mHeadView.getPtr()[6]);
//	if (sqrt(1.0F - mHeadView.getPtr()[6] * mHeadView.getPtr()[6]) >= 0.01)
//	{
//		yaw = (float)atan2(-mHeadView.getPtr()[2], mHeadView.getPtr()[10]);
//		roll = (float)atan2(-mHeadView.getPtr()[4], mHeadView.getPtr()[5]);
//	}
//	else
//	{
//		yaw = 0.0F;
//		roll = (float)atan2(mHeadView.getPtr()[1], mHeadView.getPtr()[0]);
//	}
    
    mQuaternion.set(mHeadView);
//
//    ofVec3f eulerAngles;
//	eulerAngles.x = (-pitch);
//	eulerAngles.y = (-yaw);
//	eulerAngles.z = (-roll);
    return mQuaternion.getEuler();
}

