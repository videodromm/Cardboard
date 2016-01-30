#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetOrientation(OF_ORIENTATION_90_LEFT);
	ofSetLogLevel(OF_LOG_VERBOSE);
	ofBackground(0, 0, 0);
	ofSetVerticalSync(true);
	ofSetFrameRate(60);

	planet.setUseVbo(false);
	planet.set(1500, 50);
	planet.setPosition(0, 0, 0);

	easycam.setDistance(20);
	cam.setPosition(0, 0, 0);

	ofxAccelerometer.setup();
	ofxRegisterAccelEvents(this);

	tracking.reset();
	invert = ofNode();
	node = ofNode();
	view = ofMatrix4x4();
}

void ofApp::accelerationChanged(SensorEvent & event) {
	accelEvent = event;
	tracking.processSensorEvent(accelEvent);
}

void ofApp::gyroChanged(SensorEvent & event) {
	gyroEvent = event;
	tracking.processSensorEvent(gyroEvent);
}
void ofApp::magChanged(SensorEvent & event) {
//	gyroEvent = event;

//tracking.processSensorEvent(event);
//	ofLog()<<"magChanged "<<event.reading<<endl;
}
//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	ofBackground(0, 0, 0);

	ofMatrix4x4 headView;
	headView.makeIdentityMatrix();
	headView = tracking.getLastHeadView(transform.getHeadView());
	ofDrawBitmapStringHighlight("Rot :" + ofToString(headView.getRotate()), 10,
			500);

//    ofMatrix4x4 translate;
//    translate.makeTranslationMatrix(ofVec3f(0.06, 0, 0));
//    view.makeIdentityMatrix();
//    view*=headView;

	transform.setMatrix(headView);

	invert = node;
	node.setTransformMatrix(headView);

	//rot.slerp(0.99, invert.getOrientationQuat(), node.getOrientationQuat());

	rot = node.getOrientationQuat();

	cam.setPosition(-0.6 / 2.0, 0, 0);
//    cam.setOrientation(rot);

	ofSetColor(255, 0, 255);
	ofDrawBitmapStringHighlight(
			"HeadView: " + ofToString(transform.getHeadView(), 10), 10, 100);

	ofDrawBitmapStringHighlight("Rot :" + ofToString(node.getOrientationQuat()),
			10, 400);

	ofDrawBitmapStringHighlight("Cardboard Camera",
			ofGetWidth() - ofGetHeight(), ofGetHeight() / 2 - 20);
	cam.begin(ofRectangle(0, 0, ofGetWidth() / 2, ofGetHeight()));

	ofPushMatrix();
	ofVec3f axis;
	float angle;
	rot.getRotate(angle, axis);
	ofRotate(angle, axis.x, axis.y, axis.z);
	ofSetColor(255, 0, 255);
	planet.drawWireframe();
	ofSetColor(255, 255, 0);
	ofDrawBox(ofVec3f(-50, 0, 0), 10, 10, 10);
	ofDrawBox(ofVec3f(-50, -50, 0), 10, 10, 10);
	ofDrawBox(ofVec3f(-50, -50, -50), 10, 10, 10);
	ofPopMatrix();
	cam.end();

	cam.setPosition(0.6 / 2.0, 0, 0);
	cam.begin(
			ofRectangle(ofGetWidth() / 2, 0, ofGetWidth() / 2, ofGetHeight()));
	ofSetColor(255, 0, 255);
	ofPushMatrix();
	rot.getRotate(angle, axis);
	ofRotate(angle, axis.x, axis.y, axis.z);
	planet.drawWireframe();
	ofSetColor(255, 255, 0);
	ofDrawBox(ofVec3f(-50, 0, 0), 10, 10, 10);
	ofDrawBox(ofVec3f(-50, -50, 0), 10, 10, 10);
	ofDrawBox(ofVec3f(-50, -50, -50), 10, 10, 10);
	ofPopMatrix();
	cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
	ofLog() << "windowResized" << endl;
}

//--------------------------------------------------------------
void ofApp::touchDown(int x, int y, int id) {

}

//--------------------------------------------------------------
void ofApp::touchMoved(int x, int y, int id) {

}

//--------------------------------------------------------------
void ofApp::touchUp(int x, int y, int id) {
	tracking.reset();

}

//--------------------------------------------------------------
void ofApp::touchDoubleTap(int x, int y, int id) {

}

//--------------------------------------------------------------
void ofApp::touchCancelled(int x, int y, int id) {

}

//--------------------------------------------------------------
void ofApp::swipe(ofxAndroidSwipeDir swipeDir, int id) {

}

//--------------------------------------------------------------
void ofApp::pause() {

}

//--------------------------------------------------------------
void ofApp::stop() {

}

//--------------------------------------------------------------
void ofApp::resume() {

}

//--------------------------------------------------------------
void ofApp::reloadTextures() {
	planet.setUseVbo(false);
	planet.set(1000, 50);
	planet.setPosition(0, 0, 0);
}

//--------------------------------------------------------------
bool ofApp::backPressed() {
	return false;
}

//--------------------------------------------------------------
void ofApp::okPressed() {

}
;

//--------------------------------------------------------------
void ofApp::cancelPressed() {

}
;
