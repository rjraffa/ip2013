#pragma once

#include "ofMain.h"
#include "samplerButton.h"
#include "circleTimer.h"

class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    
        //my new instruments
        ofSoundPlayer  kick;
        ofSoundPlayer  handclap;
        ofSoundPlayer  snare;
        ofSoundPlayer  vocal;
        ofSoundPlayer  vocalTwo;
        ofSoundPlayer  bass;
        ofSoundPlayer  bassTwo;
        ofSoundPlayer  cool;
        ofSoundPlayer  coolTwo;
        ofSoundPlayer  keyboard;
        ofSoundPlayer  keyboardTwo;
        
        //draws the buttons
        vector <samplerButton> samplerButtons;
        
        //draws the timer
        vector <circleTimer> circleTimers;
        
        int counter;
        bool playerState;
        
        //manage what has already played so it doesn't repeat tones
        int kickJustPlayed;
        
        int numOfButtons[8];
    
        ofTrueTypeFont  ahg20;
    

};
