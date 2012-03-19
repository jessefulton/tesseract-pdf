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
    mov.setFrame(0);
    
    img = ofImage(mov.getPixelsRef());
    scaled = ofImage(mov.getPixelsRef());
    
    scale = 1.0;
    medianSize = 0.0;
    
    printf("total frames %i", mov.getTotalNumFrames());
    
    //ofSetBackgroundAuto(false);
    ofSetFrameRate(30);
    
    int totalPages = mov.getTotalNumFrames();
    
    gui = new ofxUICanvas(0,0,320,320);		//ofxUICanvas(float x, float y, float width, float height)		
    gui->addWidgetDown(new ofxUILabel("PDF OCR", OFX_UI_FONT_LARGE)); 
    gui->addWidgetDown(new ofxUISlider(304,32,0,totalPages,0,"FRAME"));
    gui->addWidgetDown(new ofxUIButton(64, 64, false, "RUN_OCR"));  
    gui->addWidgetDown(new ofxUISlider(304,32,0,10,1.0,"SCALE_AMT"));
    gui->addWidgetDown(new ofxUISlider(304,32,1,100,1.0,"BLUR_AMT")); 
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
    
    if (mov.isFrameNew()) {
        //img = ofImage(mov.getPixelsRef());
        loadFrameToImage();
        preprocessImage();
    }

    scaled.draw(150,0);

    
    
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
    else if (e.widget->getName() == "SCALE_AMT") {
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        scale = slider->getScaledValue();
        preprocessImage();
    }
    else if (e.widget->getName() == "BLUR_AMT") {
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        //todo: int?
        medianSize = slider->getScaledValue();
    }
    else if (e.widget->getName() == "RUN_OCR") {
        runOcr();
    }
}

void testApp::loadFrameToImage() {
    img = ofImage(mov.getPixelsRef());
	img.setImageType(OF_IMAGE_GRAYSCALE);
	img.update();
    
}

void testApp::preprocessImage() {
    scaled = img;
    scaled.resize(img.getWidth() * scale, img.getHeight() * scale);
	//medianBlur(scaled, medianSize);
}

// depending on the source of the text you want to OCR,
// you might need to preprocess it. here i'm doing a
// simple resize followed by a median blur.
void testApp::runOcr() {
	loadFrameToImage();
    preprocessImage();
	//return tess.findText(scaled);
	ocrResult = tess.findText(scaled);
    cout << ocrResult;
    //return ocrResult;
}