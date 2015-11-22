#include "DMS-055A.h"

DMS055A::DMS055A (uint8_t id)
{
	this->_device_id = id;
}

void DMS055A::EnableModbus(bool enable)
{
	if (enable) {
		send(ADDR_MODBUS_ENABLE, (uint16_t)1);
	}else{
		send(ADDR_MODBUS_ENABLE, (uint16_t)0);
	}
}

void DMS055A::EnableOutput(bool enable)
{
	if (enable) {
		send(ADDR_OUTPUT_ENABLE, (uint16_t)1);
	}else{
		send(ADDR_OUTPUT_ENABLE, (uint16_t)0);
		send(ADDR_OUTPUT_ENABLE, (uint16_t)0);
	}
}

void DMS055A::SetTargetSpeed(int speed)
{
	send(ADDR_TARGET_SPEED, (uint16_t)speed);
}

void DMS055A::SetTargetPosition(int step)
{
	//send(ADDR_TARGET_POS, (uint32_t)step);
	sendpos(step);
}

void DMS055A::SetGear(int numerator,int denominator)
{
	send(ADDR_GEAR_NUMERATOR,(uint16_t)numerator);
	send(ADDR_GEAR_DENOMINATOR,(uint16_t)denominator);
}

void DMS055A::send(uint16_t addr, uint16_t data)
{
	SRFrame frame;
	frame.device_address = this->_device_id;
	frame.function_code = FUNC_WRITE_SINGLE;
	frame.register_address = addr;
	frame.register_data = data;

	nal.Send(frame);
}

void DMS055A::send(uint16_t addr, uint32_t data)
{
	DRFrame frame;
	frame.device_address = this->_device_id;
	frame.function_code = FUNC_WRITE_DOUBLE;
	frame.register_address = addr;
	frame.register_data = data;

	nal.Send(frame);
}

void DMS055A::sendpos(uint32_t data)
{
	SRFrame frame;
	frame.device_address = this->_device_id;
	frame.function_code = FUNC_WRITE_POS;
	frame.register_address = data >> 16;
	frame.register_data = data & 0xffff;

	nal.Send(frame);
}
