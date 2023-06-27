#pragma once

#include "ofMain.h"
#include "ofxDepthCamera.h"

#ifdef OFX_DEPTH_CAMERA_ASUS_PRO_V1
#include "ofxNI2.h"

namespace ofxDepthCam {
class AsusXtionProV1 : public Base {

public:
    AsusXtionProV1();
    ofxNI2::Device& getSensor();

    // Set useColor = true to enable color data
    // When set to false, no color (or IR) data are grabbed
    void setup(int deviceId = 0, bool useColor = false);
    void close();
    void update();

    ofVec3f getWorldCoordinateAt(int x, int y);
    ofxNI2::Grayscale gray;

protected:
    ofxNI2::Device device;
    ofxNI2::IrStream ir;
    ofxNI2::DepthStream depth;
    ofxNI2::ColorStream color;



    bool useColor;
};
}


/*namespace ofxDepthCam {
    using namespace ofxDepthCam;

    class AsusXtionProV1: public Base {

    public:
        AsusXtionProV1() {
            frameRate = 30;
            depthWidth = 640;
            depthHeight = 480;
            colorWidth = 640;
            colorHeight = 480;

            maxDepth = 9 * 1000;
        }

        ofxNI2::Device& getSensor() {
            return device;
        }

        void setup(int deviceId = 0, bool useColor = false) {

            // setup device
            device.setup();
            if (depth.setup(device))
            {
                depth.setSize(depthWidth, depthHeight);
                depth.setFps(30);
                depth.start();

                //gray.setup(depth);
            } else {
                ofLog() << "cannot init depth information";

            }

            if (ir.setup(device)) // only for xtion device (OpenNI2-FreenectDriver issue)
            {
                ir.setSize(depthWidth, depthHeight);
                ir.setFps(30);
                ir.start();
            }
        }

        void close()
        {
            device.exit();
        }

        void update() {
            device.update();
            depth.updateTextureIfNeeded();
            ir.updateTextureIfNeeded();


            bNewFrame = true;

            //depthPixels.setFromPixels(&depth.getPixelsRef(), depth.getWidth(), depth.getHeight(), OF_IMAGE_GRAYSCALE);
            const unsigned short* px = depth.getPixelsRef().getData();
            //px = &depth.getPixelsRef();
            depthPixels.setFromPixels(px, depth.getWidth(), depth.getHeight(),OF_IMAGE_GRAYSCALE);
        }

        int maxDepth() {
            return 10000; // arbitrary value check xtion ver 1 documents....
        }

        ofVec3f getWorldCoordinateAt(int x, int y) {
            return depth.getWorldCoordinateAt(x, y);
        }

    protected:
        ofxNI2::Device device;
        ofxNI2::IrStream ir;
        ofxNI2::DepthStream depth;


        ofFbo depthFbo;

    };
}*/
#endif
