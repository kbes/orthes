#include "ofLayer.h"

ofLayer::ofLayer(int number, string fileName) {
    fbo.allocate(ofGetWidth(), ofGetHeight());
    
    video = new ofQTKitPlayer();
    video->loadMovie(fileName, OF_QTKIT_DECODE_TEXTURE_ONLY);
    video->play();
    
    mask = new ofImage();
    mask->loadImage("masks/mask1a.png");
    
    selectedCorner = -1;
    
    // Locations of corners handles
    corners.push_back(ofPoint(0.0, 0.0));
    corners.push_back(ofPoint(1.0, 0.0));
    corners.push_back(ofPoint(1.0, 1.0));
    corners.push_back(ofPoint(0.0, 1.0));
    
    // Screen dimension
    cvSrc[0].x = 0.0;
    cvSrc[0].y = 0.0;
    cvSrc[1].x = ofGetWidth();
    cvSrc[1].y = 0.0;
    cvSrc[2].x = ofGetWidth();
    cvSrc[2].y = ofGetHeight();
    cvSrc[3].x = 0.0;
    cvSrc[3].y = ofGetHeight();

    label.setup("Layer", ofToString(number));
    showVideo.setup("video", true);
    showWarp.setup("warp", true);
    showMask.setup("mask", true);
}

void ofLayer::update() {
    video->update();
    warp();
}

void ofLayer::draw() {

    // Draw distortable image frame
    if (showWarp) {
        ofSetColor(255, 0, 0, 100);
        ofBeginShape();
        for (int i=0; i<corners.size(); i++) {
            ofVertex(cvDst[i].x, cvDst[i].y);
        }
        ofEndShape(true);
    }

    // Spill video content into buffer
    ofSetColor(255);
    fbo.begin();
        glEnable(GL_BLEND);
        glBlendFunc(GL_ZERO, GL_ONE_MINUS_SRC_ALPHA);
        ofClear(0);
        if (showMask) {
            mask->draw(0, 0);
        }
        glBlendFunc(GL_ZERO, GL_ONE_MINUS_SRC_ALPHA);
        if (showVideo) {
            video->draw(0, 0, ofGetWidth(), ofGetHeight());
        }
        glDisable(GL_BLEND);
    fbo.end();
    
    if (showWarp) {
        // Draw corner handles
        for (int i=0; i<corners.size(); i++) {
            ofSetColor(255);
            if (i == selectedCorner) {
                ofSetColor(0, 255, 255);
            }
            ofEllipse(cvDst[i].x, cvDst[i].y, 15, 15);
        }
    }
}

// Draw contents of buffer to screen
void ofLayer::pourFbo() {
    if (showVideo || showMask) {
        ofPushMatrix();
            // Warp the matrix!
            glMultMatrixf(warpMatrix);
            ofSetColor(255);
            fbo.draw(0, 0);
        ofPopMatrix();
    }
}

// Switch video file
void ofLayer::changeVideo(string fileName) {
    video->closeMovie();
    delete video;
    video = new ofQTKitPlayer();
    video->loadMovie(fileName, OF_QTKIT_DECODE_TEXTURE_ONLY);
    video->play();
}

// Enter the matrix
void ofLayer::warp() {
    // Set up transformation matrix with default elements
    
    for (int i=0; i<16; i++) {
        warpMatrix[i] = (i%5 == 0) ? 1.0 : 0.0;
    }
    
    // Create OpenCV points
    for (int i=0; i<corners.size(); i++) {
        cvDst[i].x = corners[i].x * ofGetWidth();
        cvDst[i].y = corners[i].y * ofGetHeight();
    }
    
    // Set up supporting matrices from distorted corners
    CvMat* transMatrix = cvCreateMat(3, 3, CV_32FC1);
    CvMat* src_mat = cvCreateMat(4, 2, CV_32FC1);
    CvMat* dst_mat = cvCreateMat(4, 2, CV_32FC1);
    // Fill matrices with corners
    cvSetData(src_mat, cvSrc, sizeof(CvPoint2D32f));
    cvSetData(dst_mat, cvDst, sizeof(CvPoint2D32f));
    // Determine actual transformation matrix
    cvFindHomography(src_mat, dst_mat, transMatrix);
    
    // Get transformation matrix as floats
    float* matrixFloats = transMatrix->data.fl;
    
    // Copy values into final warp matrix | 3x3 to 4x4
    warpMatrix[0] = matrixFloats[0];
    warpMatrix[4] = matrixFloats[1];
    warpMatrix[12] = matrixFloats[2];
    warpMatrix[1] = matrixFloats[3];
    warpMatrix[5] = matrixFloats[4];
    warpMatrix[13] = matrixFloats[5];
    warpMatrix[3] = matrixFloats[6];
    warpMatrix[7] = matrixFloats[7];
    warpMatrix[15] = matrixFloats[8];
}

// Move corner points
void ofLayer::mouseDragged(int x, int y) {
    if (selectedCorner >=0) {
        corners[selectedCorner].x = (float) x/ofGetWidth();
        corners[selectedCorner].y = (float) y/ofGetHeight();
    }
}

// Select corner handles
void ofLayer::mousePressed(int x, int y) {

    if (showWarp) {
        // Equals to 5% screen size
        float nearest = 0.05;

        selectedCorner = -1;
    
        for (int i=0; i<corners.size(); i++) {
            float distX = corners[i].x - (float) x/ofGetWidth();
            float distY = corners[i].y - (float) y/ofGetHeight();
            float dist = sqrt(distX*distX + distY*distY);
        
            if(dist < nearest && dist < 0.05){
                selectedCorner = i;
                nearest = dist;
            }
        }
    }
}

void ofLayer::releaseCorner() {
    selectedCorner = -1;
}

ofxLabel* ofLayer::getLabel() {
    return &label;
}

ofxToggle* ofLayer::getShowVideo() {
    return &showVideo;
}

ofxToggle* ofLayer::getShowWarp() {
    return &showWarp;
}

ofxToggle* ofLayer::getShowMask() {
    return &showMask;
}