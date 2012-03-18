#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup() {
    
    mov.loadMovie("paradise.pdf");
    mov.setSpeed(0.1);
    mov.play();
    
    //ofSetBackgroundAuto(false);
    ofSetFrameRate(30);
    x = 0;
    y = 0;
    
    
    gui = new ofxUICanvas(0,0,320,320);		//ofxUICanvas(float x, float y, float width, float height)		
    gui->addWidgetDown(new ofxUILabel("OFXUI TUTORIAL", OFX_UI_FONT_LARGE)); 
    gui->addWidgetDown(new ofxUISlider(304,16,0.0,255.0,100.0,"BACKGROUND VALUE")); 
    ofAddListener(gui->newGUIEvent, this, &testApp::guiEvent); 
    gui->loadSettings("GUI/guiSettings.xml"); 
    
}


//--------------------------------------------------------------
void testApp::update() {
	mov.update();
}


//--------------------------------------------------------------
void testApp::draw() {
	mov.draw(150,0);
    
    if (mov.isFrameNew()) {
        x = x + mov.getWidth();
        
        if (x>ofGetWidth()) {
            x = 0;
            y = y + mov.getHeight();
        }
        
        if (y>ofGetHeight()) {
            x = 0;
            y = 0;
        }
    }
}


//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}




void testApp::exit()
{
    gui->saveSettings("GUI/guiSettings.xml");     
    delete gui; 
}

void testApp::guiEvent(ofxUIEventArgs &e)
{
    if(e.widget->getName() == "BACKGROUND VALUE")	
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget;    
        ofBackground(slider->getScaledValue());
    }   	
}
