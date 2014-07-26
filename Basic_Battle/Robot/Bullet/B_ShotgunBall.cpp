//#include "stdafx.h"
#include "../../../stdafx.h"
#include "B_ShotgunBall.h"


B_ShotgunBall::B_ShotgunBall(void)
{
}

B_ShotgunBall::B_ShotgunBall(double x,double y,double rr,int launcherIDX)
{
	shapeType=S_Circle;
	LoadData(BT_ShotgunBall);

	GeneralInit(x,y,rr,launcherIDX);

}




B_ShotgunBall::~B_ShotgunBall(void)
{
}

bool B_ShotgunBall::HitObstcale(Obstacle& ob)
{
	//ÏûÊ§·µ»Øtrue
	return true;
}
void B_ShotgunBall::Hit(Robot& robot)
{
	robot.GetEngine().ModifyHp(-damage);
	
	Robot* r=(Robot*)(pmngr->GetEntityFromID(launcherID));
	r->GetAchievementData().Add_hit();
	r->GetAchievementData().Add_output(damage);
}

void B_ShotgunBall::AdjustDirection(Robot & robot)
{
}