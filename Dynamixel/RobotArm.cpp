#include "RobotArm.h"

RobotArm::RobotArm(PinName tx, PinName rx)
{
	for(int i = 0;i<JOINTNUM;i++)
	{
		Joints[i] =	new AX12(tx,rx,i);
	}
}

RobotArm::~RobotArm()
{
	for(int i = 0;i<6;i++)
	{
		delete Joints[i];
	}
}

int RobotArm::SetArmPosition(int* data)
{
	Timer timer;
	timer.reset();
	timer.start();
	for(int i = 0;i<JOINTNUM;i++)
	{
		Joints[i]->SetGoal(data[i]);
	}
	while(isMoving())
	{
		if(timer.read_ms()>3000)
		{
			return 1;
		}
	}
	return 0;	
}

bool RobotArm::isMoving()
{
	int moving = 0;
	for(int i = 0;i<JOINTNUM;i++)
	{
		moving += Joints[i]->isMoving();
	}
	if(moving>=0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
