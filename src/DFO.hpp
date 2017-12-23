//
//  DFO.hpp
//  swarm
//
//  Created by Becky Johnson on 23/12/2017.
//
//

#ifndef DFO_hpp
#define DFO_hpp

#include <stdio.h>
#include "ofMain.h"
#include "Fly.hpp"

class DFO {
    
    
public:
    

    
    void setup();
    void run();
    void checkPos();
    void fitness();
    void calculateBestFly();
    void calculateBestNeighbour();
    void updateFly();
    void mean();
    
    
    vector<Fly*> flies;
    int N = 50; //Number of flies
    
    float bestFlyX;
    
    
    float dt = 0.01;    //disturbance threshold
    
    ofVec2f target;
    
    int activated;
};

#endif /* DFO_hpp */
