//#include "stdafx.h"
#include "../../../stdafx.h"
#include "B_Grenade.h"
#include "../../DataLoader.h"
#include "../../Battlefield.h"



B_Grenade::B_Grenade(void)
{
	
}

B_Grenade::B_Grenade(double x,double y,double rr,int launcherIDX)
{
	Explode_R=pDataLoader->GetGameData()->explodeR_Grenade;

	shapeType=S_Circle;
	LoadData(BT_Grenade);

	GeneralInit(x,y,rr,launcherIDX);

}


B_Grenade::~B_Grenade(void)
{
}

void B_Grenade::HitCircleBounce(GameEntity * entity)
{
	//先位置矫正，利用atan2获取角度选择实际的切点
		double dx=circle.x-(entity->GetCircle().x);
		double dy=circle.y-(entity->GetCircle().y);

		double rar=atan2(dy,dx);


		circle.x=(entity->GetCircle().r)*cos(rar)+(entity->GetCircle().x);
		circle.y=(entity->GetCircle().r)*sin(rar)+(entity->GetCircle().y);

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

bool B_Grenade::HitObstcale(Obstacle & ob)
{
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
		HitCircleBounce(&ob);
	}
	//没消失

	return false;

}

bool B_Grenade::Hit(Robot& robot)
{
	//反弹，不爆炸
	HitCircleBounce(&robot.GetEngine());
	return false;
}

bool B_Grenade::HitFlyEnd()
{
	//产生范围爆炸
	Circle* expld=new Circle;
	expld->x=circle.x;
	expld->y=circle.y;
	expld->r=Explode_R;

	pDispatcher->DispatchEvent(ID,pBattlefield->GetID(),
		Explode_Grenade,expld);
	//Dispatch_Remove_Event();删除在Battlefield.cpp里做

	//TODO:范围伤害的统计计算？
	Robot* r=pBattlefield->GetRobotPointer(launcherID);
	r->GetAchievementData().Add_hit();
	r->GetAchievementData().Add_output(damage);

	return true;
}

