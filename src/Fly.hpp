//
//  Fly.hpp
//  swarm
//
//  Created by Becky Johnson on 01/12/2017.
//
//

#ifndef Fly_hpp
#define Fly_hpp

#include <stdio.h>
#include "ofMain.h"

class Fly {
    
public:
    float x, y;
    float fitness;
   
    
    Fly(float _x) {
        
       
        x = _x;
        
        
    }
    
    
    void display();
    
    
    float bestNeighbourFitness;
    float bestNeighbourX;
};


#endif /* Fly_hpp */
