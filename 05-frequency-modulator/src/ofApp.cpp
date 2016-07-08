#include "ofApp.h"

void ofApp::setup(){
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    ofBackground(0,0,0);
    gui.setup();
    gui.setPosition(ofPoint(ofGetWidth()-250, 40));
    gui.add(fundamental_frequency.set("fundamental freq.", 500.0, 20.0, 2000.0));
    gui.add(modulation_index.set("modulation index", 1000, 100, 5000));
    gui.add(frequency.set("modulation freq.", 1.0, 0.1, 100.0));
    gui.add(use_phasor.set("phasor", false));

    sampleRate 	= 44100; /* Sampling Rate */
    bufferSize	= 512; /* Buffer Size. you have to fill this buffer with sound using the for loop in the audioOut method */

    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    // the higher the value, the more accurate will be the fft analysis
    fftSize = 1024 * 2;
    fft.setup(fftSize, 512, 256);

    /* this has to happen at the end of setup - it switches on the DAC */
    ofSoundStreamSetup(2,2,this, sampleRate, bufferSize, 4);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    gui.draw();
    string msg = "decreasing the frequency of the second wave decrease the speed that the waves take to go from -1 to +1";
    string msg2 = "increasing the modulation index increase the number of sidewaves on the left and on the right of the fundamental";
    string msg3 = "using phasor the modulator wave goes between 0 and 1 instead -1 and 1 like with the sine wave";
    ofDrawBitmapString(msg, 10, 10);
    ofDrawBitmapString(msg2, 10, 25);
    ofDrawBitmapString(msg3, 10, 30);

    ofSetColor(255, 255, 255);
    // frequency domain
    for(int i = 0; i < fftSize ;i++){
        ofDrawRectangle(i * 2, ofGetHeight(), 2, -(fft.magnitudesDB[i]) * 8);
    }
}

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
    double wave;
    for (int i = 0; i < bufferSize; i++){
        if (use_phasor) {
            wave = myOscill.sinewave(fundamental_frequency + (myOscill2.phasor(frequency) * modulation_index));
        } else {
            wave = myOscill.sinewave(fundamental_frequency + (myOscill2.sinewave(frequency) * modulation_index));
        }

        //fft
        if(fft.process(wave)){
            fft.magsToDB();
        }
        output[i*nChannels    ] = wave;
        output[i*nChannels + 1] = wave;

        //used only in the time domain visualization
        counter ++;
        drawOutput[counter % 1024] = wave;
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
