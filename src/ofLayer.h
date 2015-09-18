//
//  ofLayer.h
//  quadWarp
//
//  Created by Christian Geick on 16.09.15.
//
//

#ifndef __quadWarp__ofLayer__
#define __quadWarp__ofLayer__

#include <stdio.h>
#include "ofApp.h"
#include "ofxGui.h"

class ofLayer {
    
    public:
        void update();
        void draw();
        void pourFbo();
        void changeVideo(string fileName);
        void mousePressed(int x, int y);
        void mouseDragged(int x, int y);
        void releaseCorner();
        ofLayer(int number, string fileName);
        ofxLabel* getLabel();
        ofxToggle* getShowVideo();
        ofxToggle* getShowWarp();
        ofxToggle* getShowMask();

    private:
        void warp();
    
        ofFbo fbo;
        ofQTKitPlayer* video;
        vector<ofPoint> corners;
        ofImage* mask;
    
        GLfloat warpMatrix[16];
        CvPoint2D32f cvSrc[4];
        CvPoint2D32f cvDst[4];

        int selectedCorner;

        ofxLabel label;
        ofxToggle showVideo;
        ofxToggle showWarp;
        ofxToggle showMask;
};

#endif /* defined(__quadWarp__ofLayer__) */
