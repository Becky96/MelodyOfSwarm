#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    gui->setAssetPath("");
    
    sampleRate = 44100;
    bufferSize = 512;
    
    rhythm = new Rhythm();
    
    //GUI
    play = new ofxDatGuiButton("Play");
    play->setWidth(75);
    play->setPosition(350, 30);
    play->onButtonEvent(this, &ofApp::onButtonEvent);
    components.push_back(play);
    
    
    //ENVELOPE
    //Setup Envelope
    env.setAttack(500);
    env.setDecay(1);
    env.setSustain(1);
    env.setRelease(1000);
    
    rhythm->setup();
    
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    ofSoundStreamSetup(2,0,this, sampleRate, bufferSize, 4);
    
    
    pso.setup();
    dfo.setup();
    
    
    float x = ofGetWidth()/8;
    //C
    Notes * n = new Notes(40, x, 'C');
    notes.push_back(n);
    
    //D
    n = new Notes(42, x*2, 'D');
    notes.push_back(n);
    
    //E
    n = new Notes(44, x*3, 'E');
    notes.push_back(n);
    
    //F
    n = new Notes(45, x*4, 'F');
    notes.push_back(n);
    
    //G
    n = new Notes(47, x*5, 'G');
    notes.push_back(n);
    
    //A
    n = new Notes(49, x*6, 'A');
    notes.push_back(n);
    
    //B
    n = new Notes(51, x*7, 'B');
    notes.push_back(n);
    
    //C
    n = new Notes(52, x*8, 'C');
    notes.push_back(n);
    
    frequencies[0] = pow(pow(2, 1/12.0), 40-49) * 440;
    frequencies[1] = pow(pow(2, 1/12.0), 42-49) * 440;
    frequencies[2] = pow(pow(2, 1/12.0), 44-49) * 440;
    frequencies[3] = pow(pow(2, 1/12.0), 45-49) * 440;
    frequencies[4] = pow(pow(2, 1/12.0), 47-49) * 440;
    frequencies[5] = pow(pow(2, 1/12.0), 49-49) * 440;
    frequencies[6] = pow(pow(2, 1/12.0), 51-49) * 440;
    frequencies[7] = pow(pow(2, 1/12.0), 52-49) * 440;


}

//--------------------------------------------------------------
void ofApp::update(){

    //Updating all GUIs
    
    for (int i = 0; i < components.size(); i++) {
        components[i]->update();
    }
    
    rhythm->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    //Drawing ofApp GUIs
    for (int i = 0; i < components.size(); i++) {
        components[i]->draw();
    }
    
    pso.run();
    //dfo.run();
    
    rhythm->draw();
    
    for (int i = 0; i < notes.size(); i++) {
        notes[i]->display();
    
    }
    
    //activateNote = pso.activated;
    activateNote = dfo.activated;
    
    notes[activateNote]->activated = 1;
    
    activatedNoteNum = notes[activateNote]->n;
    activatedNoteLetter = notes[activateNote]->letter;
    
    calculateNotes(activatedNoteNum);
    
    
    //cout << "BEst velocity: " << pso.best.vX << endl;
    
    for (int i = 0; i < notes.size(); i++) {
        
        if (i != activateNote) {
            notes[i]->activated = 0;
            
        }
    }
    

}

//--------------------------------------------------------------

void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
    
    
    //playSound determined by Play button.
    if (playSound == true) {
        
       
        for (unsigned i = 0; i < bufferSize; i++) {
            
            
            //8 hertz = 120 bmp
            currentCount = (int)timer.phasor(8);
            
            //mix = 0;
           
            
            //Check if count has changed
            if (lastCount!=currentCount) {
                
                
                env.trigger = rhythm->rhythm[playHead%rhythm->steps];
                
                //cout << frequency << endl;
                playHead++;
                lastCount=0;
                
                
                //cout << "PLAYING" << endl;
                if (env.trigger == 1) {
                    freqNum++;
                    frequency = freqs[freqNum%4];
                    
                    
                    //env.setRelease(abs(pso.best.vX*10000));
                    
                    //env.set
                }

                
                
            }
            
            

            
            //cout << frequency << endl;
            
            //Outputting combination of envelopes and oscillators.
            output[i*nChannels]= (env.adsr(1., env.trigger)*osc.sinewave(frequency))/2.;
            output[i*nChannels+1]= output[i*nChannels];
            

            env.trigger = 0;

            
        }
        
        
        
        
        
    }
    
    
}


//--------------------------------------------------------------
//Handler for ofApp GUI.
void ofApp::onButtonEvent(ofxDatGuiButtonEvent e) {
    
    //Set sound to start to play button by inverting boolean playSound on each click.
    if (e.target == play && playSound == false) {
        play->setLabel("Stop");
        playSound = true;
        
        //Resetting ticker and playHead to reset phase when playing again.
        playHead = 0;
        
        
        for (int i = 0; i < rhythm->steps; i++) {
            cout << rhythm->rhythm[i] << endl;
        }
        
    } else if (e.target == play && playSound == true) {
        play->setLabel("Play");
        playSound = false;
        
    }
}


void ofApp::calculateNotes(int n) {
    
    float freqRoot, freqThird, freqFifth;
    
    freqRoot = n;
    
    //Calculating third
    
    if (n % 12 == 6 || n % 12 == 8 || n % 12 == 3 || n % 12 == 1) {
        
        //cout << "1st mod" << endl;
        freqThird = n+3;
        
        
    } else if (n % 12 == 4 || n % 12 == 9 || n % 12 == 11) {
        
        //cout << "2nd mod" << endl;
        freqThird = n+4;
    }
    /*
    //Calculating fifth
    if (n % 12 != 11) {
        
        freqFifth = n+6;
    } else {
        freqFifth = n+7;
    }*/
    
    freqFifth = int(ofRandom(40, 52));
    
    freqs[0] = pow(pow(2, 1/12.0), n-49) * 440;
    freqs[1] = pow(pow(2, 1/12.0), freqThird-49) * 440;
    freqs[2] = pow(pow(2, 1/12.0), freqFifth-49) * 440;
    freqs[3] = pow(pow(2, 1/12.0), freqThird-49) * 440;
    cout << activatedNoteLetter << endl;
    //cout << activatedNoteNum << endl;
   // cout << n << endl;
    //cout << freqThird << endl;
    //cout << freqFifth << endl;
    for (int i =0 ; i < 4; i++) {
        
        cout << i << ": " << freqs[i] << endl;
    }
}

void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
