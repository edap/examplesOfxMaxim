#include "ofApp.h"

void ofApp::setup(){
    gui.setup();
    gui.add(enableSmooth.set("enable smothed volume", false));
    gui.add(minThreshold.set("minTreshold", 0.1, 0.1, 0.3));
    gui.add(smoothedVal.set("smoothed value", 0.97, 0.70, 0.99));
    gui.add(radius.set("radius", 200, 100, 800));
    gui.add(lineScale.set("lineScale", 500, 200, 1200));
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    ofBackground(0,0,0);

    sample.load(ofToDataPath("beat.wav"));
    sampleRate 	= 44100;
    bufferSize	= 512;

    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    ofSoundStreamSetup(2,2,this, sampleRate, bufferSize, 4);
    ofSetBackgroundColor(255, 200, 0);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    gui.draw();
    ofSetColor(255, 0, 0);
    ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2, threshold * radius);
}

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
    float rms = 0.0;
    int numCounted = 0;
    for (int i = 0; i < bufferSize; i++){
        wave = sample.play();
        mymix.stereo(wave, outputs, 0.5);
        output[i*nChannels    ] = outputs[0];
        output[i*nChannels + 1] = outputs[1];

        //rms calculation as explained here http://openframeworks.cc/ofBook/chapters/sound.html
        float left = outputs [0];
        float right = outputs[1];
        rms += left * left;
        rms += right * right;
        numCounted += 2;
    }

    rms /= (float)numCounted;
    rms = sqrt(rms);

    if (enableSmooth) {
        smoothedVolume *= smoothedVal;
        smoothedVolume += 0.07 * rms;
    } else {
        smoothedVolume = rms;
    }

    //onset detection as in http://openframeworks.cc/ofBook/chapters/sound.html
    threshold = ofLerp(threshold, minThreshold, decayRate);
    if(rms > threshold) {
        threshold = rms;
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
