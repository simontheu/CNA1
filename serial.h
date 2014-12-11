//
//  serial.h
//  CNA1 Project
//
//  Created by simon on 12/11/14.
//  Copyright (c) 2014 simon. All rights reserved.
//

#ifndef CNA1_Project_serial_h
#define CNA1_Project_serial_h


int set_interface_attribs (int fd, int speed, int parity);
void set_blocking (int fd, int should_block);
int set_up_port(char * portname);

#endif
