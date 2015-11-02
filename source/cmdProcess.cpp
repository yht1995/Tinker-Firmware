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
DMS055A motor(1);


tCmdLineEntry g_psCmdTable[] =
{
	{ "Subscribe", SubscribeHandler, "Subscribe" },
	{ "EN", EnableHandler, "Enable" },
	{ "SP", SetSpeedHandler, "SetSpeed" },
	{ "SS", SetPosHandler, "SetPos" },
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
		motor.EnableModbus();
		motor.EnableOutput();
		return 0;
	}else if (argc < correctArgc) {
		return CMDLINE_TOO_FEW_ARGS;
	}else{
		return CMDLINE_TOO_MANY_ARGS;
	}
}

int SetSpeedHandler(int argc, char *argv[])
{
	const int correctArgc = 2;
	if (argc == correctArgc) {
		int speed = atoi(argv[1]);
		motor.SetTargetSpeed(speed);
		return 0;
	}else if (argc < correctArgc) {
		return CMDLINE_TOO_FEW_ARGS;
	}else{
		return CMDLINE_TOO_MANY_ARGS;
	}
}

int SetPosHandler(int argc, char *argv[])
{
	const int correctArgc = 2;
	if (argc == correctArgc) {
		int pos = atoi(argv[1]);
		motor.SetTargetPosition(pos);
		return 0;
	}else if (argc < correctArgc) {
		return CMDLINE_TOO_FEW_ARGS;
	}else{
		return CMDLINE_TOO_MANY_ARGS;
	}
}
