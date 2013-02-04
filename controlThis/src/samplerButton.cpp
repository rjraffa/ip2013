/*
 *  samplerButton.cpp
 *  controlThis
 *
 *  Created by Ryan Raffa on 2/2/13.
 *  Copyright 2013. All rights reserved.
 *
 */

#include "samplerButton.h"


//------------------------------------------------------------------
void samplerButton::setup() {
	
	posX=0;
	posY=0;
	buttonWidth=75;
	buttonHeight=75;
	
	myButtonWidth=buttonWidth-10;
	myButtonHeight=buttonHeight-10;
	
	buttonState = true;

	//going to use this to check if something has played
	//if checkMyPlay is less than one, it can be played
	checkMyPlay = false;
	
}



//------------------------------------------------------------------
void samplerButton::update() {
	
	
	
}



//------------------------------------------------------------------
void samplerButton::draw() {
	ofSetColor(255, 255, 255);

	if (buttonState==true) {
		ofNoFill();
	}
	
	if (buttonState==false) {
		ofFill();
	}
	
	ofRect(posX, posY, myButtonWidth, myButtonHeight);

}



//------------------------------------------------------------------

void samplerButton::mode() {
}	
