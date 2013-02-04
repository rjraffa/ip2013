#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    ofEnableAlphaBlending();
    ofSetVerticalSync(true);
	
    //set how quickly it draws
	ofSetFrameRate(30);
    
    ahg20.loadFont("ahg-bold.ttf", 20, true, true);
    ahg20.setLineHeight(24.0f);
    ahg20.setLetterSpacing(1.037);
    
	//checks the state of the spacebar keypress
	playerState=false;
	
	//sounds used for the sampler
	kick.loadSound("sounds/kick.wav");
	handclap.loadSound("sounds/handclap.wav");
	snare.loadSound("sounds/snare.wav");
	vocal.loadSound("sounds/vocal.wav");
	vocalTwo.loadSound("sounds/vocal2.wav");
	bass.loadSound("sounds/bass.wav");
	bassTwo.loadSound("sounds/bass2.wav");
	cool.loadSound("sounds/cool.wav");
	coolTwo.loadSound("sounds/cool2.wav");
	keyboard.loadSound("sounds/keyboard.wav");
	keyboardTwo.loadSound("sounds/keyboard2.wav");
	
	
	//does the setup and puts all of the X and Y position values for the buttons
	for (int i=0;i<64;i++) {
        samplerButton mySamplerButton;
        circleTimer myCircleTimer;
		mySamplerButton.setup();
		myCircleTimer.setup();
		mySamplerButton.posY=((i%8)*mySamplerButton.buttonHeight);
		mySamplerButton.checkMyPlay=false;
        samplerButtons.push_back(mySamplerButton);
        circleTimers.push_back(myCircleTimer);
	}
    
	for (int i = 0; i<8; i++) {
		samplerButtons[i].posX=0;
		circleTimers[i].circleTimerPosX=samplerButtons[i].buttonWidth/2;
		circleTimers[i].circleStateTimerStart=0;
		circleTimers[i].circleStateTimerFinish=10;
	}
    
	for (int i = 8; i<16; i++) {
		samplerButtons[i].posX=samplerButtons[i].buttonWidth;
		circleTimers[i].circleTimerPosX=(samplerButtons[i].buttonWidth)+samplerButtons[i].buttonWidth/2;
		circleTimers[i].circleStateTimerStart=10;
		circleTimers[i].circleStateTimerFinish=20;
	}
    
	for (int i = 16; i<24; i++) {
		samplerButtons[i].posX=(2*samplerButtons[i].buttonWidth);		
		circleTimers[i].circleTimerPosX=(2*samplerButtons[i].buttonWidth)+samplerButtons[i].buttonWidth/2;
		circleTimers[i].circleStateTimerStart=20;
		circleTimers[i].circleStateTimerFinish=30;		
	}
	
	for (int i = 24; i<32; i++) {
		samplerButtons[i].posX=(3*samplerButtons[i].buttonWidth);
		circleTimers[i].circleTimerPosX=(3*samplerButtons[i].buttonWidth)+samplerButtons[i].buttonWidth/2;
		circleTimers[i].circleStateTimerStart=30;
		circleTimers[i].circleStateTimerFinish=40;
	}
    
	for (int i = 32; i<40; i++) {
		samplerButtons[i].posX=(4*samplerButtons[i].buttonWidth);
		circleTimers[i].circleTimerPosX=(4*samplerButtons[i].buttonWidth)+samplerButtons[i].buttonWidth/2;
		circleTimers[i].circleStateTimerStart=40;
		circleTimers[i].circleStateTimerFinish=50;
	}
    
	for (int i = 40; i<48; i++) {
		samplerButtons[i].posX=(5*samplerButtons[i].buttonWidth);
		circleTimers[i].circleTimerPosX=(5*samplerButtons[i].buttonWidth)+samplerButtons[i].buttonWidth/2;
		circleTimers[i].circleStateTimerStart=50;
		circleTimers[i].circleStateTimerFinish=60;
	}
    
	for (int i = 48; i<56; i++) {
		samplerButtons[i].posX=(6*samplerButtons[i].buttonWidth);
		circleTimers[i].circleTimerPosX=(6*samplerButtons[i].buttonWidth)+samplerButtons[i].buttonWidth/2;
		circleTimers[i].circleStateTimerStart=60;
		circleTimers[i].circleStateTimerFinish=70;
	}
    
	for (int i = 56; i<64; i++) {
		samplerButtons[i].posX=(7*samplerButtons[i].buttonWidth);
		circleTimers[i].circleTimerPosX=(7*samplerButtons[i].buttonWidth)+samplerButtons[i].buttonWidth/2;
		circleTimers[i].circleStateTimerStart=70;
		circleTimers[i].circleStateTimerFinish=80;
	}

}

//--------------------------------------------------------------
void testApp::update(){

    //updates all of the X and Y positions created before
	for (int i=0; i<samplerButtons.size(); i++) {
		samplerButtons[i].posX;
		samplerButtons[i].posY;
		
		printf("posX: %f\n",samplerButtons[i].posX);		
		printf("posY: %f\n",samplerButtons[i].posY);
		printf("buttonState: %d\n",samplerButtons[i].buttonState);
		printf("checkMyPlay: %d\n",samplerButtons[i].checkMyPlay);	
		printf("circleTimerPosX: %f\n",circleTimers[i].circleTimerPosX);
	}
    
	//playerState turns on and turns off the sequencer
	//if the playerState is false, the circles get noFill, player checker resets, and the counter resets
	if (playerState==false) {
		for (int i=0; i<samplerButtons.size(); i++) {
			circleTimers[i].circleState=true;
			samplerButtons[i].checkMyPlay=false;
			counter=0;
		}
	}
	
	//turns the circles on and off
	//if playerState is true, the sequencer is playing
	//need to come up with a plan on how to change tempo.
	//right now, counter has to be updated manually
	else if (playerState==true) {
		counter++;
		
		if (counter>79) {
			for (int i=0; i<samplerButtons.size(); i++) {
				//this clears all of the samples so they can be played again on the next series
				samplerButtons[i].checkMyPlay=false;
				//this resets the counter
				counter=0;
			}
		}
		
		//this fills the circles if the counter is at a specific time
		for (int i=0; i<samplerButtons.size(); i++) {
			if (counter>circleTimers[i].circleStateTimerStart && counter<=circleTimers[i].circleStateTimerFinish) {
				circleTimers[i].circleState=false;
			}
			else {
				circleTimers[i].circleState=true;
			}
		}
	}
	
	//see what's going on with the counter
	printf("counter: %d\n",counter);
    
}

//--------------------------------------------------------------
void testApp::draw(){

    ofBackground(0, 0, 0);
    ofEnableSmoothing();
	
	//this draws the sampler buttons
	ofPushMatrix();
        ofTranslate(5, 5, 0);
        
        for (int i=0; i<samplerButtons.size(); i++) {		
            samplerButtons[i].draw();
        }
	ofPopMatrix();
    
	
	//this draws the timer circles
	for (int i=0; i<circleTimers.size(); i++) {
		circleTimers[i].draw();
	}
	
	//kick drum
	//this secion checks to see if the button has been clicked, if the circle timer is there, if it is playing, and if it has already been played
	//if this all checks out, it plays the sample
	for (int i=0; i<samplerButtons.size(); i=i+8) {
		
		if (samplerButtons[i].buttonState == false && circleTimers[i].circleState==false && samplerButtons[i].checkMyPlay==false) {		
            ofNoFill();
            ofCircle(ofGetWidth()/2, ofGetHeight()/2, 100);
            kick.play();
            samplerButtons[i].checkMyPlay=true;
        }
    }
    
	
	//handclap drum
	//this secion checks to see if the button has been clicked, if the circle timer is there, if it is playing, and if it has already been played
	//if this all checks out, it plays the sample
	for (int i=1; i<samplerButtons.size(); i=i+8) {
		
		if (samplerButtons[i].buttonState == false && circleTimers[i].circleState==false && samplerButtons[i].checkMyPlay==false) {		
			ofNoFill();
			ofCircle(ofGetWidth()/2, ofGetHeight()/2, 100);
			handclap.play();
			samplerButtons[i].checkMyPlay=true;
		}
	}
	
	
	//snare drum
	//this secion checks to see if the button has been clicked, if the circle timer is there, if it is playing, and if it has already been played
	//if this all checks out, it plays the sample
	for (int i=2; i<samplerButtons.size(); i=i+8) {
		
		if (samplerButtons[i].buttonState == false && circleTimers[i].circleState==false && samplerButtons[i].checkMyPlay==false) {		
			ofNoFill();
			ofCircle(ofGetWidth()/2, ofGetHeight()/2, 100);
			snare.play();
			samplerButtons[i].checkMyPlay=true;
		}
	}
    
	//keyboard
	//this secion checks to see if the button has been clicked, if the circle timer is there, if it is playing, and if it has already been played
	//if this all checks out, it plays the sample
	for (int i=3; i<samplerButtons.size(); i=i+8) {
		
		if (samplerButtons[i].buttonState == false && circleTimers[i].circleState==false && samplerButtons[i].checkMyPlay==false) {		
			ofNoFill();
			ofCircle(ofGetWidth()/2, ofGetHeight()/2, 100);
			keyboard.play();
			samplerButtons[i].checkMyPlay=true;
		}
	}
	
	
	//keyboard two
	//this secion checks to see if the button has been clicked, if the circle timer is there, if it is playing, and if it has already been played
	//if this all checks out, it plays the sample
	for (int i=4; i<samplerButtons.size(); i=i+8) {
		
		if (samplerButtons[i].buttonState == false && circleTimers[i].circleState==false && samplerButtons[i].checkMyPlay==false) {		
			ofNoFill();
			ofCircle(ofGetWidth()/2, ofGetHeight()/2, 100);
			keyboardTwo.play();
			samplerButtons[i].checkMyPlay=true;
		}
	}
	
	//bass
	//this secion checks to see if the button has been clicked, if the circle timer is there, if it is playing, and if it has already been played
	//if this all checks out, it plays the sample
	for (int i=5; i<samplerButtons.size(); i=i+8) {
		
		if (samplerButtons[i].buttonState == false && circleTimers[i].circleState==false && samplerButtons[i].checkMyPlay==false) {		
			ofNoFill();
			ofCircle(ofGetWidth()/2, ofGetHeight()/2, 100);
			bass.play();
			samplerButtons[i].checkMyPlay=true;
		}
	}
	
	//bassTwo
	//this secion checks to see if the button has been clicked, if the circle timer is there, if it is playing, and if it has already been played
	//if this all checks out, it plays the sample
	for (int i=6; i<samplerButtons.size(); i=i+8) {
		
		if (samplerButtons[i].buttonState == false && circleTimers[i].circleState==false && samplerButtons[i].checkMyPlay==false) {		
			ofNoFill();
			ofCircle(ofGetWidth()/2, ofGetHeight()/2, 100);
			bassTwo.play();
			samplerButtons[i].checkMyPlay=true;
		}
	}
	
	//vocal
	//this secion checks to see if the button has been clicked, if the circle timer is there, if it is playing, and if it has already been played
	//if this all checks out, it plays the sample
	for (int i=7; i<samplerButtons.size(); i=i+8) {
		
		if (samplerButtons[i].buttonState == false && circleTimers[i].circleState==false && samplerButtons[i].checkMyPlay==false) {		
			ofNoFill();
			ofCircle(ofGetWidth()/2, ofGetHeight()/2, 100);
			vocal.play();
			samplerButtons[i].checkMyPlay=true;
		}
	}

    
    ofSetColor(225);
	ahg20.drawString("Kick", 610, 45);
	ahg20.drawString("Hand-clap", 610, 45+samplerButtons[0].buttonHeight);
    ahg20.drawString("High-hat", 610, 45+(samplerButtons[0].buttonHeight*2));
    ahg20.drawString("Keyboard One", 610, 45+(samplerButtons[0].buttonHeight*3));
	ahg20.drawString("Keyboard Two", 610, 45+(samplerButtons[0].buttonHeight*4));
	ahg20.drawString("Bass One", 610, 45+(samplerButtons[0].buttonHeight*5));
	ahg20.drawString("Bass Two", 610, 45+(samplerButtons[0].buttonHeight*6));
	ahg20.drawString("Voices", 610, 45+(samplerButtons[0].buttonHeight*7));
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    if (key == ' ') {
		playerState=!playerState;
	}

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
    if (key == 'f') {
        ofToggleFullscreen();
    }

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
    //pan goes from -1 (left) to 1 (right)
//    float panValue = x-(ofGetWindowWidth()/2);
//    panValue = ofMap(panValue, 0, ofGetWindowWidth()/2, -1, 1);
//    
//    kick.setPan(panValue);

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
    for (int i=0; i<samplerButtons.size(); i++) {
        
		if (x >= (samplerButtons[i].posX) && x <= (samplerButtons[i].posX)+samplerButtons[i].myButtonWidth && y >=(samplerButtons[i].posY) && y <= (samplerButtons[i].posY)+samplerButtons[i].myButtonHeight) {
            
            samplerButtons[i].buttonState=!samplerButtons[i].buttonState;
            
		}
        
	}

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}