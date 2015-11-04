#include "nal.h"

#include "minar/minar.h"
#include "core-util/FunctionPointer.h"

#include "CRC/CRC.h"

using namespace mbed::util;

MotorNal::MotorNal(PinName tx, PinName rx, PinName dir)
	: _serial(tx, rx), _dir(dir), tx_buffer(64)
{
	_serial.baud(19200);
	_serial.attach(this, &MotorNal::_RxIrq, (mbed::SerialBase::IrqType)RxIrq);
	remain_to_send = 0;
	remain_to_recieve = 0;
	minar::Scheduler::postCallback(FunctionPointer0<void>(this, &MotorNal::ScheduledSend).bind()).period(minar::milliseconds(40));
}

void MotorNal::Send(SRFrame frame)
{
	tx_buffer.push_back(8);		//Bytes to send
	tx_buffer.push_back(8);		//Bytes to recieve
	uint8_t msg[8] = { frame.device_address,
			   frame.function_code,
			   (uint8_t)(frame.register_address >> 8),
			   (uint8_t)(frame.register_address & 0xff),
			   (uint8_t)(frame.register_data >> 8),
			   (uint8_t)(frame.register_data & 0xff) };
	frame.crc = CRC16(msg, 6);
	msg[6] = (uint8_t)(frame.crc & 0xff);
	msg[7] = (uint8_t)(frame.crc >> 8);
	for (size_t i = 0; i < 8; i++) {
		tx_buffer.push_back(msg[i]);
	}
}

void MotorNal::Send(DRFrame frame)
{
	tx_buffer.push_back(13);	//Bytes to send
	tx_buffer.push_back(8);		//Bytes to recieve
	uint8_t msg[13] = { frame.device_address,
			    frame.function_code,
			    (uint8_t)(frame.register_address >> 8),
			    (uint8_t)(frame.register_address & 0xff),
			    (uint8_t)(0x00),//frame.register_register_count
			    (uint8_t)(0x02),//frame.register_register_count
			    (uint8_t)(0x04),
			    (uint8_t)(frame.register_data >> 8),
			    (uint8_t)(frame.register_data & 0xff),
			    (uint8_t)(frame.register_data >> 24),
			    (uint8_t)(frame.register_data >> 16) };
	frame.crc = CRC16(msg, 11);
	msg[11] = (uint8_t)(frame.crc & 0xff);
	msg[12] = (uint8_t)(frame.crc >> 8);
	for (size_t i = 0; i < 13; i++) {
		tx_buffer.push_back(msg[i]);
	}
}

void MotorNal::ScheduledSend()
{
	static uint8_t time_out_count = 0;
	if (remain_to_recieve == 0 && remain_to_send == 0) {
		if (!tx_buffer.isEmpty()) {
			remain_to_send = tx_buffer.pop_front();
			remain_to_recieve = tx_buffer.pop_front();
			_dir = DIR_WRITE;
			_serial.attach(this, &MotorNal::_TxIrq, (mbed::SerialBase::IrqType)TxIrq);
		}
	}else{
		time_out_count++;
	}
	if (time_out_count >=2) {
		time_out_count = 0;
		remain_to_recieve = 0;
	}
}

void MotorNal::_RxIrq()
{
	_serial.getc();
	remain_to_recieve--;
}

void MotorNal::_TxIrq()
{
	if (remain_to_send > 0) {
		_serial.putc(tx_buffer.pop_front());
		remain_to_send--;
	}else if (remain_to_send == 0) {
		_serial.attach(NULL, (mbed::SerialBase::IrqType)TxIrq);
		_tx_timer.attach_us(this,&MotorNal::_TxFinishHandler,550);
	}
}

void MotorNal::_TxFinishHandler()
{
	_dir = DIR_READ;
}
