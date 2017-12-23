//
//  DFO.cpp
//  swarm
//
//  Created by Becky Johnson on 23/12/2017.
//
//

#include "DFO.hpp"

void DFO::setup() {
    
    for (int i = 0; i < N; i++) {
        
        
        Fly * f = new Fly(ofRandom(ofGetWidth()));
        
        flies.push_back(f);
    }
    
    
    target.x = ofRandom(ofGetWidth());
    target.y = ofGetHeight()/2;
}


void DFO::run() {
    
    
    

    for (int i = 0; i < flies.size(); i++) {
        
        flies[i]->display();
        
       
        
        
    }
    
    ofDrawEllipse(target.x, target.y, 15, 15);
    
    
    
    checkPos();
    
    fitness();
    
    calculateBestFly();
    
    calculateBestNeighbour();
    
    updateFly();
    
    mean();
    
    
    //Resetting each particle
    if (ofGetFrameNum() % 250 == 0) {
        
              target.x=ofRandom(ofGetWidth());
        //target.y=ofRandom(height);
    }


    
    
}

//Check that fly is within bounds of sketch window
void DFO::checkPos() {
    
    for (int i = 0; i < flies.size(); i++) {
        if (flies[i]->x < 0 || flies[i]->x > ofGetWidth()) {
            flies[i]->x = ofRandom(ofGetWidth());
            flies[i]->fitness = 0;
        }
       }
}

void DFO::fitness() {
    
    
    for (int i = 0; i < flies.size(); i++) {
    float fitnessSum = 0;
    

            
            fitnessSum += abs(target.x-flies[i]->x);
            
            
        
        flies[i]->fitness = fitnessSum;
    }

}


void DFO::calculateBestFly() {
    
    float bestFitness = 200000.;
    
    for (int i = 0; i < flies.size(); i++) {
        
        if (flies[i]->fitness < bestFitness) {
            
            bestFitness = flies[i]->fitness;
            bestFlyX = flies[i]->x;
        }
    }
    
}



void DFO::calculateBestNeighbour() {
    
    for (int i = 0; i < flies.size(); i++) {
        
     
        
        int index1, index2;
        
        if (i == 0) {
            index1 = N-1;
            index2 = i+1;
        } else if (i == N-1) {
            index1 = i-1;
            index2 = 0;
        } else {
            
            index1 = i-1;
            index2 = i+1;
        }
        
        if (flies[index1]->fitness < flies[index2]->fitness) {
            
            flies[i]->bestNeighbourX = flies[index1]->x;
        } else {
            
            flies[i]->bestNeighbourX = flies[index2]->x;
        }
    }
    
    
}


void DFO::updateFly() {
    
    
    //Loop through all flies
    for (int i = 0; i < flies.size(); i++) {

            float r = ofRandom(1);
            
            //Reset fly
            if (r < dt) {
                
                
                flies[i]->x = ofRandom(ofGetWidth());
                //Update fly
            } else {
                
                flies[i]->x = int(flies[i]->bestNeighbourX + ofRandom(1) * (bestFlyX - flies[i]->x));
            }
        }
    
}



void DFO::mean() {
    float mean;
    for (int i = 0; i < N; i++) {
        mean+=flies[i]->x;
        
    }
    
    mean/=N;
    
    ofSetColor(0, 255, 0);
    ofDrawEllipse(mean, ofGetHeight()/2, 25, 25);
    
    
    //int distance = width;
    
    vector<float> distance;
    
    for (int i = 1; i <= 8; i++)  {
        distance.push_back(ofGetWidth()/8*i);
        
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

