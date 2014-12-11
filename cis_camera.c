//
//  cis_camera.c
//  camera
//
//  Created by simon on 12/6/14.
//  Copyright (c) 2014 simon. All rights reserved.
//

#include "cis_camera.h"

int setFormat(struct camera_settings settings, int newValue){
    return 0;
}

int setAEMode(struct camera_settings, int newValue);
int setWhiteBalanceMode(struct camera_settings, int newValue);
int setAELevel(struct camera_settings, int newValue);
int setAEspeed(struct camera_settings, int newValue);
int setWhiteBalanceMode(struct camera_settings, int newValue);
int setAutoGainOn(struct camera_settings);
int setAutoGainOff(struct camera_settings);
int setMaxAutoGain(struct camera_settings, int newValue);
int setAutoIrisOn(struct camera_settings);
int setAutoIrisOff(struct camera_settings);
int setAutoShutterOn(struct camera_settings);
int setAutoShutterOff(struct camera_settings);
int setMinAutoShutter(struct camera_settings, int newValue);
int setManualGain(struct camera_settings, int newValue);
int setManualShutter(struct camera_settings, int newValue);
int setRGain(struct camera_settings, int newValue);
int setBGain(struct camera_settings, int newValue);
int setNoiseReduction(struct camera_settings, int newValue);
int setEdgeEnhancement(struct camera_settings, int newValue);
int setSaturation(struct camera_settings, int newValue);
int setRBColourBalance(struct camera_settings, int newValue);
int setGMColourBalance(struct camera_settings, int newValue);
int setPedestalOn(struct camera_settings);
int setPedestalOff(struct camera_settings);
int setPedestal(struct camera_settings, int newValue);
int setAutoGammaCompensation(struct camera_settings, int newValue);
int setGammaTable(struct camera_settings, int newValue);

int getAllCameraSettings(struct camera_settings);
int getFormat(struct camera_settings);
int getAEMode(struct camera_settings);
int getWhiteBalanceMode(struct camera_settings);
int getAELevel(struct camera_settings);
int getAEspeed(struct camera_settings);
int getWhiteBalanceMode(struct camera_settings);
int getAutoGainOn(struct camera_settings);
int getAutoGainOff(struct camera_settings);
int getMaxAutoGain(struct camera_settings);
int getAutoIrisOn(struct camera_settings);
int getAutoIrisOff(struct camera_settings);
int getAutoShutterOn(struct camera_settings);
int getAutoShutterOff(struct camera_settings);
int getMinAutoShutter(struct camera_settings);
int getManualGain(struct camera_settings);
int getManualShutter(struct camera_settings);
int getRGain(struct camera_settings);
int getBGain(struct camera_settings);
int getNoiseReduction(struct camera_settings);
int getEdgeEnhancement(struct camera_settings);
int getSaturation(struct camera_settings);
int getRBColourBalance(struct camera_settings);
int getGMColourBalance(struct camera_settings);
int getPedestalOn(struct camera_settings);
int getPedestalOff(struct camera_settings);
int getPedestal(struct camera_settings);
int getAutoGammaCompensation(struct camera_settings);
int getGammaTable(struct camera_settings);
