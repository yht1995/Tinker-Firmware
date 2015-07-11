#include "main.h"
#include "PlatFormMove.h"

DigitalOut Connected(LED1);
DigitalOut Process(LED2);
DigitalOut SysEnable(LED3);

InterruptIn topNotReached(PIN_TOP_REACH);
InterruptIn buttomNotReached(PIN_BUTTOM_REACH);

DigitalOut downMoveOut(PIN_DOWN_OUT);
DigitalOut upMoveOut(PIN_UP_OUT);


Motor motor1(PIN_FOCMOTOR_TX,PIN_FOCMOTOR_RX,0x0011,PIN_Encoder1);
Motor motor2(PIN_FOCMOTOR_TX,PIN_FOCMOTOR_RX,0x0012,PIN_Encoder2);
Motor motor3(PIN_FOCMOTOR_TX,PIN_FOCMOTOR_RX,0x0013,PIN_Encoder3);
Motor motor4(PIN_FOCMOTOR_TX,PIN_FOCMOTOR_RX,0x0014,PIN_Encoder4);
Motor *motorTable[4] = {&motor1,&motor2,&motor3,&motor4};

//RobotArm robotArm(PIN_DYNAMIXEL_TX,PIN_DYNAMIXEL_RX);

UDPSocket server;
Endpoint client;

int main (void)
{
	Connected = 1;
	Process = 1;
	SysEnable = 1;
    printf("setting up\n");
	topNotReached.mode(PullUp);
	buttomNotReached.mode(PullUp);
	topNotReached.fall(stop_platform);
	buttomNotReached.fall(stop_platform);
    EthernetInterface eth;
    eth.init(IP,NETMASK,GATEWAY);
    eth.connect();
    printf("IP Address is %s\n", eth.getIPAddress());
		Connected = 0;
		Process = 1;
    server.bind(PORT);
    while (true) 
		{
				Process = 1;	
        char buffer[256],str[256];
				int n = server.receiveFrom(client,buffer, sizeof(buffer));
				Process = 0;
				if(n <= 0)
				{
					strcpy(str,"Bad");
					server.sendTo(client,str,strlen(str));
				}
				buffer[n] = 0;
				int result = CmdLineProcess(buffer);
				strcpy(str,"Received");
				server.sendTo(client,str,strlen(str));
				if(result == 0)
				{
						strcpy(str,"Command Completed!");
				}
				else if(result == CMDLINE_BAD_CMD) 
				{
						strcpy(str,"Bad command!");
				} 
				else if(result == CMDLINE_TOO_MANY_ARGS) 
				{
						strcpy(str,"Too many arguments for command processor!");
				}
				else if(result == CMDLINE_TOO_FEW_ARGS)
				{
						strcpy(str,"Too few arguments for command processor!");
				}
				else if(result == CMDLINE_INVALID_ARG)
				{
						strcpy(str,"Invalid arguments for command processor!");
				} 
				server.sendTo(client,str,strlen(str));
				strcpy(str,"");
				server.sendTo(client,str,strlen(str));
    }
}
