#ifndef __DMS_055A_H__
#define __DMS_055A_H__

#include <stdint.h>
#include <stdbool.h>
#include "frame_type.h"
#include "../NAL/nal.h"

class DMS055A {
public:
static void BoardCastEnableOutput(bool enable = true);
static MotorNal &nal;

DMS055A(uint8_t id);
void EnableModbus(bool enable = true);
void EnableOutput(bool enable = true);
void SetTargetSpeed(int speed);
void SetTargetPosition(int step);

private:
uint8_t _device_id;
uint16_t _target_speed;
uint32_t _target_position;
uint32_t _absolute_position;

void send(uint16_t addr, uint16_t data);
void send(uint16_t addr, uint32_t data);

static const uint8_t FUNC_WRITE_SINGLE = 0x06;
static const uint8_t FUNC_WRITE_DOUBLE = 0x10;

static const uint8_t ADDR_MODBUS_ENABLE = 00;
static const uint8_t ADDR_OUTPUT_ENABLE = 01;
static const uint8_t ADDR_TARGET_SPEED = 02;
static const uint8_t ADDR_MAX_SPEED = 02;
static const uint8_t ADDR_ACCEL = 03;
static const uint8_t ADDR_MIN_SPEED = 04;
static const uint8_t ADDR_TARGET_POS = 12;
};
#endif
