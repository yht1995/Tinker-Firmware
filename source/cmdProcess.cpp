#include "cmdProcess.h"
#include "mbed-net-sockets/SocketAddr.h"
#include "mbed-net-sockets/UDPSocket.h"

#include "minar/minar.h"
#include "core-util/FunctionPointer.h"

using namespace mbed::util;

extern mbed::Sockets::v0::SocketAddr addr;
extern mbed::Sockets::v0::SocketAddr remote_addr;
extern mbed::Sockets::v0::UDPSocket *udpserver;

tCmdLineEntry g_psCmdTable[] =
{
	{ "Subscribe", SubscribeHandler, "Subscribe" },
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
		if (period >=10 && period <= 10000) {
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
