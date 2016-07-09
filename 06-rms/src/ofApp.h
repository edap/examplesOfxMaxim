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

    ofxPanel gui;
    ofParameter<bool> enableSmooth = false;
    ofParameter<float> smoothedVal;
    ofParameter<int> radius;
    ofParameter<int> lineScale;

    int		bufferSize;
    int		sampleRate;
    ofxMaxiSample sample;
    maxiMix mymix;
    double wave;
    double outputs[2];
    float smoothedVolume = 0;
    float scaledVolume = 0;
    vector <float> volHistory;
    ofPolyline line;
};