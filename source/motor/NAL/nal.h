#ifndef __NAL_H__
#define __NAL_H__

#include <mbed.h>
#include "../DMS-055A/frame_type.h"
#include "RingBuffer/RingBuffer.h"


class MotorNal{
public:
    MotorNal(PinName tx,PinName rx,PinName dir);
    void Send(SRFrame frame);
    void Send(DRFrame frame);
private:
    Serial _serial;
    DigitalOut _dir;
    RingBuffer tx_buffer;
    Timeout _tx_timer;

    int remain_to_send;
    int remain_to_recieve;

    void ScheduledSend();
    void _RxIrq();
    void _TxIrq();
    void _TxFinishHandler();

    static const int DIR_WRITE = 1;
    static const int DIR_READ  = 0;
};

#endif
