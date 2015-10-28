#ifndef __NAL_H__
#define __NAL_H__

#include <mbed.h>
#include "../DMS-055A/frame_type.h"
#include "../DMS-055A/DMS-055A.h"

typedef void (*RegisterOnAckHandler)(ReadFrameACK *readFrameACK);

class MotorNal{
public:
    MotorNal(PinName tx,PinName rx,PinName dir);
    void RegisterOnAckHandler(RegisterOnAckHandler);
    void Send(SRFrame frame);
    void Send(MRFrame frame);
private:
    Serial _serial;
    DigitalOut _dir;
};

#endif
