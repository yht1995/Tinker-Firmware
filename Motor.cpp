#include "Motor.h"
#include <math.h>

Motor::Motor(PinName pwm,PinName dir,PinName encoder)
            :pwm(pwm),dir(dir),encoder(encoder)
{
    encoderCount = 0;
		
		this->dir = 1;
		this->pwm.period_us(500);
		this->pwm = 1.0f;
    this->encoder.rise(this, &Motor::EncoderISR);
    this->encoder.fall(this, &Motor::EncoderISR);
}

void Motor::EncoderISR()
{
    if(dir)
    {
        this->encoderCount++;    
    }
    else
    {
        this->encoderCount--;    
    }
}

void Motor::SetSpeed(float speed)
{
    if(speed > 0.0f)
    {
        this->dir = 1;
    }
    else
    {
        this->dir = 0;
    }
    pwm = 1 - abs(speed)/1000.0f;
}

int Motor::GetEncoderChange()
{
    int temp = this->encoderCount;
    this->encoderCount = 0;
    return temp;
}
