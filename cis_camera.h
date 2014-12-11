//
//  cis_camera.h
//  camera
//
//  Created by simon on 12/6/14.
//  Copyright (c) 2014 simon. All rights reserved.
//

#ifndef camera_cis_camera_h
#define camera_cis_camera_h

//Defines features accessible on CIS VCC-HD1 Camera
//Also defines get and set serial commands.
/*
        Parameter       Setting
        Baud rate       9600
        Bit length      8bit
        Stop bit        1bit
        Parity bit      N/A
        Flow control    N/A

*/
struct camera_settings
{
    int port_fd;
    int format;
    /*
    0: 1920×1080p @60fps(LevelA)
    1: 1920×1080p @60fps(LevelB)
    2: 1920×1080p @59.94fps(LevelA)
    3: 1920×1080p @59.94fps(LevelB)
    4: 1920×1080p @50fps(LevelA)
    5: 1920×1080p @50fps(LevelB)
    6: 1920×1080i @60fps
    7: 1920×1080i @59.94fps
    8: 1920×1080i @50fps
    9: 1280×720p @60fps
    10: 1280×720p @59.94fps
    11: 1280×720p @50fps
    */
    
    int auto_gain_on;       //0 manual, 1 auto
    int auto_iris_on;       //0 open??, 1 auto
    int auto_shutter_on;    //0 manual, 1 auto
    int manual_gain;        //0 - 30 in db
    int manual_shutter;

    /*
     0:Open
     1: 1/60
     2: 1/100
     3: 1/120
     4: 1/250
     5: 1/500
     6: 1/1000
     7: 1/2000
     8: 1/4000
     9: 1/8000
     */
    
    int max_auto_gain;      //As gain
    int max_auto_shutter;   //As shutter
    int min_auto_shutter;   //As shutter
    int ae_mode;
    /*
    0: Averaged
    1: Center-weighted
    2: Spot
    3: Back Light
     */
     
    int ae_level;           //0 - 100%
    int ae_speed;           //0 - 100%
    int white_balance_mode;
    /*
     0: Auto
     1: Auto (Outoor)
     2: DayLight
     3: Cloudy
     4: Shade
     5: Tungsten
     6: Flw (Fluorescent White)
     7: Fln (Fluorescent Daytime white)
     8: Fld (Fluorescent Daylight color) 9: Auto (test)
     10: OnePush
     11: Manual
     12-16: Preset 1-5
     */
    int r_gain;             // 0 - 800
    int b_gain;             // 0 - 800
    int noise_reduction;    // 0: Off 1: On
    int edge_enhancement;   // 0 : off 1-5: Level 1 - 5
    int saturation;         // 0 - 200
    int rb_colour_balance;  // 0 - 200
    int gm_colour_balance;  // 0 - 200
    int pedestal_on;        // 0: Off 1: On
    int pedestal;           // 0 - 127
    int auto_gamma_comp;    // 0: Off 1: Level 1 2: Level 2
    int gamma_table;        // 0 - 4: Gamma table 1 - 5
    char * version;
};

int setFormat(struct camera_settings, int newValue);
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



#endif
