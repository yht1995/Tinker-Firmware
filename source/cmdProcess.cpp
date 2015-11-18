#include "mbed-net-sockets/SocketAddr.h"
#include "mbed-net-sockets/UDPSocket.h"
#include "minar/minar.h"
#include "core-util/FunctionPointer.h"

#include "cmdProcess.h"
#include "config.h"
#include "motor/DMS-055A/DMS-055A.h"
#include "motor/NAL/nal.h"

using namespace mbed::util;

extern mbed::Sockets::v0::SocketAddr addr;
extern mbed::Sockets::v0::SocketAddr remote_addr;
extern mbed::Sockets::v0::UDPSocket *udpserver;

MotorNal motorNal(PIN_MOTOR_TX, PIN_MOTOR_RX, PIN_RS485_DIR);
MotorNal& DMS055A::nal = motorNal;
DMS055A motor1(1);
DMS055A motor2(2);
DMS055A motor3(3);
DMS055A motor4(4);
DMS055A *motor_list[4] = { &motor1, &motor2, &motor3, &motor4 };


tCmdLineEntry g_psCmdTable[] =
{
	{ "Subscribe", SubscribeHandler, "Subscribe" },
	{ "EN", EnableHandler, "Enable" },
	{ "DIS", DisableHandler, "Disable" },
	{ "SS", SetSpeedHandler, "SetSpeed" },
	{ "SP", SetPosHandler, "SetPos" },
	{ "SG", SetGearHandler, "SetGear" },
	{ 0, 0, 0 }
};

void UploadInfo()
{
	//TODO: Finish this Function
	char str[] = "hello";
	udpserver->send_to(str, strlen(str), &remote_addr, 21);
}

int SubscribeHandler(int argc, char *argv[])
{
	const int correctArgc = 2;
	if (argc == correctArgc) {
		int period = atoi(argv[1]);
		if (period >= 10 && period <= 10000) {
			//Save the remote IP to remote_addr
			remote_addr.setAddr(&addr);
			//Start the Scheduler to UploadInfo
			minar::Scheduler::postCallback(FunctionPointer0<void>(UploadInfo).bind()).period(minar::milliseconds(period));
			return 0;
		}else{
			return CMDLINE_INVALID_ARG;
		}
	}else if (argc < correctArgc) {
		return CMDLINE_TOO_FEW_ARGS;
	}else{
		return CMDLINE_TOO_MANY_ARGS;
	}
}

int EnableHandler(int argc, char *argv[])
{
	(void)argv;
	const int correctArgc = 1;
	if (argc == correctArgc) {
		for (uint8_t i = 0; i < 4; i++) {
			motor_list[i]->EnableModbus();
			motor_list[i]->EnableOutput();
		}
		return 0;
	}else if (argc < correctArgc) {
		return CMDLINE_TOO_FEW_ARGS;
	}else{
		return CMDLINE_TOO_MANY_ARGS;
	}
}

int DisableHandler(int argc, char *argv[])
{
	(void)argv;
	const int correctArgc = 1;
	if (argc == correctArgc) {
		for (uint8_t i = 0; i < 4; i++) {
			motor_list[i]->EnableModbus(false);
			motor_list[i]->EnableOutput(false);
		}
		return 0;
	}else if (argc < correctArgc) {
		return CMDLINE_TOO_FEW_ARGS;
	}else{
		return CMDLINE_TOO_MANY_ARGS;
	}
}

int SetSpeedHandler(int argc, char *argv[])
{
	const int correctArgc = 5;
	if (argc == correctArgc) {
		for (uint8_t i = 0; i < 4; i++) {
			int speed = atoi(argv[i + 1]);
			motor_list[i]->SetTargetSpeed(speed);
		}
		return 0;
	}else if (argc < correctArgc) {
		return CMDLINE_TOO_FEW_ARGS;
	}else{
		return CMDLINE_TOO_MANY_ARGS;
	}
}

int SetPosHandler(int argc, char *argv[])
{
	const int correctArgc = 5;
	if (argc == correctArgc) {
		for (uint8_t i = 0; i < 4; i++) {
			int pos = atoi(argv[i + 1]);
			motor_list[i]->SetTargetPosition(pos);
		}
		return 0;
	}else if (argc < correctArgc) {
		return CMDLINE_TOO_FEW_ARGS;
	}else{
		return CMDLINE_TOO_MANY_ARGS;
	}
}

int SetGearHandler(int argc, char *argv[])
{
	const int correctArgc = 3;
	if (argc == correctArgc) {
		int numerator = atoi(argv[1]);
		int denominator = atoi(argv[2]);
		for (uint8_t i = 0; i < 4; i++) {
			motor_list[i]->SetGear(numerator, denominator);
		}
		return 0;
	}else if (argc < correctArgc) {
		return CMDLINE_TOO_FEW_ARGS;
	}else{
		return CMDLINE_TOO_MANY_ARGS;
	}
}
