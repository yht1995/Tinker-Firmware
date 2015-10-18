#include <mbed.h>
#include "EthernetInterface.h"
#include "mbed-net-sockets/UDPSocket.h"
#include "mbed-net-lwip/lwipv4_init.h"
#include "mbed-net-socket-abstract/socket_api.h"
#include "minar/minar.h"

#include "Motor/Motor.h"
#include "cmdline/cmdline.h"
#include "config.h"
#include <string>

namespace {
const int ECHO_SERVER_PORT = 7;
const int BUFFER_SIZE = 512;
}

using namespace mbed::Sockets::v0;

DigitalOut Connected(LED1);
DigitalOut Process(LED2);
DigitalOut SysEnable(LED3);

Motor motor1(PIN_FOCMOTOR_TX, PIN_FOCMOTOR_RX, 0x0011, PIN_Encoder1);
Motor motor2(PIN_FOCMOTOR_TX, PIN_FOCMOTOR_RX, 0x0012, PIN_Encoder2);
Motor motor3(PIN_FOCMOTOR_TX, PIN_FOCMOTOR_RX, 0x0013, PIN_Encoder3);
Motor motor4(PIN_FOCMOTOR_TX, PIN_FOCMOTOR_RX, 0x0014, PIN_Encoder4);
Motor *motorTable[4] = { &motor1, &motor2, &motor3, &motor4 };

EthernetInterface eth;
UDPSocket *udpserver;

char buffer[BUFFER_SIZE] = { 0 };

void onError(Socket *s, socket_error_t err)
{
	(void)s;
	printf("MBED: Socket Error: %s (%d)\r\n", socket_strerror(err), err);
	minar::Scheduler::stop();
}
void onRx(Socket *s)
{
	SocketAddr addr;
	uint16_t port;
	size_t len = BUFFER_SIZE - 1;
	/* Recieve the packet */
	socket_error_t err = s->recv_from(buffer, &len, &addr, &port);
	if (!s->error_check(err) && len) {
		buffer[len] = 0;
		char str[256];
		/* Send the packet */
		int result = CmdLineProcess(buffer);
		strcpy(str, "Received");
		err = s->send_to(str, strlen(str), &addr, port);
		if (result == 0) {
			strcpy(str, "Command Completed!");
		}else if (result == CMDLINE_BAD_CMD) {
			strcpy(str, "Bad command!");
		}else if (result == CMDLINE_TOO_MANY_ARGS) {
			strcpy(str, "Too many arguments for command processor!");
		}else if (result == CMDLINE_TOO_FEW_ARGS) {
			strcpy(str, "Too few arguments for command processor!");
		}else if (result == CMDLINE_INVALID_ARG) {
			strcpy(str, "Invalid arguments for command processor!");
		}

		err = s->send_to(str, strlen(str), &addr, port);
		printf("MBED: Received message: %s\r\n", buffer);
		if (err != SOCKET_ERROR_NONE) {
			onError(s, err);
		}
	}
}

void app_start(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	Connected = 1;
	Process = 1;
	SysEnable = 1;
	printf("setting up\n");
	eth.init(IP, NETMASK, GATEWAY);
	eth.connect();
	printf("IP Address is %s\n", eth.getIPAddress());
	Connected = 0;
	Process = 1;
	socket_error_t err = lwipv4_socket_init();
	if (err) {
		printf("MBED: Failed to initialize socket stack (%d)\r\n", err);
		return;
	}
	udpserver = new UDPSocket(SOCKET_STACK_LWIP_IPV4);

	printf("MBED: UDP Server IP Address is %s:%d\r\n", eth.getIPAddress(), ECHO_SERVER_PORT);

	udpserver->setOnError(UDPSocket::ErrorHandler_t(onError));
	udpserver->open(SOCKET_AF_INET4);
	err = udpserver->bind("0.0.0.0", ECHO_SERVER_PORT);
	udpserver->error_check(err);
	udpserver->setOnReadable(UDPSocket::ReadableHandler_t(onRx));

	printf("MBED: Waiting for packet...\r\n");
	return;
}

// for non-mbed-os targets, main is the entry point. The mbed OS scheduler uses
// app-start as the entry point (see https://github.com/ARMmbed/mbed-drivers)
#ifndef TARGET_LIKE_MBED
int main()
{
	app_start(0, (char**)0);
	return 0;
}
#endif
