#include "ofApp.h"

void ofApp::setup(){


    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    ofBackground(0,0,0);
    gui.setup();
    gui.setPosition(ofPoint(ofGetWidth()-250, 40));
    gui.add(magnitude.set("scale", 1.0, 0.2, 10.0));
    gui.add(frequency.set("frequency Hz", 50.0, 20.0, 4000.0));
    currentWave = SAW;

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
    string msg = "press 0 for saw, 1 for sawn, 2 for square, press 3 for pulse, press 4 for triangle, press 5 for sine";
    string msg2 = "press f to visualize the wase in frequency domain, t for time domain";
    ofDrawBitmapString(msg, 10, 10);
    ofDrawBitmapString(msg2, 10, 25);

    ofSetColor(255, 255, 255);
    if( visualization == "frequency-domain" ){
        // frequency domain
        for(int i = 0; i < fftSize ;i++){
            ofDrawRectangle(i * 2, ofGetHeight(), 2, -(fft.magnitudesDB[i]) * 8);
        }
    }else {
        //time domain
        int spacing = ofGetWidth()/1024;
        for (int i = 0; i < 1024; i++) {
            ofDrawRectangle(i * spacing, ofGetHeight()/2, spacing, (drawOutput[i] * ofGetHeight() / 5));
        }
    }
}

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
    for (int i = 0; i < bufferSize; i++){
        double wave;
        switch (currentWave) {
            case SAW:
                wave = myOscill.saw(frequency) * magnitude;
                break;
            case SQUARE:
                wave = myOscill.square(frequency) * magnitude;
                break;
            case TRIANGLE:
                wave = myOscill.triangle(frequency) * magnitude;
                break;
            case PULSE:
                wave = myOscill.pulse(frequency, 0.2) * magnitude;
                break;
            case SAWN:
                wave = myOscill.sawn(frequency) * magnitude;
                break;
            case SINE:
                wave = myOscill.sinewave(frequency) * magnitude;
                break;
                
            default:
                wave = myOscill.sinewave(frequency) * magnitude;
                break;
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
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    for(int i = 0; i < bufferSize; i++){
        /* you can also grab the data out of the arrays*/
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case '0':
            currentWave = SAW;
            break;
        case '1':
            currentWave = SAWN;
            break;
        case '2':
            currentWave = SQUARE;
            break;
        case '3':
            currentWave = PULSE;
            break;
        case '4':
            currentWave = TRIANGLE;
            break;
        case '5':
            currentWave = SINE;
            break;

        default:
            currentWave = SINE;
            break;
    }

    if (key == 't'){
        visualization = "time-domain";

    };
    if (key == 'f'){
        visualization = "frequency-domain";
    };
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
