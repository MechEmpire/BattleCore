//#include "stdafx.h"
#include "../../../stdafx.h"
#include "B_PlasmaBall.h"
#include "../../DataLoader.h"
#include "../../Battlefield.h"



B_PlasmaBall::B_PlasmaBall(void)
{
	
}

B_PlasmaBall::B_PlasmaBall(double x,double y,double rr,int launcherIDX)
{
	left_bounce_time=pDataLoader->GetGameData()->bounce_time;

	shapeType=S_Circle;
	LoadData(BT_PlasmaBall);

	GeneralInit(x,y,rr,launcherIDX);

}


B_PlasmaBall::~B_PlasmaBall(void)
{
}



bool B_PlasmaBall::HitObstcale(Obstacle & ob)
{

	//等离子反弹
	if(left_bounce_time>0)
	{
		left_bounce_time--;
		if(ob.GetCircle().r<=0.01)
		{
			//战场边界
			//这里编码又有点紧耦合了
			if(circle.x<=pBattlefield->Get_B_Left())
			{
				//简化的矫正方案
				circle.x=pBattlefield->Get_B_Left();
				vx=-vx;
			}
			else if(circle.x>=pBattlefield->Get_B_Right())
			{
				circle.x=pBattlefield->Get_B_Right();
				vx=-vx;
			}
			else if(circle.y<=pBattlefield->Get_B_Up())
			{
				circle.y=pBattlefield->Get_B_Up();
				vy=-vy;
			}
			else if(circle.y>=pBattlefield->Get_B_Down())
			{
				circle.y=pBattlefield->Get_B_Down();
				vy=-vy;
			}
		}
		else
		{
			//9-3 这里现在还有bug
			//障碍

			//先位置矫正，利用atan2获取角度选择实际的切点
			double dx=circle.x-ob.GetCircle().x;
			double dy=circle.y-ob.GetCircle().y;

			double rar=atan2(dy,dx);


			circle.x=ob.GetCircle().r*cos(rar)+ob.GetCircle().x;
			circle.y=ob.GetCircle().r*sin(rar)+ob.GetCircle().y;

			//vx,vy转化为切向速度vp，法向速度vn
			//反向法向速度vn

			//9-3 这里有问题(旋转的方向)
			//rar+=PI/2;		//切线角度
			if(rar>=0 && rar<=PI)
			{
				rar=rar-PI/2;
			}
			else if(rar<=0 && rar>=-PI)
			{
				rar=rar+PI/2;
			}


			//dx=circle.x-ob.GetCircle().x;
			//dy=circle.y-ob.GetCircle().y;
			double c=cos(rar);	//cos
			double s=sin(rar);	//sin

			//旋转坐标系后的坐标和速度
			//double x2=c*dx+s*dy;
			//double y2=c*dy-s*dx;
			double vx2=c*vx+s*vy;
			double vy2=c*vy-s*vx;

			//反转法向速度（vy）
			vy2=-vy2;
			vx=c*vx2-s*vy2;
			vy=c*vy2+s*vx2;

		}
		//没消失

		//发送一个反弹用的hitinfo

		return false;
	}

	return true;

}

bool B_PlasmaBall::Hit(Robot& robot)
{
	return GeneralHit(robot);
}

bool B_PlasmaBall::HitFlyEnd()
{
	return false;
}

