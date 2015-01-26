//****************************************
//FuRoC Tinker2014 
//****************************************

#ifndef __MOTOR_H_
#define __MOTOR_H_

#include "mbed.h"

class Motor
{
private:
    PwmOut pwm;
    DigitalOut dir;
    InterruptIn encoder;
    int encoderCount;
    float targetPwm;
    void EncoderISR();
public:
    Motor(PinName pwm,PinName dir,PinName encoder);
    void SetSpeed(float speed);
    int GetEncoderChange();
};

#endif
