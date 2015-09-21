#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofLayer.h"
#include "ofxGui.h"
#include "ofxOsc.h"

#define RECEIVEPORT 23585
#define SENDPORT 85523
#define HOST "192.168.0.85" //remote IP

class ofLayer;

class ofApp : public ofBaseApp {
    
    public:
		
        void setup();
        void update();
        void draw();
        void warp();
        void exit();

        void keyPressed(int key);
        void keyReleased(int key);
        void mouseMoved(int x, int y);
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void windowResized(int w, int h);
        void dragEvent(ofDragInfo dragInfo);
        void gotMessage(ofMessage msg);
    
    private:
        vector<ofLayer*> layers;
    
        bool showHud;
        int selectedCorner;
    
        ofxPanel gui;
        ofDirectory* videoFolder;
    
        ofxOscReceiver oscReceiver;
        ofxOscSender oscSender;
        float oscX = 0.0;
        float oscY = 0.0;
};
