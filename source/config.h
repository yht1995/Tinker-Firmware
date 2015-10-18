#ifndef __CONFIG_H_
#define __CONFIG_H_

static const int PORT = 7;
static const char* IP = "192.168.2.10";
static const char* NETMASK = "255.255.255.0";
static const char* GATEWAY = "192.168.2.1";

const int JOINTNUM = 6;

const int Polar[4] = { -1, -1, 1, 1 };


#define PIN_Encoder1 A0
#define PIN_Encoder2 A1
#define PIN_Encoder3 A2
#define PIN_Encoder4 A3

#define PIN_FOCMOTOR_TX D1
#define PIN_FOCMOTOR_RX D0

#define PIN_DYNAMIXEL_TX PTC14
#define PIN_DYNAMIXEL_RX PTC15
#endif
