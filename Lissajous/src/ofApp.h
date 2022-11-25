#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        float delay(float in);
    
        void audioIn(ofSoundBuffer & input);
    
        ofPolyline line;
        ofSoundStream soundStream;
        ofFbo fbo;

        vector <float> left;
        vector <float> right;
        vector <float> mix;
    
        int delaySize = 2205;
        float delayBuff[2205];
        float delayed[2205];
        int bufPosn = 0;
    
        int frameCount=0;
};
