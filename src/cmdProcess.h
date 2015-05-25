#ifndef __CMDPROCESS_H_
#define __CMDPROCESS_H_

#include "mbed.h"
#include "Motor.h"
#include "EthernetInterface.h"
#include "cmdline.h"
#include "config.h"
#include "main.h"

void Mecanum(int Vx,int Vy,int Omega);
int ProcessEnable(int argc, char *argv[]);
int ProcessShutdown(int argc, char *argv[]);
int ProcessSetRobotSpeed(int argc, char *argv[]);
int ProcessSetMotorSpeed(int argc, char *argv[]);
int ProcessGetEncoderChange(int argc, char *argv[]);
int ProcessSetMaxAccel(int argc,char* argv[]);
int ProcessHelp(int argc, char *argv[]);
int ProcessRobotArmSet(int argc,char* argv[]);

#endif
