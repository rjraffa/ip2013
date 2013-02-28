//comments pulled from oF firmataExample

/*
 * ofArduino currently only supports the standard Arduino boards
 * (UNO, Duemilanove, Diecimila, NG, and other boards based on the
 * ATMega168 or ATMega328 microcontrollers
 * The Arduio FIO and Arduino Mini should also work.
 * The Arduino MEGA and other variants based on microcontrollers
 * other than the ATMega168 and ATMega328 are not currently supported.
 * 
 * To use this example, open Arduino (preferably Arduino 1.0) and 
 * navigate to File -> Examples -> Firmata and open StandardFirmata.
 * Compile and upload StandardFirmata for your board, then close
 * the Arduino application and run this application.
 *
 * If you have a servo attached, press the left arrow key to rotate
 * the servo head counterclockwise and press the right arrow key to
 * rotate the servo head clockwise.
 *
 * Clicking the mouse over any part of the application will turn the
 * on-board LED on and off.
 *
 */


//944


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


    // replace the string below with the serial port for your Arduino board
    // you can get this from the Arduino application or via command line
    // for OSX, in your terminal type "ls /dev/tty.*" to get a list of serial devices
	ard.connect("/dev/tty.usbserial-A6008gva", 57600);
	
	// listen for EInitialized notification. this indicates that
	// the arduino is ready to receive commands and it is safe to
	// call setupArduino()
	ofAddListener(ard.EInitialized, this, &testApp::setupArduino);
	bSetupArduino	= false;	// flag so we setup arduino when its ready, you don't need to touch this :)
    
    selectTrack = 0;
    pos = ideal = 0;
    pos.x = ideal.x  = 615;
    
    //put the high value of your Analog 0 pin (aka your pot or other analog sensor)
    highAnalogValue = 944;
}

//--------------------------------------------------------------
void testApp::update(){

    updateArduino();
    
    //moves the selector based on analog value coming in
    if (potValue[0] < highAnalogValue/8) selectTrack = 0;
    if (potValue[0] >= highAnalogValue/8 && potValue[0] < (highAnalogValue/8)*2) selectTrack = 1;
    if (potValue[0] >= (highAnalogValue/8)*2 && potValue[0] < (highAnalogValue/8)*3) selectTrack = 2;
    if (potValue[0] >= (highAnalogValue/8)*3 && potValue[0] < (highAnalogValue/8)*4) selectTrack = 3;
    if (potValue[0] >= (highAnalogValue/8)*4 && potValue[0] < (highAnalogValue/8)*5) selectTrack = 4;
    if (potValue[0] >= (highAnalogValue/8)*5 && potValue[0] < (highAnalogValue/8)*6) selectTrack = 5;
    if (potValue[0] >= (highAnalogValue/8)*6 && potValue[0] < (highAnalogValue/8)*7) selectTrack = 6;
    if (potValue[0] >= (highAnalogValue/8)*7) selectTrack = 7;
    
    //using easing to show which track row is selected
    ideal.y = 35+(75*selectTrack);
    
    dist.x = ideal.x - pos.x;
	dist.y = ideal.y - pos.y;
	
	pos.x += dist.x/5.0;
	pos.y += dist.y/5.0;
    
    //updates all of the X and Y positions created before
	for (int i=0; i<samplerButtons.size(); i++) {
		samplerButtons[i].posX;
		samplerButtons[i].posY;
		
//		printf("posX: %f\n",samplerButtons[i].posX);		
//		printf("posY: %f\n",samplerButtons[i].posY);
//		printf("buttonState: %d\n",samplerButtons[i].buttonState);
//		printf("checkMyPlay: %d\n",samplerButtons[i].checkMyPlay);	
//		printf("circleTimerPosX: %f\n",circleTimers[i].circleTimerPosX);
	}
    
    
    //uses button push to select/deselect instrument buttons
    //only need to check 8 of the buttons
    for (int i=0; i<8; i++) {
        
        if (buttonState[i]!=lastButtonState[i]) {
            if(buttonState[i] == 1) {
                samplerButtons[(selectTrack)+(i*8)].buttonState=!samplerButtons[(selectTrack)+(i*8)].buttonState;
            }
        }

        lastButtonState[i] = buttonState[i];

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
void testApp::setupArduino(const int & version) {
	
	// remove listener because we don't need it anymore
	ofRemoveListener(ard.EInitialized, this, &testApp::setupArduino);
    
    // it is now safe to send commands to the Arduino
    bSetupArduino = true;
    
    // print firmware name and version to the console
    cout << ard.getFirmwareName() << endl; 
    cout << "firmata v" << ard.getMajorFirmwareVersion() << "." << ard.getMinorFirmwareVersion() << endl;
    
    // Note: pins A0 - A5 can be used as digital input and output.
    // Refer to them as pins 14 - 19 if using StandardFirmata from Arduino 1.0.
    // If using Arduino 0022 or older, then use 16 - 21.
    // Firmata pin numbering changed in version 2.3 (which is included in Arduino 1.0)
    
    // set all digital pins to input
    for (int i = 2; i < 14; i++){
        ard.sendDigitalPinMode(i, ARD_INPUT);        
    }
    
    // set analog pins to analog input
    for (int i = 0; i < 5; i++){
        ard.sendAnalogPinReporting(i, ARD_ANALOG);
    }
    
    // Listen for changes on the digital and analog pins
    ofAddListener(ard.EDigitalPinChanged, this, &testApp::digitalPinChanged);
    ofAddListener(ard.EAnalogPinChanged, this, &testApp::analogPinChanged);    
}

//--------------------------------------------------------------
void testApp::updateArduino(){
    
	// update the arduino, get any data or messages.
    // the call to ard.update() is required
	ard.update();

}

// digital pin event handler, called whenever a digital pin value has changed
// note: if an analog pin has been set as a digital pin, it will be handled
// by the digitalPinChanged function rather than the analogPinChanged function.

//--------------------------------------------------------------
void testApp::digitalPinChanged(const int & pinNum) {
    // do something with the digital input. here we're simply going to print the pin number and
    // value to the screen each time it changes
    
    buttonState[pinNum - 2] = ard.getDigital(pinNum);
    
}

// analog pin event handler, called whenever an analog pin value has changed

//--------------------------------------------------------------
void testApp::analogPinChanged(const int & pinNum) {
    // do something with the analog input. here we're simply going to print the pin number and
    // value to the screen each time it changes
    
    potValue[pinNum] = ard.getAnalog(pinNum);
    
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
	
    ofFill();
    ofEllipse(pos.x,pos.y, 20, 20);
    ofNoFill();
    
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
	ahg20.drawString("Kick", 630, 45);
	ahg20.drawString("Hand-clap", 630, 45+samplerButtons[0].buttonHeight);
    ahg20.drawString("High-hat", 630, 45+(samplerButtons[0].buttonHeight*2));
    ahg20.drawString("Keyboard One", 630, 45+(samplerButtons[0].buttonHeight*3));
	ahg20.drawString("Keyboard Two", 630, 45+(samplerButtons[0].buttonHeight*4));
	ahg20.drawString("Bass One", 630, 45+(samplerButtons[0].buttonHeight*5));
	ahg20.drawString("Bass Two", 630, 45+(samplerButtons[0].buttonHeight*6));
	ahg20.drawString("Voices", 630, 45+(samplerButtons[0].buttonHeight*7));
    
    
    if (!bSetupArduino){
		ahg20.drawString("arduino not ready...\n", 630, 640);
	} else {
		ahg20.drawString("arduino is ready!\n", 630, 640);
		//ahg20.drawString(ofToString(potValue[0]) + "\n" + ofToString(selectTrack)+"\n" + ofToString(buttonState[0]) +
		//				"\n\nsending pwm: " + ofToString((int)(128 + 128 * sin(ofGetElapsedTimef()))), 630, 640);

	}
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

    // turn on the onboard LED when the application window is clicked
	ard.sendDigital(13, ARD_HIGH);
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

    // turn off the onboard LED when the application window is clicked
	ard.sendDigital(13, ARD_LOW);
    
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