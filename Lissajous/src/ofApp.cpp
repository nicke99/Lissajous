#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    soundStream.printDeviceList();
    
    int bufferSize = 1024;

    left.assign(bufferSize, 0.0);
    right.assign(bufferSize, 0.0);
    
    ofSoundStreamSettings settings;
    
    auto devices = soundStream.getMatchingDevices("MOTU, Inc: M4");
    
    //auto devices = soundStream.getMatchingDevices("Existential Audio Inc.: BlackHole 2ch");
    //auto devices = soundStream.getMatchingDevices("Apple Inc.: MacBook Air Microphone");
    
    if(!devices.empty()){
        settings.setInDevice(devices[0]);
    }

    numChannels = 8; //1 for mic else 8 for Motu M4
    inputChannel = 4;//0 for blackhole, 4 for moto loopback
    
    settings.setInListener(this);
    settings.sampleRate = 44100;
    settings.numOutputChannels = 0;
    settings.numInputChannels = numChannels;
    settings.bufferSize = bufferSize;
    soundStream.setup(settings);
    
    ofSetLineWidth(3);
    
    ofSetBackgroundAuto(false);
    syphonServer.setName("Lisajous");
}

//--------------------------------------------------------------
void ofApp::update(){

}

float ofApp::delay(float in){
    delayBuff[bufPosn] = in;
    
    if(++bufPosn == delaySize)
          bufPosn=0;
    
    return delayBuff[bufPosn];
}


//--------------------------------------------------------------
void ofApp::draw(){
    line.clear();
    
    int displayWidth = ofGetWindowWidth();
    int displayHeight = ofGetWindowHeight();
    //rotation++;
    
    //ofRotateDeg(rotation,displayWidth/2,displayHeight/2,0);
    ofFill();
    ofSetColor(0,0,0, 15);
    ofDrawRectangle(0,0,displayWidth,displayHeight);
    
    ofSetColor(255,255,255, 255);
    
    for (unsigned int i = 0; i < left.size(); i++)
        line.lineTo(displayWidth/2 + left[i]*(displayWidth), displayHeight/2 + delayed[i]*(displayHeight));
    
    line.draw();
    
    syphonServer.publishScreen();
}

//--------------------------------------------------------------
void ofApp::audioIn(ofSoundBuffer & input){
    
    for (size_t i = 0; i < input.getNumFrames(); i++){
        left[i]=input[i*numChannels+inputChannel];
        right[i]=input[i*numChannels+inputChannel+1];
        
        delayed[i] = delay(right[i]);
    }
}

//--------------------------------------------------------------
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
