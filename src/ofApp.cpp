#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    fprintf(stderr, "αρχίζοντας\n");
    ofBackground(0);
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofEnableSmoothing();
    
    showHud = false;
    
    layer = new ofLayer("sample.mov");
   
    selectedCorner = -1;
    
    corners.push_back(ofPoint(0.0, 0.0));
    corners.push_back(ofPoint(1.0, 0.0));
    corners.push_back(ofPoint(1.0, 1.0));
    corners.push_back(ofPoint(0.0, 1.0));
    
    cvSrc[0].x = 0.0;
    cvSrc[0].y = 0.0;
    cvSrc[1].x = ofGetWidth();
    cvSrc[1].y = 0.0;
    cvSrc[2].x = ofGetWidth();
    cvSrc[2].y = ofGetHeight();
    cvSrc[3].x = 0.0;
    cvSrc[3].y = ofGetHeight();
}

//--------------------------------------------------------------
void ofApp::update()
{
    if (ofGetFrameNum() > 200) {
        layer->changeVideo("movie.mov");
    }

    layer->update();

}

//--------------------------------------------------------------
void ofApp::draw() {
    
    // Draw videos into buffers
    layer->draw();

    warp();
    
    // Draw distortable image frame
    ofSetColor(255, 0, 0, 100);
    ofBeginShape();
    for (int i=0; i<corners.size(); i++) {
        ofVertex(cvDst[i].x, cvDst[i].y);
    }
    ofEndShape(true);
    
    // Draw corner handles
    for (int i=0; i<corners.size(); i++) {
        ofSetColor(255);
        if (i == selectedCorner) {
            ofSetColor(0, 255, 255);
        }
        ofEllipse(cvDst[i].x, cvDst[i].y, 5, 5);
    }
    
    warp();

    ofPushMatrix();
        // Warp the matrix!
        glMultMatrixf(warpMatrix);

        // Pour out buffer
         layer->pourFbo();
    ofPopMatrix();

    if (showHud) {
        ofSetColor(25);
        ofRect(0, 0, 400, ofGetHeight());
    }
}

void ofApp::warp() {
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

void ofApp::exit() {
    fprintf(stderr, "τέλος");
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    switch (key) {
        case 'i':
            showHud = !showHud;
            break;
        case '+':
            corners.push_back(ofPoint(ofGetWidth()/2, ofGetHeight()/2));
            break;
        case '-':
            if (corners.size() > 3) {
                corners.erase(corners.end());
            }
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    if (selectedCorner >=0) {
        corners[selectedCorner].x = (float) x/ofGetWidth();
        corners[selectedCorner].y = (float) y/ofGetHeight();
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    float nearest = 25.0;

    selectedCorner = -1;
    
    for (int i=0; i<corners.size(); i++) {
        float distX = corners[i].x - (float) x/ofGetWidth();
        float distY = corners[i].y - (float) y/ofGetHeight();
        float dist = sqrt(distX*distX + distY*distY);
        
        if(dist < nearest && dist < 25){
            selectedCorner = i;
            nearest = dist;
        }
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    selectedCorner = -1;
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