//#include "stdafx.h"
#include "../../../stdafx.h"
#include "B_Mine.h"


B_Mine::B_Mine(void)
{
	
}

B_Mine::B_Mine(double x,double y,double rr,int launcherIDX)
{
	Explode_R=pDataLoader->GetGameData()->explodeR_Grenade;

	shapeType=S_Circle;
	LoadData(BT_Mine);

	GeneralInit(x,y,rr,launcherIDX);

}


B_Mine::~B_Mine(void)
{
}




bool B_Mine::HitObstcale(Obstacle& ob)
{
	return GeneralHitObstcale(ob);
}

void B_Mine::Explode()
{
	//产生范围爆炸
	Circle* expld=new Circle;
	expld->x=circle.x;
	expld->y=circle.y;
	expld->r=Explode_R;

	pDispatcher->DispatchEvent(ID,pBattlefield->GetID(),
		Explode_RPG,expld);
	//Dispatch_Remove_Event();删除在Battlefield.cpp里做
}

bool B_Mine::Hit(Robot& robot)
{
	Explode();

	//TODO:范围伤害的统计计算？
	Robot* r=pBattlefield->GetRobotPointer(launcherID);
	r->GetAchievementData().Add_hit();
	r->GetAchievementData().Add_output(damage);

	return true;
}


bool B_Mine::HitFlyEnd()
{
	Explode();
	return true;
}

