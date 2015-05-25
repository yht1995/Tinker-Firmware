#include "cmdProcess.h"

tCmdLineEntry g_psCmdTable[] = 
{
	{ "EnableSystem", ProcessEnable, "EnableSystem" },
	{ "ShutdownSystem", ProcessShutdown, "ShutdownSystem" },
    { "SetRobotSpeed", ProcessSetRobotSpeed, "SetRobotSpeed" },
    { "SetMotorSpeed", ProcessSetMotorSpeed, "SetMotorSpeed" },
    { "GetEncoderChange", ProcessGetEncoderChange, "GetEncoderChange" },
	{ "SetMaxAccel", ProcessSetMaxAccel, "SetMaxAccel" },
    { "RobotArmSet", ProcessRobotArmSet, "RobotArmSet" },
    { "help", ProcessHelp, "Help" },
    { 0, 0, 0 }
};

void Mecanum(int Vx,int Vy,int Omega)
{
    float speed[4];
    speed[0] = Vx + Vy - Omega;
    speed[1] = Vx - Vy + Omega;
    speed[2] = Vx - Vy - Omega;
    speed[3] = Vx + Vy + Omega;
    for(int i=0; i<4; i++) 
		{
        speed[i] = speed[i] * Polar[i];
        motorTable[i]->SetSpeed(speed[i]);
    }
}

int ProcessEnable(int argc, char *argv[])
{
		if(argc>1) 
		{
        return CMDLINE_TOO_MANY_ARGS;
    }
		for(int i=0; i<4; i++) 
		{
        motorTable[i]->EnableDriver(true);
    }
		SysEnable = 0;
		return 0;
}
	
int ProcessShutdown(int argc, char *argv[])
{
		if(argc>1) 
		{
        return CMDLINE_TOO_MANY_ARGS;
    }
		for(int i=0; i<4; i++) 
		{
        motorTable[i]->SetSpeed(0);
    }
		for(int i=0; i<4; i++) 
		{
        motorTable[i]->EnableDriver(false);
    }
		SysEnable = 1;
		return 0;
}

int ProcessSetRobotSpeed(int argc, char *argv[])
{
    static int Vx = 0,Vy = 0,Omega = 0;
    if(argc<3) {
        return CMDLINE_TOO_FEW_ARGS;
    }
    if(argc>3) {
        return CMDLINE_TOO_MANY_ARGS;
    }
    if(!strcmp(argv[1],"Vx")) 
		{
        Vx = atoi(argv[2]);
    } 
		else if(!strcmp(argv[1],"Vy")) 
		{
        Vy = atoi(argv[2]);
    } 
		else if(!strcmp(argv[1],"Omega"))
		{
        Omega = atoi(argv[2]);
    } 
		else 
		{
        return CMDLINE_INVALID_ARG;
    }
		printf("Vx:%d,Vy:%d,Omega:%d\n",Vx,Vy,Omega);
    Mecanum(Vx,Vy,Omega);
    return 0;
}

int ProcessSetMotorSpeed(int argc, char *argv[])
{
    if(argc<3) {
        return CMDLINE_TOO_FEW_ARGS;
    }
    if(argc>3) {
        return CMDLINE_TOO_MANY_ARGS;
    }
    int motorIndex = atoi(argv[1]) - 1;
    if(motorIndex <0 || motorIndex > 4) {
        return CMDLINE_INVALID_ARG;
    }
		float speed = (float)atoi(argv[2]);
		speed = speed * Polar[motorIndex];
    motorTable[motorIndex]->SetSpeed(speed);
    return 0;
}

int ProcessGetEncoderChange(int argc, char *argv[])
{
    if(argc<2) {
        return CMDLINE_TOO_FEW_ARGS;
    }
    if(argc>2) {
        return CMDLINE_TOO_MANY_ARGS;
    }
    int motorIndex = atoi(argv[1]) - 1;
    if(motorIndex <0 || motorIndex > 4) {
        return CMDLINE_INVALID_ARG;
    }
    char s[10];
		int change = motorTable[motorIndex]->GetEncoderChange() * Polar[motorIndex];
    sprintf(s,"%d",change);
    server.sendTo(client,s,strlen(s));
    return 0;
}

int ProcessSetMaxAccel(int argc,char* argv[])
{
	  if(argc<2) {
        return CMDLINE_TOO_FEW_ARGS;
    }
    if(argc>2) {
        return CMDLINE_TOO_MANY_ARGS;
    }
		for(int i=0; i<4; i++) 
		{
        motorTable[i]->SetMaxAccel(atoi(argv[1]));
    }
		return 0;
}

int ProcessRobotArmSet(int argc,char* argv[])
{
	  if(argc<JOINTNUM+1) {
        return CMDLINE_TOO_FEW_ARGS;
    }
    if(argc>JOINTNUM+1) {
        return CMDLINE_TOO_MANY_ARGS;
    }
		int data[JOINTNUM];
		for(int i=0;i<JOINTNUM;i++)
		{
			data[i] = atoi(argv[i+1]);
		}
		if(robotArm.SetArmPosition(data) == 0)
		{	
			return 0;
		}
		else
		{
			char s[10];
			sprintf(s,"Time Out");
			server.sendTo(client,s,strlen(s));
			return -1;
		}
}


int ProcessHelp(int argc, char *argv[])
{
	char str[512];
    if(argc == 1)
    {
			strcpy(str,"\nThese commmand can be used:\n\
EnableSystem\n\
ShutdownSystem\n\
SetRobotSpeed\n\
SetMotorSpeed\n\
SetMaxAccel\n\
GetEncoderChange\n\
type \"help <Command Name>\" for detail.\n\
======================\n\
Other command are under development\n\
For more information, please contact Timmy Yao(yaoht13@mails.tsinghua.edu.cn).");
    }   
	else if(argc == 2)
	{
		if(!strcmp(argv[1],"SetRobotSpeed"))
		{
			strcpy(str,"\nSetRobotSpeed <Vx|Vy|Omega> <Speed>\n\
Vx -- X axis speed\n\
Vy -- Y axis speed\n\
Omega -- Rotation speed");
		}
	}
	else
	{
		return CMDLINE_TOO_MANY_ARGS;
	}
	server.sendTo(client,str,strlen(str));		
    return 0;
}
