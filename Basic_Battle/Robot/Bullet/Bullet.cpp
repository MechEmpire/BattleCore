//#include "stdafx.h"
#include "../../../stdafx.h"
#include "../../struct.h"
#include "Bullet.h"
#include "../../GameEntity.h"



Bullet::Bullet(void)
{
}

Bullet::Bullet(double x,double y,double rr)
{
	shapeType=S_Circle;
	circle.x=x;
	circle.y=y;
	rotation=rr;
	rr=AngleToRadian(rotation);
	//...
	//speed=.....//来自脚本的数据
	vx=speed*cos(rr);
	vy=speed*sin(rr);
}


Bullet::~Bullet(void)
{
}


//在子弹子类构造函数最末使用
void Bullet::GeneralInit(double x,double y,double rr,int launcherIDX)
{
	launcherID=launcherIDX;

	circle.x=x;
	circle.y=y;
	circle.r=0;

	rotation=rr;
	rr=AngleToRadian(rotation);
	vx=speed*cos(rr);
	vy=speed*sin(rr);

	vr=0;

	remainingFlyTime=flyTime;
}



inline void Bullet::Dispatch_Remove_Event()
{
	pDispatcher->DispatchEvent(ID,pBattlefield->GetID(),Remove_Bullet,NULL);
}

void Bullet::LoadData(bullettypename btn)
{
	type=btn;

	name=pDataLoader->GetGameData()->name_Bullet[btn];
	speed=pDataLoader->GetGameData()->speed_Bullet[btn];
	damage=pDataLoader->GetGameData()->damage_Bullet[btn];
	flyTime=pDataLoader->GetGameData()->flyTime_Bullet[btn];
}

void Bullet::GeneralHit(Robot & robot)
{
	robot.GetEngine().ModifyHp(-damage);

	Robot* r=pBattlefield->GetRobotPointer(launcherID);
	r->GetAchievementData().Add_hit();
	r->GetAchievementData().Add_output(damage);
}