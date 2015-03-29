//#include "../../stdafx.h"
//#include "stdafx.h"
#include "../../../stdafx.h"
#include "E_UFO.h"


E_UFO::E_UFO(enginetypename t)
{
	shapeType=S_Circle;
	LoadData(t);
	InitData();
	Init_GameEntity();
}


E_UFO::~E_UFO(void)
{
}


bool E_UFO::Run(int mnplt)
{
	//幽浮(UFO)
	//飘移悬浮式，加速度与速度完全分开
	//==0不加速，其他沿rotation方向喷气加速
	

	

	if(mnplt!=0)
	{
		double tempr=AngleToRadian(rotation);
		//这里UFO的acceleration是绝对值，不是AFV的比例
		vx+=acceleration*cos(tempr);
		vy+=acceleration*sin(tempr);

		if(maxSpeed*maxSpeed<vx*vx+vy*vy)
		{
			//2014-3-25调整
			double new_tempr=atan2(vy,vx);
			vx=maxSpeed*cos(new_tempr);
			vy=maxSpeed*sin(new_tempr);
		}

		return true;
	}
	return false;
	
}

bool E_UFO::Turn(int mnplt)
{
	//>0顺时针,<0逆时针
	if(mnplt>0)
	{
		vr=rotationSpeed;
		return true;
	}
	else if(mnplt<0)
	{
		vr=-rotationSpeed;
		return true;
	}
	else
	{
		vr=0;
		return false;
	}
}