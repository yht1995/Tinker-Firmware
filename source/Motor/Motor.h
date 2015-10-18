//****************************************
//FuRoC Tinker2014
//****************************************

#ifndef __MOTOR_H_
#define __MOTOR_H_

#include "mbed.h"
#include "FOC/FuRoC_FOC_F28027.h"

class Motor
{
private:
	FocMotor focMotor;
	InterruptIn encoder;
	bool dir;
	int encoderCount;
	float targetPwm;
	void EncoderISR();
public:
	Motor(PinName tx, PinName rx, int MotorID, PinName encoder);
	void SetSpeed(float speed);
	void SetMaxAccel(float accel);
	int GetEncoderChange();
	void EnableDriver(bool isEnable);
};
#endif
