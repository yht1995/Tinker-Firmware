#ifndef __MAIN_H_
#define __MAIN_H_

#include "mbed.h"
#include "EthernetInterface.h"
#include "Motor.h"
#include "PinConfig.h"
#include "cmdline.h"
#include "config.h"
#include "RobotArm.h"
#include <string>

extern Motor *motorTable[];
extern RobotArm robotArm;
extern DigitalOut SysEnable;
extern UDPSocket server;
extern Endpoint client;

#endif
