//
//  ofLayer.cpp
//  quadWarp
//
//  Created by Christian Geick on 16.09.15.
//
//

#include "ofLayer.h"

ofLayer::ofLayer(int number, string fileName) {
  	ofSetVerticalSync(true);
    fbo.allocate(ofGetWidth(), ofGetHeight());
    video = new ofQTKitPlayer();
    video->loadMovie(fileName, OF_QTKIT_DECODE_TEXTURE_ONLY);
    video->play();
    
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

    string showToggleName = "show video";
    show.setup(showToggleName, true);
}

void ofLayer::update() {
    video->update();
    warp();
}

void ofLayer::draw() {
    // Draw distortable image frame
    ofSetColor(255, 0, 0, 100);
    ofBeginShape();
    for (int i=0; i<corners.size(); i++) {
        ofVertex(cvDst[i].x, cvDst[i].y);
    }
    ofEndShape(true);
    
    ofSetColor(255);
    
    // Spill video content into buffer
    fbo.begin();
        video->draw(0, 0, ofGetWidth(), ofGetHeight());
    fbo.end();
    
    // Draw corner handles
    for (int i=0; i<corners.size(); i++) {
        ofSetColor(255);
        if (i == selectedCorner) {
            ofSetColor(0, 255, 255);
        }
        ofEllipse(cvDst[i].x, cvDst[i].y, 15, 15);
    }
}

// Draw contents of buffer to screen
void ofLayer::pourFbo() {
    if (show) {
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
    
    // Check if click is inside the polygon and outside the handles
    if (selectedCorner == -1) {
        bool inside = false;
        for (int i=0, j=corners.size(); i<corners.size(); j = i++) {
            if ((cvDst[i].y > y) != (cvDst[j].y > y) &&
                (x < (cvDst[j].x - cvDst[i].x) * (y - cvDst[i].y) / (cvDst[j].y-cvDst[i].y) + cvDst[i].x)) {
                inside = !inside;
            }
        }

    if (inside) {
            fprintf(stderr, "inside");
        }
    }
}

void ofLayer::releaseCorner() {
    selectedCorner = -1;
}

ofxToggle* ofLayer::getShowToggle() {
    return &show;
}