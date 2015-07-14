#include "PlatFormMove.h"
#include "main.h"

void move_up_platform()
{
	if(topNotReached)
	{
		upMoveOut = 1;
		downMoveOut = 0;
	}
}

void move_down_platform()
{
	if(buttomNotReached)
	{
		upMoveOut = 0;
		downMoveOut = 1;
	}
}

void stop_platform()
{
	upMoveOut = 0;
	downMoveOut = 0;
}

void top_reached_handler()
{
	for(int i=0; i < 10; i++)
	{
		if(topNotReached) return;
		wait_ms(10);
	}
	stop_platform();
}

void buttom_reached_handler()
{
	for(int i=0; i < 10; i++)
	{
		if(buttomNotReached) return;
		wait_ms(10);
	}
	stop_platform();
}
