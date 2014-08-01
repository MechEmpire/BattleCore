//#include "stdafx.h"
#include "../../../stdafx.h"
#include "B_ElectricSaw.h"


B_ElectricSaw::B_ElectricSaw(void)
{
	LoadData(BT_ElectricSaw);
	shapeType=S_Circle;
	Init_GameEntity();
}

B_ElectricSaw::B_ElectricSaw(double x,double y,double rr,int launcherIDX)
{
	shapeType=S_Circle;
	LoadData(BT_ElectricSaw);

	launcherID=launcherIDX;

	circle.x=x;
	circle.y=y;
	//
	circle.r=0;

	rotation=rr;
	vx=0;
	vy=0;

	vr=0;

}


B_ElectricSaw::~B_ElectricSaw(void)
{
}


bool B_ElectricSaw::HitObstcale(Obstacle& ob)
{
	//ÏûÊ§·µ»Øtrue
	return true;
}

void B_ElectricSaw::Hit(Robot& robot)
{
	robot.GetEngine().ModifyHp(-damage);

	
	Robot* r=pBattlefield->GetRobotPointer(launcherID);
	r->GetAchievementData().Add_hit();
	r->GetAchievementData().Add_output(damage);
}

