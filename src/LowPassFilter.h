/*
 * LowPassFilter.h
 *
 *  Created on: Feb 28, 2015
 *      Author: dantheman
 */
#pragma once
#include "ofMain.h"
class LowPassFilter {
public:
	LowPassFilter();
	virtual ~LowPassFilter();

	float MICRO_TO_SECONDS;
	float timeConstantSecs;
	ofVec3f filteredData;
	float lastTimestampNs;
	int numSamples;
	ofVec3f temp;

	void setCutoffFrequency(float cutoffFrequency) {
		MICRO_TO_SECONDS = 1.0/1.0E-6;
		timeConstantSecs = (1.0 / (2*PI * cutoffFrequency));
		temp.set(0, 0, 0);
		filteredData.set(0, 0, 0);
		lastTimestampNs = 0;
		numSamples = 0;

	}

	int getNumSamples() {
		return numSamples;
	}

	void addSample(ofVec3f sampleData, long timestampNs) {
		addWeightedSample(sampleData, timestampNs, 1.0);
	}

	void addWeightedSample(ofVec3f sampleData, long timestampNs,
			float weight) {

//		ofLog()<<"addWeightedSample time diff "<<ofToString((timestampNs - lastTimestampNs)*MICRO_TO_SECONDS)<<endl;
//		ofLog()<<"addWeightedSample timeConstantSecs "<<timeConstantSecs<<endl;

		if (numSamples == 0) {
			filteredData.set(sampleData);
			lastTimestampNs = timestampNs;
			numSamples++;
			return;
		}

		float weightedDeltaSecs = weight * (timestampNs - lastTimestampNs)*MICRO_TO_SECONDS;

		float alpha = weightedDeltaSecs / (timeConstantSecs + weightedDeltaSecs);
		//filteredData = ofVec3f(ofLerp(filteredData.x, sampleData.x, alpha), ofLerp(filteredData.y, sampleData.y, alpha), ofLerp(filteredData.z, sampleData.z, alpha))+sampleData;
		filteredData*=(alpha);
//		ofLog()<<"addWeightedSample sampleData "<<sampleData<<endl;
//		ofLog()<<"addWeightedSample alpha "<<alpha<<endl;
		sampleData*=(1.0-alpha);
		filteredData+=sampleData;
//		ofLog()<<"addWeightedSample filteredData "<<filteredData<<endl;
		lastTimestampNs = timestampNs;
		numSamples++;
//		if(numSamples > 100){
//			numSamples = 30;
//		}
	}

	ofVec3f getFilteredData() {
		return filteredData;
	}
};

