//#include "stdafx.h"
#include "../../../stdafx.h"
#include "B_Tesla_Lightning.h"

B_Tesla_Lightning::B_Tesla_Lightning(void)
{
	shapeType=S_Beam;
	//LoadData(BT_Prism_Laser);
}

B_Tesla_Lightning::B_Tesla_Lightning(double x,double y,double rr,int launcherIDX)
{
	shapeType=S_Beam;
	LoadData(BT_Tesla_Lightning);
	launcherID=launcherIDX;

	beam.x=x;
	beam.y=y;
	beam.rotation=rr;

	rotation=0;		//不飞行

	vx=0;
	vy=0;
	vr=0;
}



B_Tesla_Lightning::~B_Tesla_Lightning(void)
{
}

bool B_Tesla_Lightning::HitObstcale(Obstacle& ob)
{
	//消失返回true
	return true;
}
void B_Tesla_Lightning::Hit(Robot& robot)
{
	robot.GetEngine().ModifyHp(-damage);
	
	Robot* r=(Robot*)(pmngr->GetEntityFromID(launcherID));
	r->GetAchievementData().Add_hit();
	r->GetAchievementData().Add_output(damage);
}

void B_Tesla_Lightning::AdjustDirection(Robot & robot)
{
}