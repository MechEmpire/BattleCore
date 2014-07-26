//#include "../../stdafx.h"
//#include "stdafx.h"
#include "../../../stdafx.h"
#include "W_Shotgun.h"


int W_Shotgun::burst=pDataLoader->GetGameData()->burst_Shotgun;
double W_Shotgun::gapRotation=pDataLoader->GetGameData()->gapRotation_Shotgun;

W_Shotgun::W_Shotgun(void)
{
	LoadData(WT_Shotgun);
	//burst=pDataLoader->GetGameData()->burst_Shotgun;
	//gapRotation=pDataLoader->GetGameData()->gapRotation_Shotgun;
	burst=pDataLoader->GetGameData()->burst_Shotgun;
	gapRotation=pDataLoader->GetGameData()->gapRotation_Shotgun;

	InitData();
	Init_GameEntity();
}


W_Shotgun::~W_Shotgun(void)
{
}


bool W_Shotgun::Fire(int mnplt)
{
	if(General_Fire(mnplt))
	{
		double p=inaccuracy*(Random0_1()-0.5);//偏移角度
		//double r=AnglePlus(AnglePlus(rotation,engineRotation),p);//角度
		double r=AnglePlus(rotation,p);
		double a=AngleToRadian(r);//弧度

		double b,c;
		int i;
		for(i=0;i<burst;i++)
		{
			//发射burst次
			b=(double)r+gapRotation*(int)(i-burst/2);//此式正确性要实验
			c=AngleToRadian(b);
			//b=(double)a+AngleToRadian(gapRotation)*(int)(i-burst/2);	//此式正确性要实验
			pDispatcher->DispatchEvent(ID,pBattlefield->GetID(),
				Add_Bullet,
				new B_ShotgunBall(circle.r*cos(c)+circle.x,circle.r*sin(c)+circle.y,b,pRobot->GetID()));
		}

		pRobot->GetAchievementData().Add_Fire();
		return true;
	}
	return false;
}