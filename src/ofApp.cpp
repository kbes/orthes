#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    fprintf(stderr, "αρχίζοντας\n");
    ofBackground(0);
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofEnableSmoothing();

    layer = new ofLayer("sample.mov");
}

//--------------------------------------------------------------
void ofApp::update()
{
    if (ofGetFrameNum() % 300 == 0) {
        layer->changeVideo("sample2.mov");
    } else if (ofGetFrameNum() % 150 == 0) {
        layer->changeVideo("sample.mov");
    }

    layer->update();
}

//--------------------------------------------------------------
void ofApp::draw() {
    
    // Draw videos into buffers
    layer->draw();

    // Pour out buffer
    layer->pourFbo();

    if (showHud) {
        ofSetColor(25);
        ofRect(0, 0, 400, ofGetHeight());
    }
}

void ofApp::exit() {
    fprintf(stderr, "τέλος");
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    switch (key) {
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
    layer->mouseDragged(x, y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    layer->mousePressed(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    layer->releaseCorner();
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