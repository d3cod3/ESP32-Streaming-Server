#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetFrameRate(24);
    ofSetWindowTitle("ESP-32 Video Streaming");

    grabber = make_shared<ofx::Video::IPVideoGrabber>();
    grabber->setURI("http://192.168.1.159:81/stream");
    grabber->connect();

    osc_port            = 12345;
    osc_host            = "localhost";
    osc_sender.setup(osc_host.c_str(),osc_port);

    _tempPixels         = new ofPixels();
    _grayPixels         = new ofPixels();
    _tempTexture        = new ofTexture();
    colorImg            = new ofxCvColorImage();
    grayImg             = new ofxCvGrayscaleImage();

    _tempImage          = new ofImage();
    _tempBuffer         = new ofBuffer();

    _tempPixels->allocate(800,600,3);
    _grayPixels->allocate(800,600,1);
    colorImg->allocate(800,600);
    grayImg->allocate(800,600);
}

//--------------------------------------------------------------
void ofApp::update(){

    grabber->update();

    grabber->getTexture().readToPixels(*_tempPixels);

    colorImg->setFromPixels(*_tempPixels);
    colorImg->updateTexture();

    *grayImg = *colorImg;
    grayImg->updateTexture();

    *_tempTexture = grayImg->getTexture();

    ofxOscMessage m;
    m.setAddress("/labelimage");

    _tempTexture->readToPixels(*_grayPixels);
    m.addFloatArg(800);
    m.addFloatArg(600);
    _tempImage->setFromPixels(_grayPixels->getData(),800,600,OF_IMAGE_GRAYSCALE);
    m.addInt32Arg(OF_IMAGE_GRAYSCALE);
    _tempImage->save(*_tempBuffer);
    m.addBlobArg(*_tempBuffer);
    _tempBuffer->clear();

    osc_sender.sendMessage(m);

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);

    ofSetColor(255);

    _tempImage->draw(0,0,800,600);

}

//--------------------------------------------------------------
void ofApp::exit(){

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
