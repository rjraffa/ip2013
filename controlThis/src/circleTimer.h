/*
 *  circleTimer.h
 *  controlThis
 *
 *  Created by Ryan Raffa on 2/2/13.
 *  Copyright 2013. All rights reserved.
 *
 */
#ifndef _circleTimer
#define _circleTimer


#include "ofMain.h"


class circleTimer {
	
	public:
		void setup();
		void update();
		void draw();
	
        float circleTimerPosX;
        float circleTimerPosY;
        
        float circleTimerRadius;

        bool circleState;
        
        //keeps track of when it should be played
        int circleStateTimerStart;
        int circleStateTimerFinish;

};

#endif
