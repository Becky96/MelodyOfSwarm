//
//  Particle.hpp
//  swarm
//
//  Created by Becky Johnson on 23/12/2017.
//
//

#ifndef Particle_hpp
#define Particle_hpp

#include <stdio.h>
#include "ofMain.h"

class Particle {
    
public:
    float x, y;
    float vX, vY; //velocities
    float bestX, bestY, bestFit;
    float fitness;
    
    Particle() {
        
        x = ofRandom(ofGetWidth());
        //y = ofRandom(ofGetHeight());
        vX = ofRandom(-20, 20);
        //vY = ofRandom(-20, 20);
        bestX = 1000000;
        //bestY = 1000000;
        bestFit = 1000000;
        
        
    }
    
    
    void display();
    
    
    
};

#endif /* Particle_hpp */
