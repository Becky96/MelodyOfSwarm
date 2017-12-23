//
//  Rhythm.cpp
//  swarm
//
//  Created by Becky Johnson on 01/12/2017.
//
//

#include "Rhythm.hpp"


void Rhythm::setup() {
    
    steps = 16;
    beats = 4;
    
    //Generate rhythm sequence
    compute_bitmap(steps, beats);
    
    //GUI
    //Number of steps in sequence
    stepsSlider = new ofxDatGuiSlider(ofStepsInt.set("Steps", 16, 1, 16));
    stepsSlider->setPosition(x, y);
    stepsSlider->onSliderEvent(this, &Rhythm::onSliderEvent);
    components.push_back(stepsSlider);
    y+=stepsSlider->getHeight();
    
    //Number of beats in sequence
    beatsSlider = new ofxDatGuiSlider(ofBeatsInt.set("Beats", 4, 1, 16));
    beatsSlider->setPosition(x, y);
    beatsSlider->onSliderEvent(this, &Rhythm::onSliderEvent);
    components.push_back(beatsSlider);
    y+=beatsSlider->getHeight();
    
    
    
    //ENVELOPE
    //Setup Envelope
    env.setAttack(500);
    env.setDecay(1);
    env.setSustain(1);
    env.setRelease(1000);
    
    
}


void Rhythm::update() {
    
    for (int i = 0; i < components.size(); i++) {
        components[i]->update();
    }
    
    
}



void Rhythm::draw() {
    
    
    for (int i = 0; i < components.size(); i++) {
        components[i]->draw();
    }
    
    
}

//--------------------------------------------------------------
//Handler for all Ring sliders.
void Rhythm::onSliderEvent(ofxDatGuiSliderEvent e) {
    
    //Changing number of steps in sequence
    if (e.target == stepsSlider) {
        
        //Resetting rhythm sequence values
        steps = e.value;
        patit = 0;
        level = 0;
        compute_bitmap(steps, beats);   //Recreate rhyhthm sequence with new number of steps
        
        
        resetPhase = true;      //Bool is monitered in ofApp::draw to reset phases of all Ring oscillators when steps is changed for any Ring.
        
        
        //Changing number of beats in sequence
    } else if (e.target == beatsSlider) {
        
        //Resetting rhythm sequence values
        beats = e.value;
        patit = 0;
        level = 0;
        compute_bitmap(steps, beats);   //Recreate rhythm sequence with new number of beats

        
        resetPhase = true;      //Bool is monitered in ofApp::draw to reset phases of all Ring oscillators when steps is changed for any Ring.
        
        
    }
    
    
}


//--------------------------------------------------------------

void Rhythm::compute_bitmap (int steps, int beats)
{
    /*---------------------
     * First, compute the count and remainder arrays
     */
    
    if (beats > steps) {
        beats= steps;
    }
    divisor = steps - beats;
    remainder[0] = beats;
    level = 0;
    while (remainder[level] > 1) {
        count[level] = divisor / remainder[level];
        remainder[level+1] = divisor % remainder[level];
        divisor = remainder[level];
        level = level + 1;
    }
    
    count[level] = divisor;
    build_string (level);
}

//--------------------------------------------------------------

void Rhythm::build_string (int level) {
    if (level == -1) {
        rhythm[patit]=0; //0 into array rhythm
        patit=patit+1;      //plus 1
    } else if (level == -2) {
        
        rhythm[patit]=1; //1 into array rhythm
        patit=patit+1;      //plus 1
        
    } else {
        for (int i = 0; i < count[level]; i++)
            build_string(level-1);
        if (remainder[level] !=0)
            build_string(level-2);
    }//end else
}//end build_string
//--------------------------------------------------------------
