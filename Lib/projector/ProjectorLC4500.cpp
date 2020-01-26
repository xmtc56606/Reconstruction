#include "ProjectorLC4500.h"

#include <iostream>

#include "LC4500API/API.h"
#include "LC4500API/usb.h"

void showError(std::string err){
    std::cerr << "lc4500startup: " << err.c_str() << std::endl;
}


ProjectorLC4500::ProjectorLC4500(unsigned int): nPatterns(0) , isRunning(false){

    std::cout << "ProjectorLC4500: preparing LightCrafter 4500 for duty... " << std::endl;

    // Initialize usb connection
    if(USB_Init()){
        showError("Could not init USB!");
    }
    if(USB_Open()){
        showError("Could not connect!");
    }
    if(!USB_IsConnected()){
        showError("Could not connect.");
    }

    // Make sure LC is not in standby
    const bool standby = false;
    if(!LCR_SetPowerMode(standby)){
        showError("Error Setting Power Mode");
    }

    LCR_SetMode(false);
    LCR_SetInputSource(2 , 0);
    LCR_SetPixelFormat(0);
}

void ProjectorLC4500::setPattern(unsigned int patternNumber , const unsigned char *tex , unsigned int texWidth  ,unsigned int texHeight){

}

void ProjectorLC4500::displayPattern(unsigned int PatNum){
    LCR_LoadSplash(PatNum);
    rectangle croppedArea , displayArea;
    croppedArea.firstPixel = 0;
    croppedArea.firstLine = 0;
    croppedArea.pixelsPerLine = 912;
    croppedArea.linesPerFrame = 1140;
    displayArea.firstPixel = 0;
    displayArea.firstLine = 0;
    displayArea.pixelsPerLine = 1280;
    displayArea.linesPerFrame = 800;
    LCR_SetDisplay(croppedArea , displayArea);
}

void ProjectorLC4500::displayTexture(const unsigned char *tex , unsigned int texWidth , unsigned int texHeight){

}

void ProjectorLC4500::displayBlack(){

}

void ProjectorLC4500::displayWhite(){

}

void ProjectorLC4500::getScreenRes(unsigned int *nx , unsigned int *ny){
    *nx = 912;
    *ny = 1140;
}

ProjectorLC4500::~ProjectorLC4500(){

    // Stop pattern sequence
    LCR_PatternDisplay(0);

    USB_Close();
    USB_Exit();

}

