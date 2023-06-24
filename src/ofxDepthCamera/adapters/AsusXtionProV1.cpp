#include "AsusXtionProV1.h"

#ifdef OFX_DEPTH_CAMERA_ASUS_PRO_V1
using namespace ofxDepthCam;
AsusXtionProV1::AsusXtionProV1() {
    depthWidth = 640;
    depthHeight = 480;
    colorWidth = 640;
    colorHeight = 480;

    frameRate = 30;

    // Max range is sorted of hinted to be 8m in these docs, so give a bit
    // of extra padding..
    // https://msdn.microsoft.com/en-us/library/hh973078.aspx#Depth_Ranges
    maxDepth = 9 * 1000;
    this->useColor = true;
}

ofxNI2::Device& AsusXtionProV1::getSensor() {
    return device;
}

void AsusXtionProV1::setup(int deviceId, bool useColor) {
    this->useColor = useColor;

    // setup device
    device.setup();
    if (depth.setup(device))
    {
        depth.setSize(depthWidth, depthHeight);
        depth.setFps(frameRate);
        depth.start();

        ofLogNotice() << "DEPTH sensor initiated";

    } else {
        ofLogNotice() << "cannot init DEPTH information";

    }

    if(!this->useColor)
    {
        if (ir.setup(device)) // only for xtion device (OpenNI2-FreenectDriver issue)
        {
            ir.setSize(depthWidth, depthHeight);
            ir.setFps(frameRate);
            ir.start();
            ofLogNotice() << "IR sensor initiated";
        } else {
            ofLogNotice() << "cannot init IR information";

        }
    }else{
        if(color.setup(device)) {
            color.setSize(depthWidth, depthHeight);
            color.setFps(frameRate);
            color.start();

            ofLogNotice() << "COLOR sensor initiated";
        } else {
            ofLogNotice() << "cannot init COLOR information";

        }
    }
}

void AsusXtionProV1::close()
{
    depth.exit();
    if(!this->useColor)
        ir.exit();
    else
        color.exit();
    device.exit();

    ofLogNotice()<< "SENSOR De-actived";
}

void AsusXtionProV1::update() {
    device.update();

    bNewFrame = depth.isFrameNew();

    depth.updateTextureIfNeeded();

    if(!this->useColor) {
        ir.updateTextureIfNeeded();
        colorImage.setFromPixels(ir.getPixelsRef());
    } else {
        color.updateTextureIfNeeded();
        colorImage.setFromPixels(color.getPixelsRef());
    }

    //const unsigned short* px = depth.getPixelsRef().getData();
    //depthPixels.setFromPixels(px, depth.getWidth(), depth.getHeight(),OF_IMAGE_GRAYSCALE);
    depthPixels = depth.getPixelsRef();
}


ofVec3f AsusXtionProV1::getWorldCoordinateAt(int x, int y) {
    return depth.getWorldCoordinateAt(x, y);
}

#endif
