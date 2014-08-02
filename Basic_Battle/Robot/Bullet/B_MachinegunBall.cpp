//#include "stdafx.h"
#include "../../../stdafx.h"
#include "B_MachinegunBall.h"


B_MachinegunBall::B_MachinegunBall(void)
{
}

B_MachinegunBall::B_MachinegunBall(double x,double y,double rr,int launcherIDX)
{
	shapeType=S_Circle;
	LoadData(BT_MachinegunBall);

	GeneralInit(x,y,rr,launcherIDX);
}



B_MachinegunBall::~B_MachinegunBall(void)
{
}

bool B_MachinegunBall::HitObstcale(Obstacle& ob)
{
	return GeneralHitObstcale(ob);
}
bool B_MachinegunBall::Hit(Robot& robot)
{
	return GeneralHit(robot);
}

bool B_MachinegunBall::HitFlyEnd()
{
	return false;
}
