//#include "../../stdafx.h"
//#include "stdafx.h"
#include "../../../stdafx.h"
#include "W_Prism.h"


W_Prism::W_Prism(void)
{
	LoadData(WT_Prism);
	InitData();
	Init_GameEntity();
}


W_Prism::~W_Prism(void)
{
}

bool W_Prism::Fire(int mnplt)
{
	if(General_Fire(mnplt))
	{
		//直线在全局坐标系下的
		double p=inaccuracy*(Random0_1()-0.5);//偏移角度
		//double r=AnglePlus(AnglePlus(rotation,engineRotation),p);//角度
		double r=AnglePlus(rotation,p);
		double a=AngleToRadian(r);//弧度

		pDispatcher->DispatchEvent(ID,pBattlefield->GetID(),
			Add_Bullet,
			new B_Prism_Laser(circle.r*cos(a)+circle.x,circle.r*sin(a)+circle.y,r,pRobot->GetBattlefieldID()));

		pRobot->GetAchievementData().Add_Fire();
		return true;
	}
	return false;
}