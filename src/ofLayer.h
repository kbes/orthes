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

class ofLayer {
    
    public:
        void update();
        void draw();
        void pourFbo();
        void changeVideo(string fileName);
        void mousePressed(int x, int y);
        void mouseDragged(int x, int y);
        void releaseCorner();
        ofLayer(string fileName);
    
    private:
        void warp();
    
        ofFbo fbo;
        ofQTKitPlayer* video;
    
        GLfloat warpMatrix[16];
        CvPoint2D32f cvSrc[4];
        CvPoint2D32f cvDst[4];

        vector<ofPoint> corners;

        bool showHud;
        int selectedCorner;
};

#endif /* defined(__quadWarp__ofLayer__) */
