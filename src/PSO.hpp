//
//  PSO.hpp
//  swarm
//
//  Created by Becky Johnson on 23/12/2017.
//
//

#ifndef PSO_hpp
#define PSO_hpp

#include <stdio.h>
#include "ofMain.h"
#include "Particle.hpp"


class PSO {
    
    
    
public:
    
    void setup();
    void run();
    void display();
    void fitness();
    void checkPersonalBest();
    void calculateBest();
    void updateParticles();
    void mean();

    
    vector<Particle*> particles;
    int N = 10;
    float con = 0.0984;
    float c1, c2;
    float r1, r2;
    Particle best;
    
    int numEvaluations = 2000;
    int currentEvaluation = 0;
    
    ofVec2f target;

    
    int width, height;

    
     int activated;
    
};


#endif /* PSO_hpp */
