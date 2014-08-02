#include "../../../stdafx.h"
#include "Weapon.h"
#include "W_GrenadeThrower.h"

W_GrenadeThrower::W_GrenadeThrower(void)
{
	LoadData(WT_GrenadeThrower);
	InitData();
	Init_GameEntity();
}


W_GrenadeThrower::~W_GrenadeThrower(void)
{
}



bool W_GrenadeThrower::Fire(int mnplt)
{
	//应该发送一个事件给Battlefield，让其生成一个炮弹
	//低级一点的就是用传入一个指向Battlefield的指针来操作（这样总觉得Robot类与Battlefield类紧耦合了又)
	if(General_Fire(mnplt))
	{
		double p=inaccuracy*(Random0_1()-0.5);//偏移角度
		//double r=AnglePlus(AnglePlus(rotation,engineRotation),p);//角度
		double r=AnglePlus(rotation,p);
		double a=AngleToRadian(r);//弧度

		pDispatcher->DispatchEvent(ID,pBattlefield->GetID(),
			Add_Bullet,
			new B_Grenade(circle.r*cos(a)+circle.x,circle.r*sin(a)+circle.y,r,pRobot->GetBattlefieldID()));
		
		pRobot->GetAchievementData().Add_Fire();

		return true;
	}
	return false;
}