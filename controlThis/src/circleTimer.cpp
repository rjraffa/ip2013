/*
 *  circleTimer.cpp
 *  controlThis
 *
 *  Created by Ryan Raffa on 2/2/13.
 *  Copyright 2013. All rights reserved.
 *
 */

#include "circleTimer.h"


//------------------------------------------------------------------
void circleTimer::setup() {

	ofSetCircleResolution(100);

	circleTimerPosX=0.0;
	circleTimerPosY=650.0;
	
	circleTimerRadius=20;

	circleState = true;
	
	//time associated with which circle
	circleStateTimerStart=0;
	circleStateTimerFinish=0;
	
}



//------------------------------------------------------------------
void circleTimer::update() {
}



//------------------------------------------------------------------
void circleTimer::draw() {
	
	ofSetColor(255, 255, 255);
	
	if (circleState==true) {
		ofNoFill();
	}
	
	if (circleState==false) {
		ofFill();
	}
	
	
	ofCircle(circleTimerPosX, circleTimerPosY, circleTimerRadius);
	
}

