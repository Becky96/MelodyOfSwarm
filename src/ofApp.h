#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "ofxDatGui.h"
#include "Rhythm.hpp"
#include "PSO.hpp"
#include "Notes.hpp"
#include "DFO.hpp"
class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    
    void audioOut(float *output, int bufferSize, int nChannels);
    unsigned bufferSize;
    unsigned sampleRate;
    
    int currentCount, lastCount;
    int playHead = 0;
    double mix;
    maxiOsc timer;
    int tempo = 4;
    double frequency;
    

    //GUI
    vector<ofxDatGuiComponent*> components;
    ofxDatGui* gui;
    ofxDatGuiButton* play;
    void onButtonEvent(ofxDatGuiButtonEvent e);
    bool playSound;
    
    ofParameter<int> ofStepsInt;
    ofParameter<int> ofBeatsInt;
    
    int x = 50;
    int y = 25;
    
    
    Rhythm * rhythm;
    maxiOsc osc;
    maxiEnv env;
    
    int freqNum = 0;
    
    
    void calculateFreq();
    PSO pso;
    
    DFO dfo;
    
    vector<Notes*> notes;
    
    void calculateNotes(int n);
    
    float freqs [4];
    float frequencies [8];
    
    int activateNote;
    int activatedNoteNum;
    char activatedNoteLetter;
};
