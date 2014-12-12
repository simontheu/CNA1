#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>

#include "serial.h"
#include "cis_camera.h"

#define RGB_GAIN_REL_REDUCTION_FACTOR 64
#define RGB_GAIN_MIN 0
#define RGB_GAIN_MAX 400

#define PEDESTAL_REL_REDUCTION_FACTOR 32
#define PEDESTAL_MIN 0
#define PEDESTAL_MAX 127

void error (char *msg)
{
    perror(msg);
    exit(0);
}

void sendSerialCommand(int current_cam,char *serialCommand, int fd)
{
    printf(" - COMMAND=%s",serialCommand);
    int commandLength=strlen(serialCommand);
    write (fd, serialCommand, commandLength);           // send 7 character greeting
    usleep ((5 + 25) * 100);             // sleep enough to transmit the 7 plus
    // receive 25:  approx 100 uS per char transmit
    char buf [20];
    int n = read (fd, buf, sizeof buf);  // read up to 100 characters if ready to read
    if (n!=0){
        printf("RECEIVED:%s",buf);
    }else
    {
        printf("No response");
    }
}

int proc16_signed(char msb,char lsb)
{
    char array[2]={lsb,msb};//endian thing i reckon
    int16_t val= *(int16_t *)&array[0];
    return val;
}

char* getSerialStringFor(int command[],int words,struct camera_settings *current_cam_struct)
{
    
    char *return_string;
    int adjustAmount; //used for analog adjustments
    
    switch (command[0]) {
        case 0x20:
            printf("Get/Set:Relative:");
            switch (command[1]) {
                case 0x00:
                    printf("shutter_speed");
                    return_string="";
                    break;

                case 0x01:
                    printf("master_gain");
                    return_string="";
                    break;

                case 0x03:
                    printf("nd_filter");
                    return_string="";
                    break;

                case 0x04:
                    printf("cc_filter");
                    return_string="";
                    break;

                case 0x06:
                    printf("master_gamma_select");
                    return_string="";
                    break;

                case 0x0a:
                    printf("auto_iris_window_select");
                    return_string="";
                    break;

                case 0x0d:
                    printf("preset_mtx_select");
                    return_string="";
                    break;

                case 0x13:
                    printf("standard_gamma_mode");
                    return_string="";
                    break;

                case 0x14:
                    printf("standard_gamma_select");
                    return_string="";
                    break;

                case 0x15:
                    printf("special_gamma_select");
                    return_string="";
                    break;

                case 0x16:
                    printf("hyper_gamma_select");
                    return_string="";
                    break;

                case 0x17:
                    printf("user_gamma_select");
                    return_string="";
                    break;

                case 0x18:
                    printf("blk_gamma_RGB_low_range");
                    return_string="";
                    break;

                case 0x1d:
                    printf("low_key_sat_low_range");
                    return_string="";
                    break;

                case 0x20:
                    printf("sls_select");//????
                    break;
                case 0x27:
                    printf("digital_extender");
                    return_string="";
                    break;

                case 0x28:
                    printf("flicker_reduce_area");
                    return_string="";
                    break;

                case 0x29:
                    printf("compensation");
                    return_string="";
                    break;

                case 0x2a:
                    printf("ns_level_mode");
                    return_string="";
                    break;

                case 0x2d:
                    printf("flicker_reduce_ave_mode");
                    return_string="";
                    break;

                case 0x2e:
                    printf("3D_camera_select");
                    return_string="";
                    break;

                case 0x81:
                    printf("chu_function_01");
                    return_string="";
                    break;

                case 0x82:
                    printf("chu_function_02");
                    return_string="";
                    break;

                case 0x83:
                    printf("chu_function_03");
                    return_string="";
                    break;

                case 0x84:
                    printf("chu_function_04");
                    return_string="";
                    break;

                case 0x85:
                    printf("chu_system_mode");
                    return_string="";
                    break;

                case 0x86:
                    printf("test_signal_select");
                    return_string="";
                    break;

                case 0x87:
                    printf("chu_function_05");
                    return_string="";
                    break;

                case 0x89:
                    printf("chu_function_06");
                    return_string="";
                    break;

                case 0x8b:
                    printf("chu_function_07");
                    return_string="";
                    break;

                case 0x8d:
                    printf("skin_detail_select_ch");
                    return_string="";
                    break;

                case 0x8e:
                    printf("skin_detail_gate_ch");
                    return_string="";
                    break;

                case 0x94:
                    printf("chu_function_08");
                    return_string="";
                    break;

                case 0x99:
                    printf("flicker_reduction_power_frequency");
                    return_string="";
                    break;

                case 0xa0:
                    printf("chu_mode_sw00");
                    return_string="";
                    break;

                case 0xa2:
                    printf("chu_mode_sw02");
                    return_string="";
                    break;

                case 0xa3:
                    printf("chu_mode_sw03");
                    return_string="";
                    break;

                case 0xa4:
                    printf("chu_mode_sw04");
                    return_string="";
                    break;

                case 0xc2:
                    printf("sd_detail");
                    return_string="";
                    break;

                default:
                    printf("COMMAND NOT FOUND");
                    return_string="";
                    break;
            }
            break;

        case 0x21:
            printf("Get/Set:Absolute:");
            switch (command[1]) {
                case 0x00:
                    printf("shutter_speed");
                    return_string="";
                    break;

                case 0x01:
                    printf("master_gain");
                    return_string="";
                    break;

                case 0x03:
                    printf("nd_filter");
                    return_string="";
                    break;

                case 0x04:
                    printf("cc_filter");
                    return_string="";
                    break;

                case 0x06:
                    printf("master_gamma_select");
                    return_string="";
                    break;

                case 0x0a:
                    printf("auto_iris_window_select");
                    return_string="";
                    break;

                case 0x0d:
                    printf("preset_mtx_select");
                    return_string="";
                    break;

                case 0x13:
                    printf("standard_gamma_mode");
                    return_string="";
                    break;

                case 0x14:
                    printf("standard_gamma_select");
                    return_string="";
                    break;

                case 0x15:
                    printf("special_gamma_select");
                    return_string="";
                    break;

                case 0x16:
                    printf("hyper_gamma_select");
                    return_string="";
                    break;

                case 0x17:
                    printf("user_gamma_select");
                    return_string="";
                    break;

                case 0x18:
                    printf("blk_gamma_RGB_low_range");
                    return_string="";
                    break;

                case 0x1d:
                    printf("low_key_sat_low_range");
                    return_string="";
                    break;

                case 0x20:
                    printf("sls_select");//????
                    break;
                case 0x27:
                    printf("digital_extender");
                    return_string="";
                    break;

                case 0x28:
                    printf("flicker_reduce_area");
                    return_string="";
                    break;

                case 0x29:
                    printf("compensation");
                    return_string="";
                    break;

                case 0x2a:
                    printf("ns_level_mode");
                    return_string="";
                    break;

                case 0x2d:
                    printf("flicker_reduce_ave_mode");
                    return_string="";
                    break;

                case 0x2e:
                    printf("3D_camera_select");
                    return_string="";
                    break;

                case 0x81:
                    printf("chu_function_01");
                    return_string="";
                    break;

                case 0x82:
                    printf("chu_function_02");
                    return_string="";
                    break;

                case 0x83:
                    printf("chu_function_03");
                    return_string="";
                    break;

                case 0x84:
                    printf("chu_function_04");
                    return_string="";
                    break;

                case 0x85:
                    printf("chu_system_mode");
                    return_string="";
                    break;

                case 0x86:
                    printf("test_signal_select");
                    return_string="";
                    break;

                case 0x87:
                    printf("chu_function_05");
                    return_string="";
                    break;

                case 0x89:
                    printf("chu_function_06");
                    return_string="";
                    break;

                case 0x8b:
                    printf("chu_function_07");
                    return_string="";
                    break;

                case 0x8d:
                    printf("skin_detail_select_ch");
                    return_string="";
                    break;

                case 0x8e:
                    printf("skin_detail_gate_ch");
                    return_string="";
                    break;

                case 0x94:
                    printf("chu_function_08");
                    return_string="";
                    break;

                case 0x99:
                    printf("flicker_reduction_power_frequency");
                    return_string="";
                    break;

                case 0xa0:
                    printf("chu_mode_sw00");
                    return_string="";
                    break;

                case 0xa2:
                    printf("chu_mode_sw02");
                    return_string="";
                    break;

                case 0xa3:
                    printf("chu_mode_sw03");
                    return_string="";
                    break;

                case 0xa4:
                    printf("chu_mode_sw04");
                    return_string="";
                    break;

                case 0xc2:
                    printf("sd_detail");
                    return_string="";
                    break;

                default:
                    printf("COMMAND NOT FOUND");
                    return_string="";
                    break;
            }
            break;
            
        case 0x22:
            printf("Get/Set:Relative:");//has contents
            switch (command[1]) {
                case 0x01: ; // "white_R"
                    //detect direction and amount
                    adjustAmount= proc16_signed(command[2],command[3])/RGB_GAIN_REL_REDUCTION_FACTOR;
                    printf("adjusted adjust!:%d",adjustAmount);
                    if (((current_cam_struct->r_gain + adjustAmount)> RGB_GAIN_MIN) && ((current_cam_struct->r_gain + adjustAmount) < RGB_GAIN_MAX)){
                        
                        current_cam_struct->r_gain=current_cam_struct->r_gain+adjustAmount;
                        printf("white_R:%d",adjustAmount);
                        printf("struct.r_gain:%d",current_cam_struct->r_gain);
                        
                        int n=sprintf (return_string, "SRG %d\n", current_cam_struct->r_gain);
                        printf("Return string:%s",return_string);
                    }else{
                        printf("white_R:Limit Reached",adjustAmount);
                        printf("struct.r_gain:%d",current_cam_struct->r_gain);
                        return_string="";
                    }
                    break;
                case 0x02:
                    printf("white_G");
                    return_string="";
                    break;
                case 0x03: // "white_B"
                    //detect direction and amount
                    adjustAmount= proc16_signed(command[2],command[3])/RGB_GAIN_REL_REDUCTION_FACTOR;
                    printf("adjusted adjust!:%d",adjustAmount);
                    if (((current_cam_struct->b_gain + adjustAmount)> RGB_GAIN_MIN) && ((current_cam_struct->b_gain + adjustAmount) < RGB_GAIN_MAX)){
                    
                        current_cam_struct->b_gain=current_cam_struct->b_gain+adjustAmount;
                        printf("white_B:%d",adjustAmount);
                        printf("struct.b_gain:%d",current_cam_struct->b_gain);
                        int n=sprintf (return_string, "SBG %d\n", current_cam_struct->b_gain);
                        printf("Return string:%s",return_string);
                    }else{
                        printf("white_B:Limit Reached",adjustAmount);
                        printf("struct.b_gain:%d",current_cam_struct->b_gain);
                        return_string="";
                    }
                    break;
                case 0x04:
                    printf("master_mod_shd_v_saw");
                    return_string="";
                    break;

                case 0x05:
                    printf("mod_shd_v_saw_R");
                    return_string="";
                    break;

                case 0x06:
                    printf("mod_shd_v_saw_G");
                    return_string="";
                    break;

                case 0x07:
                    printf("mod_shd_v_saw_B");
                    return_string="";
                    break;

                case 0x08:
                    printf("master_flare");
                    return_string="";
                    break;

                case 0x09:
                    printf("flare_R");
                    return_string="";
                    break;

                case 0x0a:
                    printf("flare_G");
                    return_string="";
                    break;

                case 0x0b:
                    printf("flare_B");
                    return_string="";
                    break;

                case 0x0c:
                    printf("detail_limiter");
                    return_string="";
                    break;

                case 0x0d:
                    printf("detail_white_limit");
                    return_string="";
                    break;

                case 0x0e:
                    printf("detail_black_limit");
                    return_string="";
                    break;

                case 0x10:
                    printf("master_black_gamma");
                    return_string="";
                    break;

                case 0x11:
                    printf("black_gamma_R");
                    return_string="";
                    break;

                case 0x12:
                    printf("black_gamma_G");
                    return_string="";
                    break;

                case 0x13:
                    printf("black_gamma_B");
                    return_string="";
                    break;

                case 0x14:
                    printf("master_knee_point");
                    return_string="";
                    break;

                case 0x15:
                    printf("knee_point_R");
                    return_string="";
                    break;

                case 0x16:
                    printf("knee_point_G");
                    return_string="";
                    break;

                case 0x17:
                    printf("knee_point_B");
                    return_string="";
                    break;

                case 0x18:
                    printf("master_knee_slope");
                    return_string="";
                    break;

                case 0x19:
                    printf("knee_slope_R");
                    return_string="";
                    break;

                case 0x1a:
                    printf("knee_slope_G");
                    return_string="";
                    break;

                case 0x1b:
                    printf("knee_slope_B");
                    return_string="";
                    break;

                case 0x1c:
                    printf("master_gamma");
                    return_string="";
                    break;

                case 0x1d:
                    printf("gamma_R");
                    return_string="";
                    break;

                case 0x1e:
                    printf("gamma_G");
                    return_string="";
                    break;

                case 0x1f:
                    printf("gamma_B");
                    return_string="";
                    break;

                case 0x20:
                    printf("master_white_clip");
                    return_string="";
                    break;

                case 0x21:
                    printf("white_clip_R");
                    return_string="";
                    break;

                case 0x22:
                    printf("white_clip_G");
                    return_string="";
                    break;

                case 0x23:
                    printf("white_clip_B");
                    return_string="";
                    break;

                case 0x24:
                    printf("flicker_reduce_gain_m");
                    return_string="";
                    break;

                case 0x28:
                    printf("flicker_reduce_ofs_m");
                    return_string="";
                    break;

                case 0x41:
                    printf("ecs_frequency");
                    return_string="";
                    break;

                case 0x42:
                    printf("evs_data");
                    return_string="";
                    break;

                case 0x43:
                    printf("skin_detail_phase");
                    return_string="";
                    break;

                case 0x44:
                    printf("skin_detail_width");
                    return_string="";
                    break;

                case 0x47:
                    printf("chu_optical_level");
                    return_string="";
                    break;

                case 0x54:
                    printf("skin_detail2_phase");
                    return_string="";
                    break;

                case 0x55:
                    printf("skin_detail2_width");
                    return_string="";
                    break;

                case 0x56:
                    printf("skin_detail3_phase");
                    return_string="";
                    break;

                case 0x57:
                    printf("skin_detail3_width");
                    return_string="";
                    break;

                case 0x60:
                    printf("iris");
                    return_string="";
                    break;

                case 0x9b:
                    printf("detail_level");
                    return_string="";
                    break;

                case 0x9c:
                    printf("detail_crispening");
                    return_string="";
                    break;

                case 0x9d:
                    printf("detail_mix_ratio");
                    return_string="";
                    break;

                case 0x9e:
                    printf("detail_HV_ratio");
                    return_string="";
                    break;

                case 0x9f:
                    printf("H_detail_HL_ratio");
                    return_string="";
                    break;

                case 0xa0:
                    printf("detail_level_depend");
                    return_string="";
                    break;

                case 0xa1:
                    printf("skin_detial_level");
                    return_string="";
                    break;

                case 0xa2:
                    printf("skin_detail_sat");
                    return_string="";
                    break;

                case 0xa3:
                    printf("matrix_GR_R");
                    return_string="";
                    break;

                case 0xa4:
                    printf("matrix_BR_R");
                    return_string="";
                    break;

                case 0xa5:
                    printf("matrix_RG_G");
                    return_string="";
                    break;

                case 0xa6:
                    printf("matrix_BG_G");
                    return_string="";
                    break;

                case 0xa7:
                    printf("matrix_RB_B");
                    return_string="";
                    break;

                case 0xa8:
                    printf("matrix_GB_B");
                    return_string="";
                    break;

                case 0xa9:
                    printf("master_black");//COMMAND USED **** "master_black"
                    //detect direction and amount
                    adjustAmount= proc16_signed(command[2],command[3])/PEDESTAL_REL_REDUCTION_FACTOR;
                    current_cam_struct->pedestal=current_cam_struct->pedestal+adjustAmount;
                    printf("adjusted adjust!:%d",adjustAmount);
                    if (((current_cam_struct->pedestal + adjustAmount)> PEDESTAL_MIN) && ((current_cam_struct->pedestal + adjustAmount) < PEDESTAL_MAX)){
                    
                    current_cam_struct->r_gain=current_cam_struct->pedestal+adjustAmount;
                    printf("white_R:%d",adjustAmount);
                    printf("struct.pedestal:%d",current_cam_struct->pedestal);
                    
                    int n=sprintf (return_string, "SPL %d\n", current_cam_struct->pedestal);
                    printf("Return string:%s",return_string);
                }else{
                    printf("white_R:Limit Reached",adjustAmount);
                    printf("struct.pedestal:%d",current_cam_struct->pedestal);
                    return_string="";
                }
                    break;

                case 0xaa:
                    printf("black_R");
                    return_string="";
                    break;

                case 0xab:
                    printf("black_G");
                    return_string="";
                    break;

                case 0xac:
                    printf("black_B");
                    return_string="";
                    break;

                case 0xae:
                    printf("knee_slope_sat");
                    return_string="";
                    break;

                case 0xaf:
                    printf("knee_aperture");
                    return_string="";
                    break;

                case 0xb0:
                    printf("comb_filter");
                    return_string="";
                    break;

                case 0xb7:
                    printf("low_key_clip_level");
                    return_string="";
                    break;

                case 0xc4:
                    printf("adaptive_knee_point");
                    return_string="";
                    break;

                case 0xc5:
                    printf("adaptive_knee_slope");
                    return_string="";
                    break;

                case 0xc6:
                    printf("slim_detial");
                    return_string="";
                    break;

                case 0xc7:
                    printf("skin_detial2_level");
                    return_string="";
                    break;

                case 0xc8:
                    printf("skin_detial2_sat");
                    return_string="";
                    break;

                case 0xc9:
                    printf("skin_detial3_level");
                    return_string="";
                    break;

                case 0xca:
                    printf("skin_detial3_sat");
                    return_string="";
                    break;

                case 0xd2:
                    printf("chu_saturation");
                    return_string="";
                    break;

                case 0xdc:
                    printf("white_color_temp_control");
                    return_string="";
                    break;

                case 0xde:
                    printf("chu_color_temp_balance");
                    return_string="";
                    break;

                case 0xdf:
                    printf("select_fps");
                    return_string="";
                    break;

                case 0xe0:
                    printf("SD_detail_level");
                    return_string="";
                    break;

                case 0xe1:
                    printf("SD_detail_crispening");
                    return_string="";
                    break;

                case 0xe2:
                    printf("SD_detail_H/V_ration");
                    return_string="";
                    break;

                case 0xe3:
                    printf("SD_detail_limiter");
                    return_string="";
                    break;

                case 0xe4:
                    printf("SD_detail_white_limiter");
                    return_string="";
                    break;

                case 0xe5:
                    printf("SD_detail_black_limiter");
                    return_string="";
                    break;

                case 0xe6:
                    printf("SD_detail_frequency");
                    return_string="";
                    break;

                case 0xe7:
                    printf("SD_detail_level_depend");
                    return_string="";
                    break;

                case 0xeb:
                    printf("SD_detail_detail_comb");
                    return_string="";
                    break;

                case 0xf2:
                    printf("master_white_gain");            //************
                    break;
                default:
                    printf("COMMAND NOT FOUND");
                    return_string="";
                    break;
            }
            break;
        case 0x23:
            printf("Get/Set:Absolute:");
            switch (command[1]) {
                case 0x01:
                    printf("white_R");
                    return_string="";
                    break;

                case 0x02:
                    printf("white_G");
                    return_string="";
                    break;

                case 0x03:
                    printf("white_B");
                    return_string="";
                    break;

                case 0x04:
                    printf("master_mod_shd_v_saw");
                    return_string="";
                    break;

                case 0x05:
                    printf("mod_shd_v_saw_R");
                    return_string="";
                    break;

                case 0x06:
                    printf("mod_shd_v_saw_G");
                    return_string="";
                    break;

                case 0x07:
                    printf("mod_shd_v_saw_B");
                    return_string="";
                    break;

                case 0x08:
                    printf("master_flare");
                    return_string="";
                    break;

                case 0x09:
                    printf("flare_R");
                    return_string="";
                    break;

                case 0x0a:
                    printf("flare_G");
                    return_string="";
                    break;

                case 0x0b:
                    printf("flare_B");
                    return_string="";
                    break;

                case 0x0c:
                    printf("detail_limiter");
                    return_string="";
                    break;

                case 0x0d:
                    printf("detail_white_limit");
                    return_string="";
                    break;

                case 0x0e:
                    printf("detail_black_limit");
                    return_string="";
                    break;

                case 0x10:
                    printf("master_black_gamma");
                    return_string="";
                    break;

                case 0x11:
                    printf("black_gamma_R");
                    return_string="";
                    break;

                case 0x12:
                    printf("black_gamma_G");
                    return_string="";
                    break;

                case 0x13:
                    printf("black_gamma_B");
                    return_string="";
                    break;

                case 0x14:
                    printf("master_knee_point");
                    return_string="";
                    break;

                case 0x15:
                    printf("knee_point_R");
                    return_string="";
                    break;

                case 0x16:
                    printf("knee_point_G");
                    return_string="";
                    break;

                case 0x17:
                    printf("knee_point_B");
                    return_string="";
                    break;

                case 0x18:
                    printf("master_knee_slope");
                    return_string="";
                    break;

                case 0x19:
                    printf("knee_slope_R");
                    return_string="";
                    break;

                case 0x1a:
                    printf("knee_slope_G");
                    return_string="";
                    break;

                case 0x1b:
                    printf("knee_slope_B");
                    return_string="";
                    break;

                case 0x1c:
                    printf("master_gamma");
                    return_string="";
                    break;

                case 0x1d:
                    printf("gamma_R");
                    return_string="";
                    break;

                case 0x1e:
                    printf("gamma_G");
                    return_string="";
                    break;

                case 0x1f:
                    printf("gamma_B");
                    return_string="";
                    break;

                case 0x20:
                    printf("master_white_clip");
                    return_string="";
                    break;

                case 0x21:
                    printf("white_clip_R");
                    return_string="";
                    break;

                case 0x22:
                    printf("white_clip_G");
                    return_string="";
                    break;

                case 0x23:
                    printf("white_clip_B");
                    return_string="";
                    break;

                case 0x24:
                    printf("flicker_reduce_gain_m");
                    return_string="";
                    break;

                case 0x28:
                    printf("flicker_reduce_ofs_m");
                    return_string="";
                    break;

                case 0x41:
                    printf("ecs_frequency");
                    return_string="";
                    break;

                case 0x42:
                    printf("evs_data");
                    return_string="";
                    break;

                case 0x43:
                    printf("skin_detail_phase");
                    return_string="";
                    break;

                case 0x44:
                    printf("skin_detail_width");
                    return_string="";
                    break;

                case 0x47:
                    printf("chu_optical_level");
                    return_string="";
                    break;

                case 0x54:
                    printf("skin_detail2_phase");
                    return_string="";
                    break;

                case 0x55:
                    printf("skin_detail2_width");
                    return_string="";
                    break;

                case 0x56:
                    printf("skin_detail3_phase");
                    return_string="";
                    break;

                case 0x57:
                    printf("skin_detail3_width");
                    return_string="";
                    break;

                case 0x60:
                    printf("iris");
                    return_string="";
                    break;

                case 0x9b:
                    printf("detail_level");
                    return_string="";
                    break;

                case 0x9c:
                    printf("detail_crispening");
                    return_string="";
                    break;

                case 0x9d:
                    printf("detail_mix_ratio");
                    return_string="";
                    break;

                case 0x9e:
                    printf("detail_HV_ratio");
                    return_string="";
                    break;

                case 0x9f:
                    printf("H_detail_HL_ratio");
                    return_string="";
                    break;

                case 0xa0:
                    printf("detail_level_depend");
                    return_string="";
                    break;

                case 0xa1:
                    printf("skin_detial_level");
                    return_string="";
                    break;

                case 0xa2:
                    printf("skin_detail_sat");
                    return_string="";
                    break;

                case 0xa3:
                    printf("matrix_GR_R");
                    return_string="";
                    break;

                case 0xa4:
                    printf("matrix_BR_R");
                    return_string="";
                    break;

                case 0xa5:
                    printf("matrix_RG_G");
                    return_string="";
                    break;

                case 0xa6:
                    printf("matrix_BG_G");
                    return_string="";
                    break;

                case 0xa7:
                    printf("matrix_RB_B");
                    return_string="";
                    break;

                case 0xa8:
                    printf("matrix_GB_B");
                    return_string="";
                    break;

                case 0xa9:
                    printf("master_black");
                    return_string="";
                    break;

                case 0xaa:
                    printf("black_R");
                    return_string="";
                    break;

                case 0xab:
                    printf("black_G");
                    return_string="";
                    break;

                case 0xac:
                    printf("black_B");
                    return_string="";
                    break;

                case 0xae:
                    printf("knee_slope_sat");
                    return_string="";
                    break;

                case 0xaf:
                    printf("knee_aperture");
                    return_string="";
                    break;

                case 0xb0:
                    printf("comb_filter");
                    return_string="";
                    break;

                case 0xb7:
                    printf("low_key_clip_level");
                    return_string="";
                    break;

                case 0xc4:
                    printf("adaptive_knee_point");
                    return_string="";
                    break;

                case 0xc5:
                    printf("adaptive_knee_slope");
                    return_string="";
                    break;

                case 0xc6:
                    printf("slim_detial");
                    return_string="";
                    break;

                case 0xc7:
                    printf("skin_detial2_level");
                    return_string="";
                    break;

                case 0xc8:
                    printf("skin_detial2_sat");
                    return_string="";
                    break;

                case 0xc9:
                    printf("skin_detial3_level");
                    return_string="";
                    break;

                case 0xca:
                    printf("skin_detial3_sat");
                    return_string="";
                    break;

                case 0xd2:
                    printf("chu_saturation");
                    return_string="";
                    break;

                case 0xdc:
                    printf("white_color_temp_control");
                    return_string="";
                    break;

                case 0xde:
                    printf("chu_color_temp_balance");
                    return_string="";
                    break;

                case 0xdf:
                    printf("select_fps");
                    return_string="";
                    break;

                case 0xe0:
                    printf("SD_detail_level");
                    return_string="";
                    break;

                case 0xe1:
                    printf("SD_detail_crispening");
                    return_string="";
                    break;

                case 0xe2:
                    printf("SD_detail_H/V_ration");
                    return_string="";
                    break;

                case 0xe3:
                    printf("SD_detail_limiter");
                    return_string="";
                    break;

                case 0xe4:
                    printf("SD_detail_white_limiter");
                    return_string="";
                    break;

                case 0xe5:
                    printf("SD_detail_black_limiter");
                    return_string="";
                    break;

                case 0xe6:
                    printf("SD_detail_frequency");
                    return_string="";
                    break;

                case 0xe7:
                    printf("SD_detail_level_depend");
                    return_string="";
                    break;

                case 0xeb:
                    printf("SD_detail_detail_comb");
                    return_string="";
                    break;

                case 0xf2:
                    printf("master_white_gain");            //************
                    break;
                default:
                    printf("COMMAND NOT FOUND");
                    return_string="";
                    break;
            }
            break;
            
        case 0x25:
            printf("CHU AutoSetup Control:");
            switch (command[1]) {
                    case 0x00:
                        printf("Status Query");
                        break;
                    case 0x01:
                        printf("Auto White Balance");
                        break;
                    case 0x02:
                        printf("Auto Black Balance");
                        break;
                    case 0x03:
                        printf("Auto Level");
                        break;
                    case 0x07:
                        printf("Skin Detail Auto Hue (CH1)");
                        break;
                    case 0x0a:
                        printf("Skin Detail Auto Hue (CH2)");
                        break;
                    case 0x0b:
                        printf("Skin Detail Auto Hue (CH3)");
                        break;
                    default:
                        printf("Other\n");
                        return_string="";
                        break;
                }
            break;

        case 0x27:
            printf("CHU Scene FileControl:");
            switch (command[1]) {
                case 0x00:
                    printf("Cancelling");
                    return_string="";
                    break;

                case 0x01:
                    printf("Initializtion (Formatting)");
                    return_string="";
                    break;

                case 0x02:
                    printf("Calling");
                    return_string="";
                    break;

                case 0x03:
                    printf("Saving");
                    return_string="";
                    break;

                case 0x04:
                    printf("Erasing");
                    return_string="";
                    break;

                case 0x05:
                    printf("Cancelling the call");
                    return_string="";
                    break;

                case 0x06:
                    printf("Status request");
                    return_string="";
                    break;

                case 0x07:
                    printf("File Call in progress");
                    return_string="";
                    break;

                case 0x08:
                    printf("There file contains data that is not called");
                    return_string="";
                    break;

                case 0x09:
                    printf("There is a file but no data");
                    return_string="";
                    break;

                case 0x0a:
                    printf("The corresponding file does not exist");
                    return_string="";
                    break;

                case 0x0b:
                    printf("Transmission of number of files");
                    return_string="";
                    break;

                case 0x0c:
                    printf("Not possible");
                    return_string="";
                    break;

                default:
                    printf("Other\n");
                    return_string="";
                    break;
            }
            break;
            
        case 0x29:
            printf("Utility:Bit data:");
            switch (command[1]) {
                case 0:
                    break;
                default:
                    printf("Other\n");
                    return_string="";
                    break;
                
            }
            break;
            
        case 0x40:
            printf("CCU Function Control:Relative:");
            switch (command[1]) {
                case 0x10:
                    printf("ccu_skin_gate");
                    return_string="";
                    break;

                case 0x12:
                    printf("mono");
                    return_string="";
                    break;

                case 0x31:
                    printf("preview");
                    return_string="";
                    break;

                case 0x40:
                    printf("sd_function_01");
                    return_string="";
                    break;

                case 0xc2:
                    printf("sd_function_02");
                    return_string="";
                    break;

                case 0xc3:
                    printf("sd_function_03");
                    return_string="";
                    break;

                case 0xe0:
                    printf("sd_crop_control");
                    return_string="";
                    break;

                default:
                    printf("Other\n");
                    return_string="";
                    break;
            }
            break;
            
        case 0x41:
            printf("CCU Function Control:Absolute:");
            switch (command[1]) {
                case 0x10:
                    printf("ccu_skin_gate");
                    return_string="";
                    break;

                case 0x12:
                    printf("mono");
                    return_string="";
                    break;

                case 0x31:
                    printf("preview");
                    return_string="";
                    break;

                case 0x40:
                    printf("sd_function_01");
                    return_string="";
                    break;

                case 0xc2:
                    printf("sd_function_02");
                    return_string="";
                    break;

                case 0xc3:
                    printf("sd_function_03");
                    return_string="";
                    break;

                case 0xe0:
                    printf("sd_crop_control");
                    return_string="";
                    break;

                default:
                    printf("Other\n");
                    return_string="";
                    break;
            }
            break;
            
        case 0x42:
            printf("CCU Function Control:Relative:");
            switch (command[1]) {
                case 0x07:
                    printf("mono_saturation");
                    return_string="";
                    break;

                case 0x08:
                    printf("mono_hue");
                    return_string="";
                    break;

                case 0x70:
                    printf("crop_position");
                    return_string="";
                    break;

                case 0x8c:
                    printf("SD_detail_limiter");
                    return_string="";
                    break;

                case 0x8d:
                    printf("SD_detail_white_limiter");
                    return_string="";
                    break;

                case 0x8e:
                    printf("SD_detail_black_limiter");
                    return_string="";
                    break;

                case 0x9c:
                    printf("SD_master_gamma");
                    return_string="";
                    break;

                case 0xa3:
                    printf("SD_matrix_GR_R");
                    return_string="";
                    break;

                case 0xa4:
                    printf("SD_matrix_BR_R");
                    return_string="";
                    break;

                case 0xa5:
                    printf("SD_matrix_RG_G");
                    return_string="";
                    break;

                case 0xa6:
                    printf("SD_matrix_BG_G");
                    return_string="";
                    break;
                case 0xa7:
                    printf("SD_matrix_RB_B");
                    return_string="";
                    break;
                case 0xa8:
                    printf("SD_matrix_GB_B");
                    return_string="";
                    break;
                case 0xb0:
                    printf("SD_detail_comb");
                    return_string="";
                    break;
                case 0xdb:
                    printf("SD_detail_level");
                    return_string="";
                    break;
                case 0xdc:
                    printf("SD_detail_crispening");
                    return_string="";
                    break;
                case 0xde:
                    printf("SD_detail_HV_ratio");
                    return_string="";
                    break;
                case 0xdf:
                    printf("SD_detail_frequency");
                    return_string="";
                    break;
                case 0xe0:
                    printf("SD_detail_level_depend");
                    return_string="";
                    break;
                case 0xf0:
                    printf("optical_level");
                    return_string="";
                    break;
                default:
                    printf("Other\n");
                    return_string="";
                    break;
            }
            break;
            
        case 0x43:
            printf("CCU Function Control:Absolute:");
            switch (command[1]) {
                case 0x07:
                    printf("mono_saturation");
                    return_string="";
                    break;
                case 0x08:
                    printf("mono_hue");
                    return_string="";
                    break;
                case 0x70:
                    printf("crop_position");
                    return_string="";
                    break;
                case 0x8c:
                    printf("SD_detail_limiter");
                    return_string="";
                    break;
                case 0x8d:
                    printf("SD_detail_white_limiter");
                    return_string="";
                    break;
                case 0x8e:
                    printf("SD_detail_black_limiter");
                    return_string="";
                    break;
                case 0x9c:
                    printf("SD_master_gamma");
                    return_string="";
                    break;
                case 0xa3:
                    printf("SD_matrix_GR_R");
                    return_string="";
                    break;
                case 0xa4:
                    printf("SD_matrix_BR_R");
                    return_string="";
                    break;
                case 0xa5:
                    printf("SD_matrix_RG_G");
                    return_string="";
                    break;
                case 0xa6:
                    printf("SD_matrix_BG_G");
                    return_string="";
                    break;
                case 0xa7:
                    printf("SD_matrix_RB_B");
                    return_string="";
                    break;
                case 0xa8:
                    printf("SD_matrix_GB_B");
                    return_string="";
                    break;
                case 0xb0:
                    printf("SD_detail_comb");
                    return_string="";
                    break;
                case 0xdb:
                    printf("SD_detail_level");
                    return_string="";
                    break;
                case 0xdc:
                    printf("SD_detail_crispening");
                    return_string="";
                    break;
                case 0xde:
                    printf("SD_detail_HV_ratio");
                    return_string="";
                    break;
                case 0xdf:
                    printf("SD_detail_frequency");
                    return_string="";
                    break;
                case 0xe0:
                    printf("SD_detail_level_depend");
                    return_string="";
                    break;
                case 0xf0:
                    printf("optical_level");
                    return_string="";
                    break;
                default:
                    printf("Other\n");
                    return_string="";
                    break;
            }
            break;
            
        case 0x49:
            printf("Utility:Bit data:");
            switch (command[1]){
                case 0x0:
                    printf("Other\n");
                    return_string="";
                    break;
                default:
                    printf("NO COMMAND FOUND");
                    return_string="";
                    break;
            }
            break;

        case 0x60:
            printf("System Control:Cam number:Relative:");
            return_string="";
            break;
            
        case 0x61:
            printf("System Control:Cam number:Absolute:");
            return_string="";
            break;
            
        default:
            printf("NO COMMAND FOUND");
            return_string="";
            break;
        }

            

    return return_string;
}


char* convertCommand(char* command,struct camera_settings *current_cam_struct_ptr){

    int i=0; //word index
    int words=0;
    int subcommand[20];
    char delimiter[2]=",";
    char *token; //next start position to parse

    token=strtok(command,delimiter);

    while (token!=NULL) {
         subcommand[words]=strtol(token,NULL,16);//convert from ascii hex to int
         words++;
         token = strtok(NULL,delimiter);
    }
    int word;
    for (word=0; word<words; word++) {
        printf ("%x,",subcommand[word]);
    }
    printf("\n");
    char *serialCommand=getSerialStringFor(subcommand,words,current_cam_struct_ptr);
    return serialCommand;
}



int main (int argc, char *argv[])
{

    printf("\nCIS CNA-1 TCP/IP >> 2 X Serial\n");

    //Variable declarations
    //fd= file descriptors
    int sockfd, portno, readStatus, writeStatus;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    
    int current_cam=1; //should be 0 or negative until response received
    
    struct camera_settings cam1;
    struct camera_settings cam2;
    
    
    
    struct camera_settings *current_cam_struct_ptr;
    
    //setup structs with default/obtained values
    cam1.r_gain= 200;
    cam1.b_gain= 200;
    cam1.pedestal=50;
    
    current_cam_struct_ptr=&cam1;
    
    
    
    //Network initialisation
    
    char buffer[256];
    if (argc<3) {
        fprintf(stderr, "usage %s hostname port\n", argv[0]);
        exit(0);
    }
    
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM,0);
    if (sockfd<0){
        error("ERROR opening socket");
    }
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    
    //setup serial port file descriptors and store in structs
    char *cam1_portname = "/dev/ttyO1";
    char *cam2_portname = "/dev/ttyO2";
    
    cam1.port_fd=set_up_port(cam1_portname);
    cam2.port_fd=set_up_port(cam2_portname);


    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr,server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0){
        error("ERROR connecting");
    }
    printf("Sending permission string");
    bzero(buffer,256);
    char permission[]="0b,90,01,00\n";
    int i;
    for (i=0;i<strlen(permission);i++){
        buffer[i]=permission[i];
    }
    //fgets(buffer,255,stdin);
    //writeStatus= write (sockfd,buffer,strlen(buffer));
    if (writeStatus<0){
      //  error("ERROR writing to socket");
    }
    bzero(buffer,256);
    char command[30];
    bzero(command,31);
    int bytePosition=0,byte;
    i=0;
while (1){ //MAIN PROGRAM LOOP
    //READ FROM NETWORK
    readStatus = read(sockfd,buffer,1);
    if (readStatus<0) {
        error("ERROR reading from socket");
    }
    
    //SOCKET INPUT PRIORITY 1 AND SEND SERIAL COMMAND
    if (i<30){
        command[i]=buffer[0];
        if (command[i]==10){ //decimal 10 is new line
            char *serialCommand=convertCommand(command,current_cam_struct_ptr);
            sendSerialCommand(current_cam,serialCommand,cam1.port_fd);
            bzero(buffer,256);
            bzero(command,31);
            i=0;
        }else{
            i++;
        }
    }else {
        printf("COMMAND OVERFLOW\n");
        bzero(buffer,256);
        bzero(command,31);
        i=0;
    }
    
    //
    
    
    
    readStatus=0;

}
    return 0;
}



