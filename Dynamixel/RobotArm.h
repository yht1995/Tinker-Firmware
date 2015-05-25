#ifndef __ROBOTARM_H_
#define __ROBOTARM_H_

#include "AX12.h"
#include "config.h"

class RobotArm
{
private:
	AX12 *Joints[6];
	bool isMoving();
public:
	RobotArm(PinName tx, PinName rx);
	~RobotArm();
	int SetArmPosition(int* data);
};

#endif
