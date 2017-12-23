//
//  PSO.cpp
//  swarm
//
//  Created by Becky Johnson on 23/12/2017.
//
//

#include "PSO.hpp"

void PSO::setup() {
    
    
    

    target = ofVec2f(width/2, height/2);
    
    //Initialising population
    for (int i = 0; i < N; i++) {
        Particle *p = new Particle();
        particles.push_back(p);
    }
    
    
    //Learning factors
    c1 = con * (4.1/2);
    c2 = c1;
    
    
    
    width = ofGetWidth();
    height = ofGetHeight();
    

}


void PSO::run() {
    
    
    
    //PSO operations
    if (currentEvaluation < numEvaluations) {
        
        display();
        fitness();
        checkPersonalBest();
        calculateBest();
        updateParticles();
        mean();
        
        
    }
    
    
    //Resetting each particle
    if (ofGetFrameNum() % 250 == 0) {
        
        best.bestFit = 10000;
        best.bestX = 10000;
        //best.bestY = 10000;
        for (int i = 0; i < N; i++) {
            
            
            
            particles[i]->x = ofRandom(width);
            //particles[i]->y = ofRandom(height);
            particles[i]->bestFit = 100000;
            particles[i]->bestX = 100000;
            //particles[i]->bestY = 100000;
            particles[i]->fitness = 10000000;
            
            
            particles[i]->vX = ofRandom(-2, 2);
            //particles[i]->vY = ofRandom(-2, 2);
            
            
            
        }
        target.x=ofRandom(width);
        //target.y=ofRandom(height);
    }
    
    if (target.x == best.bestX) {
        target.x = ofRandom(width);
    }
    
    

    
    
    display();  //Display each particle
    
    
    ofSetColor(255);
    ofDrawEllipse(target.x, height/2, 15, 15);

    
    
}

void PSO::mean() {
    float mean;
    for (int i = 0; i < N; i++) {
        mean+=particles[i]->x;
        
    }
    
    mean/=N;
    
    ofSetColor(0, 255, 0);
    ofDrawEllipse(mean, height/2, 25, 25);
    
    
    //int distance = width;
    
    vector<float> distance;
    
    for (int i = 1; i <= 8; i++)  {
        distance.push_back(width/8*i);
        
    }
    
   
    
    
    for (int i = 1; i < distance.size(); i++) {
        if (mean > distance[i-1] && distance[i]) {
            
            
            int dist1= abs(distance[i-1] - mean);
            int dist2 = abs(distance[i] - mean);
            
            if (dist1 < dist2) {
                
               activated = i-1;
            
            } else {
                activated = i;
                
            }
            
        }
    }
    
    
    
    
}


//Display each particle
void PSO::display() {
    for (int i = 0; i < N; i++) {
        
        particles[i]->display();
    }
}


//Calculate fitness of each particle (distance from target coordinates)
void PSO::fitness() {
    
    for (int i = 0; i < N; i++) {
        
        float fitnessSum = 0;
        
        
        fitnessSum = abs(target.x-particles[i]->x);
        
       // fitnessSum += abs(target.y-particles[i]->y);
        
        
        particles[i]->fitness = fitnessSum;
    }
}


//Check if particle's new position is it's best found position
void PSO::checkPersonalBest() {
    
    for (int i = 0; i < N; i++) {
        
        
        if (particles[i]->fitness < particles[i]->bestFit) {
            particles[i]->bestX = particles[i]->x;
            //particles[i]->bestY = particles[i]->y;
        }
    }
}


//Determine best particle of the population
void PSO::calculateBest() {
    
    float bestFitness = 200000.;
    
    
    
    for (int i = 0; i < particles.size(); i++) {
        
        if (particles[i]->fitness < bestFitness) {
            
            bestFitness = particles[i]->fitness;
            best = *particles[i];
        }
    }
}


//Update all particles
void PSO::updateParticles() {
    
    
    r1 = ofRandom(1);
    r2 = ofRandom(1);
    for (int i = 0; i < particles.size(); i++) {
        
        
        //Velocity update
        particles[i]->vX = con * (particles[i]->vX + (c1*r1*(particles[i]->bestX-particles[i]->x) + c2*r2*(best.bestX-particles[i]->x)));
        //particles[i]->vY = con * (particles[i]->vY + (c1*r1*(particles[i]->bestY-particles[i]->y) + c2*r2*(best.bestY-particles[i]->y)));
        
        //Position update
        particles[i]->x = particles[i]->x+particles[i]->vX;
        //particles[i]->y = particles[i]->y+particles[i]->vY;
        
        
    }
}
//--------------------------------------------------------------


