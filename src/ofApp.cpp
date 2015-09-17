#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    fprintf(stderr, "αρχίζοντας\n");
    ofBackground(0);
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofEnableSmoothing();
    
    showHud = false;

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
    
    if (showHud) {
        ofSetColor(0, 235);
        ofRect(0, 0, 400, ofGetHeight());
    }
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
//            corners.push_back(ofPoint(ofGetWidth()/2, ofGetHeight()/2));
            layers.push_back(new ofLayer("sample2.mov"));
            break;
        case '-':
            if (layers.size() > 1) {
                layers.erase(layers.end());
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