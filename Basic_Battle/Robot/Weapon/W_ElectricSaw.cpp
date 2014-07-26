//#include "../../stdafx.h"
//#include "stdafx.h"
#include "../../../stdafx.h"
#include "W_ElectricSaw.h"

W_ElectricSaw::W_ElectricSaw(void)
{
	LoadData(WT_ElectricSaw);
	InitData();
	Init_GameEntity();
}


W_ElectricSaw::~W_ElectricSaw(void)
{
}



bool W_ElectricSaw::Fire(int mnplt)
{
	//TODO:所有武器Fire的随机不准确性

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
			new B_ElectricSaw(circle.r*cos(a)+circle.x,circle.r*sin(a)+circle.y,r,pRobot->GetID()));
		
		pRobot->GetAchievementData().Add_Fire();
		return true;
	}
	return false;
}