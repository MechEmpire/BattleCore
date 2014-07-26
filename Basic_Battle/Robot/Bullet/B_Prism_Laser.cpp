//#include "stdafx.h"
#include "../../../stdafx.h"
#include "B_Prism_Laser.h"


B_Prism_Laser::B_Prism_Laser(void)
{
	shapeType=S_Beam;
	//LoadData(BT_Prism_Laser);
}

B_Prism_Laser::B_Prism_Laser(double x,double y,double rr,int launcherIDX)
{
	shapeType=S_Beam;
	LoadData(BT_Prism_Laser);
	launcherID=launcherIDX;

	beam.x=x;
	beam.y=y;
	beam.rotation=rr;

	rotation=0;		//不飞行

	vx=0;
	vy=0;
	vr=0;
}



B_Prism_Laser::~B_Prism_Laser(void)
{
}

bool B_Prism_Laser::HitObstcale(Obstacle& ob)
{
	//消失返回true
	return true;
}
void B_Prism_Laser::Hit(Robot& robot)
{
	robot.GetEngine().ModifyHp(-damage);
	
	Robot* r=(Robot*)(pmngr->GetEntityFromID(launcherID));
	r->GetAchievementData().Add_hit();
	r->GetAchievementData().Add_output(damage);
}

void B_Prism_Laser::AdjustDirection(Robot & robot)
{
}