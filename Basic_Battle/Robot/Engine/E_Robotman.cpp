//#include "../../stdafx.h"
//#include "stdafx.h"
#include "../../../stdafx.h"
#include "E_Robotman.h"

E_Robotman::E_Robotman(void)
{
	shapeType=S_Circle;
	LoadData(ET_Robotman);
	InitData();
	Init_GameEntity();
}


E_Robotman::~E_Robotman(void)
{
}


//最好的办法是这种东西用脚本写，现在就急功近利了。。。
bool E_Robotman::Run(int mnplt)
{
	//人形机甲(Robotman)没有加速过程直接满速前进
	//传入参数mnplt>0全速前进,mnplt<0全速后退,mnplt=0立即停止
	double tempr;
	if(mnplt>0)
	{
		tempr=AngleToRadian(rotation);
		vr=0;
		vx=maxSpeed*cos(tempr);
		vy=maxSpeed*sin(tempr);
		return true;
	}
	else if(mnplt<0)
	{
		tempr=AngleToRadian(rotation);
		vr=0;
		vx=-maxSpeed*cos(tempr);
		vy=-maxSpeed*sin(tempr);
		return true;
	}
	else
	{
		//mnplt==0
		vx=0;
		vy=0;
		return false;
	}
}

bool E_Robotman::Turn(int mnplt)
{
	//人形机甲(Robotman)只能在站定时转动
	//mnplt>0顺时针,mnplt<0逆时针,==0停止转动
	if(mnplt>0)
	{
		vx=0;
		vy=0;
		vr=rotationSpeed;
		return true;
	}
	else if(mnplt<0)
	{
		vx=0;
		vy=0;
		vr=-rotationSpeed;
		return true;
	}
	else
	{
		//mnplt==0
		//vx=0;
		//vy=0;
		vr=0;
		return false;
	}
}