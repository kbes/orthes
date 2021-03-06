#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    fprintf(stderr, "αρχίζοντας\n");
    ofBackground(0);
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofEnableSmoothing();
    ofHideCursor();

    shader.load("shaders/shader.vert", "shaders/shader.frag");

    layers.push_back(new ofLayer(0, "sample.mov"));
    
    // The hooman interface
    gui.setup();
    gui.add(layers[0]->getLabel());
    gui.add(layers[0]->getShowVideo());
    gui.add(layers[0]->getShowWarp());
    gui.add(layers[0]->getShowMask());
    
    showHud = false;
    
    videoFolder = new ofDirectory("/videos");
    videoFolder->listDir();
    
    if (videoFolder->isDirectory()) {
        fprintf(stderr, "path\n");
    }
    
    for(int i = 0; i < videoFolder->numFiles(); i++){
        ofLogNotice(videoFolder->getPath(i));
        fprintf(stderr, "path");
    }
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
        gui.draw();
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
            layers.push_back(new ofLayer(layers.size(), "sample2.mov"));
            gui.add(layers[layers.size()-1]->getLabel());
            gui.add(layers[layers.size()-1]->getShowVideo());
            gui.add(layers[layers.size()-1]->getShowWarp());
            gui.add(layers[layers.size()-1]->getShowMask());
            break;
        case '-':
            if (layers.size() > 1) {
                delete layers[layers.size()];
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
    ofShowCursor();
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