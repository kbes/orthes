//
//  ofLayer.cpp
//  quadWarp
//
//  Created by Christian Geick on 16.09.15.
//
//

#include "ofLayer.h"

ofLayer::ofLayer(string fileName) {
    fbo.allocate(ofGetWidth(), ofGetHeight());
    video = new ofQTKitPlayer();
    video->loadMovie(fileName, OF_QTKIT_DECODE_TEXTURE_ONLY);
    video->play();
}

void ofLayer::update() {
    video->update();
}

void ofLayer::draw() {
    fbo.begin();
        video->draw(0, 0, ofGetWidth(), ofGetHeight());
    fbo.end();
}

void ofLayer::pourFbo() {
    ofSetColor(255);
    fbo.draw(0, 0);
}

void ofLayer::changeVideo(string fileName) {
    video->closeMovie();
    delete video;
    video = new ofQTKitPlayer();
    video->loadMovie(fileName, OF_QTKIT_DECODE_TEXTURE_ONLY);
    video->play();
}