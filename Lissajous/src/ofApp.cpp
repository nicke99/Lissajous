#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    soundStream.printDeviceList();
    
    int bufferSize = 1024;

    mix.assign(bufferSize, 0.0);
    left.assign(bufferSize, 0.0);
    right.assign(bufferSize, 0.0);
    
    ofSoundStreamSettings settings;
    
    auto devices = soundStream.getMatchingDevices("Existential Audio Inc.: BlackHole 2ch");
    
    //auto devices = soundStream.getMatchingDevices("Apple Inc.: MacBook Air Microphone");
    
    if(!devices.empty()){
        settings.setInDevice(devices[0]);
    }

    settings.setInListener(this);
    settings.sampleRate = 44100;
    settings.numOutputChannels = 0;
    settings.numInputChannels = 2; //1 for mic else 2
    settings.bufferSize = bufferSize;
    soundStream.setup(settings);
    
    ofSetLineWidth(3);
    
    ofSetBackgroundAuto(false);
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
    //fbo.begin();
    
    //frameCount++;
    //if(frameCount >20)
      //  return;
    
    //ofClear(10, 10);
    line.clear();
    
    //if (line.size() > 20){
    //    line.getVertices().erase(
    //                            line.getVertices().begin()
    //                            );
    //}
    

    
    int displayWidth = ofGetWindowWidth();
    int displayHeight = ofGetWindowHeight();
    
    //ofEnableBlendMode(OF_BLENDMODE_SUBTRACT);
    //            //ofSetColor(1);
    //            ofSetRectMode(OF_RECTMODE_CORNER);
    //            ofFill();
    //            ofDrawRectangle(0, 0, displayWidth, displayHeight);
    //            ofDisableBlendMode();
    
    ofFill();
    ofSetColor(0,0,0, 15);
    ofDrawRectangle(0,0,displayWidth,displayHeight);
    
    ofSetColor(255,255,255, 255);
    
    
    
    for (unsigned int i = 0; i < mix.size(); i++)
    {
        line.lineTo(displayWidth/2 + left[i]*(displayWidth), displayHeight/2 + delayed[i]*(displayHeight));
        
        //if(mix[i]<0.1 || rightDelayed[i]<0.1)
        //    continue;
        //ofDrawLine(displayWidth/2 + mix[i]*(displayWidth), displayHeight/2 + rightDelayed[i]*(displayHeight),displayWidth/2 + mix[i+1]*(displayWidth), displayHeight/2 + rightDelayed[i+1]*(displayHeight));
    }
    
    line.draw();
    
    //fbo.end();
    //fbo.draw(0,0);
}

//--------------------------------------------------------------
void ofApp::audioIn(ofSoundBuffer & input){
    
    for (size_t i = 0; i < input.getNumFrames(); i++){
        left[i]=input[i*2];
        right[i]=input[i*2+1];
        mix[i] = (input[i*2] + input[i*2+1])/3;
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
    //ofPoint pt;
    //    pt.set(x,y);
    //    line.addVertex(pt);

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
