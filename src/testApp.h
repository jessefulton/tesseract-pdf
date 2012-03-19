#pragma once

#include "ofMain.h"
#include "ofxTesseract.h"
#include "ofxUI.h"


class testApp : public ofBaseApp{
	
    public:
        
        void setup();
        void update();
        void draw();
        
        void keyPressed( int key );
        void keyReleased( int key );
        void mouseMoved( int x, int y );
        void mouseDragged( int x, int y, int button );
        void mousePressed( int x, int y, int button );
        void mouseReleased( int x, int y, int button );
        void windowResized( int w, int h );
    
    
        void exit(); 
        void guiEvent(ofxUIEventArgs &e);
    
        ofVideoPlayer mov;
        ofxUICanvas *gui;
    
        int x,y;
		
    
    
        void runOcr(float scale, int medianSize);
        
        ofxTesseract tess;
        ofImage img, scaled;
        string ocrResult;

};
