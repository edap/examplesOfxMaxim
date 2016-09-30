#include "ofApp.h"
//this is the ofxMaxim example for this https://github.com/micknoise/Maximilian/blob/master/maximilian_examples/10.Filters.cpp

void ofApp::setup(){
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    ofBackground(0,0,0);

    sampleRate 	= 44100; /* Sampling Rate */
    bufferSize	= 512; /* Buffer Size. you have to fill this buffer with sound using the for loop in the audioOut method */
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);

    ofSoundStreamSetup(2,2,this, sampleRate, bufferSize, 4); /* this has to happen at the end of setup - it switches on the DAC */
    myEnvelope.setAttack(0);
    myEnvelope.setDecay(1);  // Needs to be at least 1
    myEnvelope.setSustain(1);
    myEnvelope.setRelease(1000);

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

        myCurrentVolume=myEnvelope.adsr(1.,myEnvelope.trigger);

        CurrentCount=myCounter.phasor(1, 1, 9);//phasor can take three arguments; frequency, start value and end value.

        // You'll notice that these 'if' statements don't require curly braces "{}".
        // This is because there is only one outcome if the statement is true.

        if (CurrentCount==1) myEnvelope.trigger=1; //trigger the envelope

        else myEnvelope.trigger=0;//release the envelope to make it fade out only if it's been triggered

        myOscOutput=mySwitchableOsc.sawn(100);

        // Below, the oscilator signals are being passed through a low pass filter.
        // The middle input is the filter cutoff. It is being controlled by the envelope.
        // Notice that the envelope is being amplified so that it scales between 0 and 1000.
        // The last input is the resonance.
        myFilteredOutput=myFilter.lores(myOscOutput,myCurrentVolume*1000,10);

        output[i*nChannels    ] = myFilteredOutput;
        output[i*nChannels + 1] = myFilteredOutput;
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
