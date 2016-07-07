#include "ofApp.h"

void ofApp::setup(){
    sampleRate 	= 44100; /* Sampling Rate */
    bufferSize	= 512; /* Buffer Size. you have to fill this buffer with sound using the for loop in the audioOut method */


    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);

    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    ofEnableSmoothing();

    ofBackground(0,0,0);

    ofSoundStreamSetup(2,2,this, sampleRate, bufferSize, 4); /* this has to happen at the end of setup - it switches on the DAC */


}

//--------------------------------------------------------------
void ofApp::update(){


}

//--------------------------------------------------------------
void ofApp::draw(){



}

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels) {


    for (int i = 0; i < bufferSize; i++){
        //double wave = myOscill.sinewave(400) + myOscill2.sinewave(401);

        //square
        //double wave = myOscill.square(200) * 0.2;
        //saw
        //double wave = myOscill.saw(200) * 0.2;

        //triangle
        double wave = myOscill.triangle(200) * 0.2;

        //pulse
        //double wave = myOscill.pulse(200, 0.2) * 0.2;
        output[i*nChannels    ] = wave;
        output[i*nChannels + 1] = wave;
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
