//#include "stdafx.h"
#include "../../../stdafx.h"
#include "B_Cannonball.h"


B_Cannonball::B_Cannonball(void)
{
	type = BT_Cannonball;
	LoadData(BT_Cannonball);
	shapeType=S_Circle;
	Init_GameEntity();
}

B_Cannonball::B_Cannonball(double x,double y,double rr,int launcherIDX,bullettypename t)
{
	type = t;
	shapeType=S_Circle;
	LoadData(type);

	GeneralInit(x,y,rr,launcherIDX);

}


B_Cannonball::~B_Cannonball(void)
{
}




bool B_Cannonball::HitObstcale(Obstacle& ob)
{
	return GeneralHitObstcale(ob);
}



bool B_Cannonball::Hit(Robot& robot)
{
	return GeneralHit(robot);
}


bool B_Cannonball::HitFlyEnd()
{
	return false;
}