#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofLayer.h"

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
        ofLayer* layer;

        GLfloat warpMatrix[16];
        CvPoint2D32f cvSrc[4];
        CvPoint2D32f cvDst[4];
    
        vector<ofPoint> corners;
    
        bool showHud;
        int selectedCorner;
};
