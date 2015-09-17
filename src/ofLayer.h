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
        ofLayer(string fileName);
    
    private:
        ofFbo fbo;
        ofQTKitPlayer* video;
};

#endif /* defined(__quadWarp__ofLayer__) */
