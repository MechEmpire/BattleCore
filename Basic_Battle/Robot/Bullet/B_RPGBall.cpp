//#include "stdafx.h"
#include "../../../stdafx.h"
#include "B_RPGBall.h"

//double B_RPGBall::Explode_R=pDataLoader->GetGameData()->explodeR_RPGBall;

B_RPGBall::B_RPGBall(void)
{
}


B_RPGBall::B_RPGBall(double x,double y,double rr,int launcherIDX)
{
	Explode_R=pDataLoader->GetGameData()->explodeR_RPGBall;
	acceleration_rpgball=pDataLoader->GetGameData()->acceleration_RPGBall;


	shapeType=S_Circle;
	LoadData(BT_RPGBall);
	//Explode_R=pDataLoader->GetGameData()->explodeR_RPGBall;


	GeneralInit(x,y,rr,launcherIDX);

	/*
	launcherID=launcherIDX;

	circle.x=x;
	circle.y=y;
	//
	circle.r=0;

	rotation=rr;
	rr=AngleToRadian(rotation);
	//...
	//speed=.....//来自脚本的数据
	vx=speed*cos(rr);
	vy=speed*sin(rr);

	vr=0;
	*/
}

B_RPGBall::~B_RPGBall(void)
{
}


void B_RPGBall::Hit(Robot & robot)
{
	//产生范围爆炸
	Circle* expld=new Circle;
	expld->x=circle.x;
	expld->y=circle.y;
	expld->r=Explode_R;

	pDispatcher->DispatchEvent(ID,pBattlefield->GetID(),
		Explode,expld);
	//Dispatch_Remove_Event();删除在Battlefield.cpp里做

	//TODO:范围伤害的统计计算？
	Robot* r=pBattlefield->GetRobotPointer(launcherID);
	r->GetAchievementData().Add_hit();
	r->GetAchievementData().Add_output(damage);
}

bool B_RPGBall::HitObstcale(Obstacle & ob)
{
	//产生范围爆炸
	Circle* expld=new Circle;
	expld->x=circle.x;
	expld->y=circle.y;
	expld->r=Explode_R;

	pDispatcher->DispatchEvent(ID,pBattlefield->GetID(),
		Explode,expld);

	return true;
	//Dispatch_Remove_Event();删除在Battlefield.cpp里做
}



void B_RPGBall::Update()
{
	//火箭弹加速，覆盖GameEntity::Update
	circle.x+=vx;
	circle.y+=vy;
	//rotation=AnglePlus(rotation,vr);
	vx*=acceleration_rpgball;
	vy*=acceleration_rpgball;

	//test
	//cout<<"RPG：调用的是新的Update\n";
}

void B_RPGBall::HitFlyEnd()
{
}