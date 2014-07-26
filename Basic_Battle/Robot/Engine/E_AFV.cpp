//#include "../../stdafx.h"
//#include "stdafx.h"
#include "../../../stdafx.h"
#include "Engine.h"
#include "E_AFV.h"


E_AFV::E_AFV(void)
{
	shapeType=S_Circle;
	LoadData(ET_AFV);
	InitData();
	Init_GameEntity();
}


E_AFV::~E_AFV(void)
{
}


bool E_AFV::Run(int mnplt)
{
	//9-6 这里现在似乎没有速度上限？

	//装甲车（AFV）
	//最正常的游戏中的vehicle, vr正比于当前速度
	//acceleration为加速比例，(0,1)
	//m>0加速,<=0刹车
	double speed=sqrt(vx*vx+vy*vy);
	double tempr=AngleToRadian(rotation);
	if(mnplt>0)
	{
		speed*=(acceleration+1);

		if(speed>=maxSpeed)
		{
			speed=maxSpeed;
		}
		else if(speed<0.1)
		{
			speed=0.1;
		}

		vx=speed*cos(tempr);
		vy=speed*sin(tempr);



		return true;
		//pDispatcher->DispatchEvent(GetID(),pRecordManager->GetID(),R_Run,//myid)
	}
	else
	{
		//暂未考虑friction，后期版本可考虑地形差异（沙地，柏油，冰面等）
		speed*=(1-acceleration);

		if(speed<=0.1)
		{
			speed=0;
		}

		vx=speed*cos(tempr);
		vy=speed*sin(tempr);

		return false;
	}
}

bool E_AFV::Turn(int mnplt)
{
	//最正常的游戏中的vehicle, vr正比于当前速度，转向可以与加速同时操作
	//mnplt>0顺时针,<0逆时针,0不转
	double k=sqrt(vx*vx+vy*vy)/maxSpeed;
	if(mnplt>0)
	{
		vr=rotationSpeed*k;
		return true;
	}
	else if(mnplt<0)
	{
		vr=-rotationSpeed*k;
		return true;
	}
	else
	{
		vr=0;
		return false;
	}
}