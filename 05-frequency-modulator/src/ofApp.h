#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    // Audio output and input methods
    void audioOut(float * output, int bufferSize, int nChannels);

    double  drawOutput[1024];
    int     counter = 0;
    int		bufferSize;
    int		sampleRate;
    int     fftSize;
    ofParameter<int>   modulation_index;
    ofParameter<double> fundamental_frequency;
    ofParameter<double> frequency;
    ofParameter<bool>   use_phasor;

    ofxPanel   gui;
    ofxMaxiOsc myOscill;
    ofxMaxiOsc myOscill2;
    ofxMaxiFFT fft;
};


