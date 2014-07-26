//#include "stdafx.h"
#include "../../../stdafx.h"
#include "B_TrackingMissile.h"


B_TrackingMissile::B_TrackingMissile(void)
{
}

B_TrackingMissile::B_TrackingMissile(double x,double y,double rr,int launcherIDX)
{
	spinSpeed=pDataLoader->GetGameData()->spinSpeed;

	shapeType=S_Circle;
	LoadData(BT_TrackingMissile);

	GeneralInit(x,y,rr,launcherIDX);
}



B_TrackingMissile::~B_TrackingMissile(void)
{
}

bool B_TrackingMissile::HitObstcale(Obstacle& ob)
{
	//消失返回true
	return true;
}
void B_TrackingMissile::Hit(Robot& robot)
{
	robot.GetEngine().ModifyHp(-damage);
	
	Robot* r=(Robot*)(pmngr->GetEntityFromID(launcherID));
	r->GetAchievementData().Add_hit();
	r->GetAchievementData().Add_output(damage);
}

void B_TrackingMissile::AdjustDirection(Robot & robot)
{
	double rr=atan2(robot.GetEngine().GetCircle().y-circle.y,robot.GetEngine().GetCircle().x-circle.x);
	rr=RadianToAngle(rr);

	double c=0,a=0;		//顺时针，逆时针
	
	if(rr>rotation)
	{
		c=rr-rotation;
		a=rotation+360-rr;	//(rotation-(-180))+(180-rr)
	}
	else
	{
		a=rotation-rr;
		c=360-rotation+rr;	//(180-rotation)+(rr-(-180));
	}

	if(c>a)
	{
		rotation-=spinSpeed;
	}
	else
	{
		rotation+=spinSpeed;
	}

	rr=AngleToRadian(rotation);

	vx=cos(rr)*speed;
	vy=sin(rr)*speed;

}