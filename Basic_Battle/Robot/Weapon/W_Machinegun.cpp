//#include "../../stdafx.h"
//#include "stdafx.h"
#include "../../../stdafx.h"
#include "W_Machinegun.h"


W_Machinegun::W_Machinegun(void)
{
	LoadData(WT_Machinegun);
	InitData();
	Init_GameEntity();
}


W_Machinegun::~W_Machinegun(void)
{
}


bool W_Machinegun::Fire(int mnplt)
{
	if(General_Fire(mnplt))
	{
		double p=inaccuracy*(Random0_1()-0.5);//Æ«ÒÆ½Ç¶È
		//double r=AnglePlus(AnglePlus(rotation,engineRotation),p);//½Ç¶È
		double r=AnglePlus(rotation,p);
		double a=AngleToRadian(r);//»¡¶È

		pDispatcher->DispatchEvent(ID,pBattlefield->GetID(),
			Add_Bullet,
			new B_MachinegunBall(circle.r*cos(a)+circle.x,circle.r*sin(a)+circle.y,r,pRobot->GetID()));
		
		pRobot->GetAchievementData().Add_Fire();
		return true;
	}
	return false;
}