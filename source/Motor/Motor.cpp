#include "Motor.h"
#include <math.h>

Motor::Motor(PinName tx, PinName rx, int MotorID, PinName encoder)
	: focMotor(tx, rx, MotorID), encoder(encoder)
{
	encoderCount = 0;
	this->dir = true;
	this->encoder.rise(this, &Motor::EncoderISR);
	this->encoder.fall(this, &Motor::EncoderISR);
}

void Motor::EncoderISR()
{
	if (dir) {
		this->encoderCount++;
	}else {
		this->encoderCount--;
	}
}

void Motor::EnableDriver(bool isEnable)
{
	this->focMotor.SetFlagenableSys(isEnable);
}

void Motor::SetSpeed(float speed)
{
	if (speed > 0.0f) {
		this->dir = 1;
	}else {
		this->dir = 0;
	}
	this->focMotor.SetSpeedRefrpm(speed);
}

int Motor::GetEncoderChange()
{
	int temp = this->encoderCount;
	this->encoderCount = 0;
	return temp;
}

void Motor::SetMaxAccel(float accel)
{
	this->focMotor.SetMaxAccelrpmps(accel);
}
