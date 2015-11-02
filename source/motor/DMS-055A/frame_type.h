#ifndef __DMS_055A_FRAME_TYPE_H__
#define __DMS_055A_FRAME_TYPE_H__

#include <stdint.h>

struct Single_Register_Frame {
	uint8_t device_address;
	uint8_t function_code;
	uint16_t register_address;
	uint16_t register_data;
	uint16_t crc;
};

typedef struct Single_Register_Frame SRFrame;


struct Double_Register_Frame {
	uint8_t device_address;
	uint8_t function_code;
	uint16_t register_address;
	uint32_t register_data;
	uint16_t crc;
};

typedef struct Double_Register_Frame DRFrame;


struct Read_Frame_ACK {
	uint8_t device_address;
	uint8_t function_code;
	uint8_t length;
	uint16_t data;
	uint16_t crc;
};

typedef struct Read_Frame_ACK ReadFrameACK;

struct Write_Frame_ACK {
	uint8_t device_address;
	uint8_t function_code;
	uint16_t register_address;
	uint16_t register_data;
	uint16_t crc;
};

typedef struct Write_Frame_ACK WriteFrameACK;
#endif
