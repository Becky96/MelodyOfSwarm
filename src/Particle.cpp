//
//  Particle.cpp
//  swarm
//
//  Created by Becky Johnson on 23/12/2017.
//
//

#include "Particle.hpp"

void Particle::display() {
    
    ofSetColor(255, 100, 0);
    ofDrawEllipse(x, ofGetHeight()/2, 5, 5);
    
}