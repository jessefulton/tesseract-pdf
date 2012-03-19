#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup() {
    
	tess.setup();
	tess.setWhitelist("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ.,");
	tess.setAccuracy(ofxTesseract::ACCURATE);
	tess.setMode(ofxTesseract::AUTO);
    
    
    mov.loadMovie("paradise.pdf");
    mov.setSpeed(0.1);
    mov.play();
    mov.setPaused(true);
    
    printf("total frames %i", mov.getTotalNumFrames());
    
    //ofSetBackgroundAuto(false);
    ofSetFrameRate(30);
    x = 0;
    y = 0;
    
    int totalPages = mov.getTotalNumFrames();
    
    gui = new ofxUICanvas(0,0,320,320);		//ofxUICanvas(float x, float y, float width, float height)		
    gui->addWidgetDown(new ofxUILabel("PDF OCR", OFX_UI_FONT_LARGE)); 
    //gui->addWidgetDown(new ofxUISlider(304,16,0.0,255.0,100.0,"BACKGROUND VALUE")); 
    gui->addWidgetDown(new ofxUISlider(304,32,0,totalPages,100,"FRAME")); 
    gui->addWidgetDown(new ofxUIButton(64, 64, false, "RUN_OCR"));  
    ofAddListener(gui->newGUIEvent, this, &testApp::guiEvent); 
    gui->loadSettings("GUI/guiSettings.xml"); 
    
}


//--------------------------------------------------------------
void testApp::update() {
	mov.update();
    //printf("" + mov.getCurrentFrame());
    /*
     if(panel.hasValueChanged("scale") || panel.hasValueChanged("medianSize")) {
     ocrResult = runOcr(panel.getValueF("scale"), panel.getValueI("medianSize"));
     scaled.update();
     panel.clearAllChanged();
     }
     
     */
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
    
    
    
    /*
     ofPushMatrix();
     
     ofTranslate(300, 0);
     
     ofSetColor(0);	
     vector<string> lines = ofSplitString(ocrResult, "\n");
     for(int i = 0; i < lines.size(); i++) {
     ofDrawBitmapString(lines[i], 10, 20 + i * 12);
     }
     
     ofSetColor(255);
     img.draw(0, 200);
     scaled.draw(0, 400);
     
     ofPopMatrix();
     
     
     */
    
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

void testApp::guiEvent(ofxUIEventArgs &e) {
    if (e.widget->getName() == "FRAME") {
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        int frame = (int)slider->getScaledValue();
        mov.setFrame(frame);
    }
    else if (e.widget->getName() == "RUN_OCR") {
        runOcr(1.0, 0);
    }
}



// depending on the source of the text you want to OCR,
// you might need to preprocess it. here i'm doing a
// simple resize followed by a median blur.
void testApp::runOcr(float scale, int medianSize) {
	//scaled = img;
	
    ofPixels pix = mov.getPixelsRef();
    ofImage img = ofImage(pix);
	img.setImageType(OF_IMAGE_GRAYSCALE);
	img.update();

    
	// resize and median blur the image
	//scaled.resize(img.getWidth() * scale, img.getHeight() * scale);
	//medianBlur(scaled, medianSize);
    
	//return tess.findText(scaled);
	ocrResult = tess.findText(img);
    cout << ocrResult;
    //return ocrResult;
}