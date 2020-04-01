# Central System code (running on OSX 10.13 HIGH SIERRA)

## Dependencies

- openFrameworks
- [ofxIpVideoGrabber](https://github.com/bakercp/ofxIpVideoGrabber)
- ofxOpenCv
- ofxOsc

## Description

OF code to receive video streaming from ESP-32 hardware module (ip streaming), extract frame by frame, applying some compositing over the image (text, graphics, etc), converting them to 1280x720 GL_LUMINANCE pixel data (grayscale), and sending them via OSC blob messages at one single specified IP.

## TODO

Add sync logic to sequentially send frames to 6 different machines IP (raspberry pi 4 version b, controlling two HD screen each)
Add graphics changes over time and a still to define logic.
