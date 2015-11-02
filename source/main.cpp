#include <mbed.h>
#include "EthernetInterface.h"
#include "mbed-net-sockets/UDPSocket.h"
#include "mbed-net-lwip/lwipv4_init.h"
#include "mbed-net-socket-abstract/socket_api.h"
#include "minar/minar.h"

#include "cmdline/cmdline.h"
#include <string>

using namespace mbed::Sockets::v0;

static const int BUFFER_SIZE = 64;
static const int PORT = 21;
static const char* LOCAL_IP = "192.168.2.10";
static const char* NETMASK = "255.255.255.0";
static const char* GATEWAY = "192.168.2.1";

EthernetInterface eth;
UDPSocket *udpserver;
SocketAddr addr;
SocketAddr remote_addr;

char buffer[BUFFER_SIZE] = { 0 };
char response[BUFFER_SIZE] = { 0 };

void onError(Socket *s, socket_error_t err)
{
	(void)s;
	printf("MBED: Socket Error: %s (%d)\r\n", socket_strerror(err), err);
}

void onRx(Socket *s)
{
	uint16_t port;
	size_t len = BUFFER_SIZE - 1;
	/* Recieve the packet */
	socket_error_t err = s->recv_from(buffer, &len, &addr, &port);
	if (!s->error_check(err) && len) {
		buffer[len] = 0;
		int result = CmdLineProcess(buffer);

		switch (result) {
		case 0:
			strcpy(response, "Command Completed!");
			break;
		case CMDLINE_BAD_CMD:
			strcpy(response, "Bad command!");
			break;
		case CMDLINE_TOO_MANY_ARGS:
			strcpy(response, "Too many arguments!");
			break;
		case CMDLINE_TOO_FEW_ARGS:
			strcpy(response, "Too few arguments!");
			break;
		case CMDLINE_INVALID_ARG:
			strcpy(response, "Invalid arguments!");
			break;
		}
		err = s->send_to(response, strlen(response), &addr, port);
		if (err != SOCKET_ERROR_NONE) {
			onError(s, err);
		}
	}
}

void app_start(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	eth.init(LOCAL_IP, NETMASK, GATEWAY);
	eth.connect();
	socket_error_t err = lwipv4_socket_init();
	if (err) {
		return;
	}

	udpserver = new UDPSocket(SOCKET_STACK_LWIP_IPV4);
	udpserver->setOnError(UDPSocket::ErrorHandler_t(onError));
	udpserver->open(SOCKET_AF_INET4);
	err = udpserver->bind("0.0.0.0", PORT);
	udpserver->error_check(err);
	udpserver->setOnReadable(UDPSocket::ReadableHandler_t(onRx));

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
