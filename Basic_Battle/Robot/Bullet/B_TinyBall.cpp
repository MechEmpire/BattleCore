//#include "stdafx.h"
#include "../../../stdafx.h"
#include "B_TinyBall.h"


B_TinyBall::B_TinyBall(void)
{
	LoadData(BT_TinyBall);
	shapeType=S_Circle;
	Init_GameEntity();
}

B_TinyBall::B_TinyBall(double x,double y,double rr,int launcherIDX)
{
	shapeType=S_Circle;
	LoadData(BT_TinyBall);

	GeneralInit(x,y,rr,launcherIDX);

}


B_TinyBall::~B_TinyBall(void)
{
}




bool B_TinyBall::HitObstcale(Obstacle& ob)
{
	return GeneralHitObstcale(ob);
}



bool B_TinyBall::Hit(Robot& robot)
{
	return GeneralHit(robot);
}


bool B_TinyBall::HitFlyEnd()
{
	return false;
}