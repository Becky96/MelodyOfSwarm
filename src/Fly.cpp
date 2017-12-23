//
//  Fly.cpp
//  swarm
//
//  Created by Becky Johnson on 01/12/2017.
//
//

#include "Fly.hpp"


void Fly::display() {
    
    ofSetColor(255, 100, 0);
    ofDrawEllipse(x, ofGetHeight()/2, 5, 5);
    
}