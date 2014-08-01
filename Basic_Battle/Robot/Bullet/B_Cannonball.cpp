//#include "stdafx.h"
#include "../../../stdafx.h"
#include "B_Cannonball.h"


B_Cannonball::B_Cannonball(void)
{
	LoadData(BT_Cannonball);
	shapeType=S_Circle;
	Init_GameEntity();
}

B_Cannonball::B_Cannonball(double x,double y,double rr,int launcherIDX)
{
	shapeType=S_Circle;
	LoadData(BT_Cannonball);

	GeneralInit(x,y,rr,launcherIDX);

}


B_Cannonball::~B_Cannonball(void)
{
}

/*
void B_Cannonball::Hit(Robot & robot)
{
	//加农炮弹，最普通的炮弹
	robot.GetEngine().ModifyHp(-damage);
	//发送一个Hit信息给RecordManager？
	//写到flash里的动画信息？由RecordManager完成？
}
*/
bool B_Cannonball::HitObstcale(Obstacle& ob)
{
	//消失返回true
	return true;
}

void B_Cannonball::Hit(Robot& robot)
{
	robot.GetEngine().ModifyHp(-damage);

	Robot* r=pBattlefield->GetRobotPointer(launcherID);
	r->GetAchievementData().Add_hit();
	r->GetAchievementData().Add_output(damage);
}

