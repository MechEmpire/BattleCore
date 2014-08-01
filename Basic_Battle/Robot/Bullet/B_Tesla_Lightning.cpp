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

	rotation=0;		//²»·ÉÐÐ

	vx=0;
	vy=0;
	vr=0;
}



B_Tesla_Lightning::~B_Tesla_Lightning(void)
{
}

bool B_Tesla_Lightning::HitObstcale(Obstacle& ob)
{
	return GeneralHitObstcale(ob);
}
void B_Tesla_Lightning::Hit(Robot& robot)
{
	GeneralHit(robot);
}

void B_Tesla_Lightning::HitFlyEnd()
{
}
