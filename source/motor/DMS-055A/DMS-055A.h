#ifndef __DMS_055A_H__
#define __DMS_055A_H__

#include "frame_type.h"
#include <stdint.h>
#include <stdbool.h>

class DMS055A {
public:
static void BoardCastEnableOutput(bool enable = true);
void EnableOutput(bool enable = true);
void SetTargetSpeed(int speed);
void SetTargetPosition(int step);
int GetAbsolutePosition();


private:
uint8_t _device_id;
uint16_t _target_speed;
uint32_t _target_position;
uint32_t _absolute_position;

void SendToDevice(SRFrame frame);
void SendToDevice(MRFrame frame);
};
#endif
