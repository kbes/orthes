#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    fprintf(stderr, "αρχίζοντας\n");
    ofBackground(0);
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofEnableSmoothing();

    layers.push_back(new ofLayer("sample.mov"));
}

//--------------------------------------------------------------
void ofApp::update()
{
    for (int i=0; i<layers.size(); i++) {
        layers[i]->update();
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
    
    // Draw videos into buffers
    for (int i=0; i<layers.size(); i++) {
        layers[i]->draw();
    }
    
    // Pour out buffer
    for (int i=0; i<layers.size(); i++) {
        layers[i]->pourFbo();
    }
}

void ofApp::exit() {
    fprintf(stderr, "τέλος");
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    switch (key) {
        case '+':
//            corners.push_back(ofPoint(ofGetWidth()/2, ofGetHeight()/2));
            break;
        case '-':
//            if (corners.size() > 3) {
//                corners.erase(corners.end());
//            }
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
    for (int i=0; i<layers.size(); i++) {
        layers[i]->mouseDragged(x, y);
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    for (int i=0; i<layers.size(); i++) {
        layers[i]->mousePressed(x, y);
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    for (int i=0; i<layers.size(); i++) {
        layers[i]->releaseCorner();
    }
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