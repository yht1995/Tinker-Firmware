#ifndef __CONFIG_H_
#define __CONFIG_H_

#include "mbed-drivers/mbed.h"

static const PinName PIN_MOTOR_TX = PTC17;
static const PinName PIN_MOTOR_RX = PTC16;
static const PinName PIN_RS485_DIR = PTB18;

static const PinName PIN_PWM_BASE = PTD1;
static const PinName PIN_PWM_SHOULDER = PTD3;
static const PinName PIN_PWM_ELBOW = PTD2;
static const PinName PIN_PWM_WRIST1 = PTD0;
static const PinName PIN_PWM_WRIST2 = PTC4;
static const PinName PIN_PWM_WRIST3 = PTC3;

#endif
