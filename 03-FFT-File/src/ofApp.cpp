#include "ofApp.h"

void ofApp::setup(){
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    ofBackground(0,0,0);

    sample.load(ofToDataPath("beat2.wav"));

    sampleRate 	= 44100; /* Sampling Rate */
    bufferSize	= 512; /* Buffer Size. you have to fill this buffer with sound using the for loop in the audioOut method */

    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    // the higher the value, the more accurate will be the fft analysis
    fftSize = 1024;
    fft.setup(fftSize, 512, 256);
    /* this has to happen at the end of setup - it switches on the DAC */
    ofSoundStreamSetup(2,2,this, sampleRate, bufferSize, 4);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255, 255, 255);
    for(int i = 0; i < fftSize ;i++){
        ofDrawRectangle(i * 2, ofGetHeight(), 2, -(fft.magnitudesDB[i]) * 8);
    }
}

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
    for (int i = 0; i < bufferSize; i++){
        wave = sample.play();
        //fft
        if(fft.process(wave)){
            fft.magsToDB();
        }
        mymix.stereo(wave, outputs, 0.5);
        output[i*nChannels    ] = outputs[0];
        output[i*nChannels + 1] = outputs[1];
    }
}

//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    for(int i = 0; i < bufferSize; i++){
        /* you can also grab the data out of the arrays*/
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){


}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){


}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){


}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
