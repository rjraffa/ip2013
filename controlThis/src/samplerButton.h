/*
 *  samplerButton.h
 *  controlThis
 *
 *  Created by Ryan Raffa on 2/2/13.
 *  Copyright 2013. All rights reserved.
 *
 */
#ifndef _samplerButton
#define _samplerButton


#include "ofMain.h"


class samplerButton {
	
	public:
		void setup();
		void update();
		void draw();
	
	void mode();
	
	float posX;
	float posY;
	float buttonWidth;
	float buttonHeight;
	
	
	float myPosX;
	float myPosY;
	float myButtonWidth;
	float myButtonHeight;

	//checks to see if the button has been clicked or not	
	bool buttonState;
	bool checkMyPlay;

};

#endif
