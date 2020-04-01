#pragma once

#include "ofMain.h"

#include "ofxOpenCv.h"
#include "ofxOsc.h"
#include "IPVideoGrabber.h"

typedef enum {
   FRAMESIZE_QQVGA,    // 160x120
   FRAMESIZE_QQVGA2,   // 128x160
   FRAMESIZE_QCIF,     // 176x144
   FRAMESIZE_HQVGA,    // 240x176
   FRAMESIZE_QVGA,     // 320x240
   FRAMESIZE_CIF,      // 400x296
   FRAMESIZE_VGA,      // 640x480
   FRAMESIZE_SVGA,     // 800x600
   FRAMESIZE_XGA,      // 1024x768
   FRAMESIZE_SXGA,     // 1280x1024
   FRAMESIZE_UXGA,     // 1600x1200
   FRAMESIZE_QXGA,     // 2048x1536
   FRAMESIZE_INVALID
} framesize_t;


class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void exit();

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


    shared_ptr<ofx::Video::IPVideoGrabber> grabber;
    ofxCvColorImage                 *colorImg;
    ofxCvGrayscaleImage             *grayImg;

    ofPixels                        *_tempPixels;
    ofPixels                        *_grayPixels;
    ofTexture                       *_tempTexture;
    ofImage                         *_tempImage;
    ofBuffer                        *_tempBuffer;

    ofxOscSender            osc_sender;
    string                  osc_host;
    int                     osc_port;

};
