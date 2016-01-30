#pragma once
#include "ofMain.h"
#include "ofxAndroid.h"
#include "headTracking.h"
#include "headTransform.h"
#include "ofxGameCamera.h"
#include "ofxAccelerometer.h"
class ofApp : public ofxAndroidApp{
	
	public:
		
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void windowResized(int w, int h);

		void touchDown(int x, int y, int id);
		void touchMoved(int x, int y, int id);
		void touchUp(int x, int y, int id);
		void touchDoubleTap(int x, int y, int id);
		void touchCancelled(int x, int y, int id);
		void swipe(ofxAndroidSwipeDir swipeDir, int id);

		void pause();
		void stop();
		void resume();
		void reloadTextures();

		bool backPressed();
		void okPressed();
		void cancelPressed();

		void accelerationChanged(SensorEvent & event);
		void gyroChanged(SensorEvent & event);
		void magChanged(SensorEvent & event);



		SensorEvent gyroEvent;
		SensorEvent accelEvent;
		ofTrueTypeFont font;
		headTracking tracking;
		headTransform transform;

		ofCamera cam;
		ofSpherePrimitive planet;

		ofNode node;
		ofNode invert;
		ofEasyCam easycam;
		ofMatrix4x4 view;

		ofQuaternion rot;
};


