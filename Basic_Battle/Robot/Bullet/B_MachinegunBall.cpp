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
	//ÏûÊ§·µ»Øtrue
	return true;
}
void B_MachinegunBall::Hit(Robot& robot)
{
	robot.GetEngine().ModifyHp(-damage);
	
	Robot* r=(Robot*)(pmngr->GetEntityFromID(launcherID));
	r->GetAchievementData().Add_hit();
	r->GetAchievementData().Add_output(damage);
}

void B_MachinegunBall::AdjustDirection(Robot & robot)
{
}