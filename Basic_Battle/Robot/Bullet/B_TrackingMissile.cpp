//#include "stdafx.h"
#include "../../../stdafx.h"
#include "B_TrackingMissile.h"


B_TrackingMissile::B_TrackingMissile(void)
{
}

B_TrackingMissile::B_TrackingMissile(double x,double y,double rr,int launcherIDX,int chaseIDX)
{
	spinSpeed=pDataLoader->GetGameData()->spinSpeed;

	shapeType=S_Circle;
	LoadData(BT_TrackingMissile);

	GeneralInit(x,y,rr,launcherIDX);

	chaseID=chaseIDX;
	if(chaseID<0 || chaseID>=(pBattlefield->GetBattleStatistivs().numRobots) )
	{
		//选手传入参数出错

		//默认追踪一个不是发射者的Robo（可能已经挂了）
		if(launcherID>0)
		{
			chaseID=launcherID-1;
		}
		else
		{
			chaseID=launcherID+1;
		}
	}
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
	
	Robot* r=pBattlefield->GetRobotPointer(launcherID);
	r->GetAchievementData().Add_hit();
	r->GetAchievementData().Add_output(damage);
}


int B_TrackingMissile::GetChaseID()
{
	return chaseID;
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