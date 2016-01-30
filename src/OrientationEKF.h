//
//  OrientationEKF.h
//  CardboardSDK-iOS
//

#pragma once
#include "ofMain.h"
#include "Vector3d.h"
#include "Matrix3x3d.h"


class OrientationEKF
{
  public:
    OrientationEKF();
    virtual ~OrientationEKF();
    
    void reset();
    bool isReady();
    
    void processGyro(ofVec3f gyro, double sensorTimeStamp);
    void processAcceleration(ofVec3f acc, double sensorTimeStamp);
    
    double getHeadingDegrees();
    void setHeadingDegrees(double heading);
    
    ofMatrix4x4 getGLMatrix();
    ofMatrix4x4 getPredictedGLMatrix(double secondsAfterLastGyroEvent);
    ofMatrix4x4 glMatrixFromSo3(Matrix3x3d *so3);
    
  private:
    Matrix3x3d _so3SensorFromWorld;
    Matrix3x3d _so3LastMotion;
    Matrix3x3d _mP;
    Matrix3x3d _mQ;
    Matrix3x3d _mR;
    Matrix3x3d _mRAcceleration;
    Matrix3x3d _mS;
    Matrix3x3d _mH;
    Matrix3x3d _mK;
    Vector3d _vNu;
    Vector3d _vZ;
    Vector3d _vH;
    Vector3d _vU;
    Vector3d _vX;
    Vector3d _vDown;
    Vector3d _vNorth;
    double _sensorTimeStampGyro;
    ofVec3f _lastGyro;
    double _previousAccelNorm;
    double _movingAverageAccelNormChange;
    double _filteredGyroTimestep;
    bool _timestepFilterInit;
    int _numGyroTimestepSamples;
    bool _gyroFilterValid;
    bool _alignedToGravity;
    bool _alignedToNorth;
    
    void filterGyroTimestep(double timestep);
    void updateCovariancesAfterMotion();
    void updateAccelerationCovariance(double currentAccelNorm);
    void accelerationObservationFunctionForNumericalJacobian(Matrix3x3d *so3SensorFromWorldPred, Vector3d *result);
};
