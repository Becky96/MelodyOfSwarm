//
//  Rhythm.hpp
//  swarm
//
//  Created by Becky Johnson on 01/12/2017.
//
//

#ifndef Rhythm_hpp
#define Rhythm_hpp

#include <stdio.h>
#include "ofMain.h"
#include "Fly.hpp"
#include "ofxDatGui.h"
#include "ofxMaxim.h"

class Rhythm {
    
public:
    
    //Rhythm();
    
    
    vector<Fly> rhythmPop;
    
    void setup();
    void update();
    void draw();
    
    //Rhythm generation.
    void compute_bitmap(int steps, int beats);
    void build_string(int level);
    
    int divisor;
    int rhythm[16];
    int remainder[16];
    int count[16];
    int level = 0;
    int pulses;
    int pauses;
    int patit=0;
    
    int steps = 16;
    int beats = 4;

    
    
    
    //Sound
    maxiEnv env;
    maxiOsc osc;
    
    //GUI
    void onSliderEvent(ofxDatGuiSliderEvent e);
    vector<ofxDatGuiComponent*> components;
    ofxDatGui* gui;
    ofxDatGuiSlider* stepsSlider;
    ofxDatGuiSlider* beatsSlider;
    
    ofParameter<int> ofStepsInt;
    ofParameter<int> ofBeatsInt;
    
    int x = 50;
    int y = 25;
    
    bool resetPhase = false;
    
    
    
};

#endif /* Rhythm_hpp */
