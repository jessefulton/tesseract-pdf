#pragma once

#include "ofMain.h"
#include "ofxTesseract.h"
#include "ofxUI.h"
//#include "CvUtils.h"

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
    
    
        float scale;
        int medianSize;
    
        void exit(); 
        void guiEvent(ofxUIEventArgs &e);
    
        ofVideoPlayer mov;
        ofxUICanvas *gui;

        void loadFrameToImage();
        void preprocessImage();
        void runOcr();
        
        ofxTesseract tess;
        ofImage img, scaled;
        string ocrResult;

};
