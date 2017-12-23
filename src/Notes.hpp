//
//  Notes.hpp
//  swarm
//
//  Created by Becky Johnson on 23/12/2017.
//
//

#ifndef Notes_hpp
#define Notes_hpp

#include <stdio.h>
#include "ofMain.h"


class Notes {
    
    
public:
    
    int n;
    int x;
    float freq;
    
    int activated = 0;
    
    char letter;
    
    Notes(int _n, int _x, char _letter) {
        n  = _n;
        x = _x;
        letter = _letter;
    }
    
    
    void setup();
    void calculateFreq(int n);
    void display();
    void setActivated();

    
};
#endif /* Notes_hpp */
