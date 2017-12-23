//
//  Notes.cpp
//  swarm
//
//  Created by Becky Johnson on 23/12/2017.
//
//

#include "Notes.hpp"


void Notes::setup() {
    
    calculateFreq(n);
    
}


//--------------------------------------------------------------


void Notes::calculateFreq(int n) {
    
    freq = pow(pow(2, 1/12.0), n-49) * 440;
    
    
}

void Notes::display() {
    
    
    if (activated == 0) {
    ofSetColor(255);
        
    } else {
        
        ofSetColor(0, 255, 0);
    }
    
    ofDrawLine(x, ofGetHeight()/2-15, x, ofGetHeight()/2+15);
    
    
    
}

void Notes::setActivated() {
    
    activated = 1;
}