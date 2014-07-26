//#include "stdafx.h"
#include "../stdafx.h"
#include "struct.h"
#include "GameEntity.h"

GameEntity::GameEntity(void)
{
}


GameEntity::~GameEntity(void)
{
}


void GameEntity::Update()
{
	//onEnterFrame
	circle.x+=vx;
	circle.y+=vy;
	rotation=AnglePlus(rotation,vr);
}


/*
void GameEntity::MomentumHit(GameEntity &g1,GameEntity &g2)
{
	//简化后的两物体碰撞
	//仅是退后各自当前的速度
	//其实并非动量碰撞
	g1.SetX(g1.GetCircle().x-g1.GetVX());
	g1.SetY(g1.GetCircle().y-g1.GetVY());

	g2.SetX(g2.GetCircle().x-g2.GetVX());
	g2.SetY(g2.GetCircle().y-g2.GetVY());

	//2014_3_1
	//还应将速度反向
	g1.SetVX(-g1.GetVX());
	g1.SetVY(-g1.GetVY());

	g2.SetVX(-g2.GetVX());
	g2.SetVY(-g2.GetVY());
}

void GameEntity::MomentumHit_Half(GameEntity &g1,GameEntity &g2)
{
	g1.SetX(g1.GetCircle().x-g1.GetVX());
	g1.SetY(g1.GetCircle().y-g1.GetVY());

	//2014_3_1
	//还应将速度反向，不然就会像飞碟卡住
	g1.SetVX(-g1.GetVX());
	g1.SetVY(-g1.GetVY());

	//g2固定
	//g2.SetX(g2.GetCircle().x-g2.GetVX());
	//g2.SetY(g2.GetCircle().y-g2.GetVY());
}
*/


void GameEntity::MomentumHit(GameEntity &g1,GameEntity &g2)
{
	//只适用于两个圆

	//参考flash

	


	//确定已经碰撞后
	double vx1,vy1,vr1;
	double vx2,vy2,vr2;

	//2014-3-15
	double vx1o,vy1o,vr1o;
	double vx2o,vy2o,vr2o;
	g1.GetVelocity(vx1o,vy1o,vr1o);
	g2.GetVelocity(vx2o,vy2o,vr2o);
	//用于粗暴调整位置


	g1.GetVelocity(vx1,vy1,vr1);
	g2.GetVelocity(vx2,vy2,vr2);




	double r1=g1.GetCircle().r,r2=g2.GetCircle().r;

	double dx=g2.GetCircle().x-g1.GetCircle().x;
	double dy=g2.GetCircle().y-g1.GetCircle().y;
	double dist=sqrt(dx*dx+dy*dy);



	double angle=atan2(dy,dx);
	double s=sin(angle);
	double c=cos(angle);

	


	Point pos1;
	pos1.x=0;
	pos1.y=0;
	//g2变成g1坐标系
	Point pos2=myRotate(dx,dy,s,c,true);


	//g1速度调整
	Point vel1=myRotate(vx1,vy1,s,c,true);
	//g2速度调整
	Point vel2=myRotate(vx2,vy2,s,c,true);


	//这样只有vx起作用，vy法向速度不用考虑


	
	//碰撞反应
	double vxTotal=vel1.x-vel2.x;

	//考虑质量的做法
	//vel1.x=((mass1-mass2)*vel1.x+2*mass2*vel2.x)/(mass1+mass2);
	//vel2.x=vxTotal+vel1.x;

	//我质量都相等
	vel1.x=vel2.x;
	vel2.x=vxTotal+vel1.x;
	

	

	//更新位置，防止吸住
	//3_11,防除数为零
	double absV=abs(vel1.x)+abs(vel2.x);
	if(absV==0)
	{
		double overlap=(r1+r2)-abs(pos1.x-pos2.x);	//如果我所有Robot（Bullet不发生动量碰撞）半径都一样又可简化

		double tmp=pos1.x>pos2.x ? 1 : -1;
		pos1.x+=tmp*overlap;
		pos2.x+=-tmp*overlap;
	}
	else
	{
		double overlap=(r1+r2)-abs(pos1.x-pos2.x);	//如果我所有Robot（Bullet不发生动量碰撞）半径都一样又可简化
		pos1.x+=vel1.x/absV*overlap;
		pos2.x+=vel2.x/absV*overlap;
	}



	//旋转回去
	Point pos1F=myRotate(pos1.x,pos1.y,s,c,false);
	Point pos2F=myRotate(pos2.x,pos2.y,s,c,false);


	/*
	//调整到屏幕坐标系
	g2.SetX(g1.GetCircle().x+pos2F.x);
	g2.SetY(g1.GetCircle().y+pos2F.y);
	g1.SetX(g1.GetCircle().x+pos1F.x);
	g1.SetY(g1.GetCircle().y+pos1F.y);
	*/
	//2014-3-15粗暴调整位置
	g2.SetX(g2.GetCircle().x-vx2o);
	g2.SetY(g2.GetCircle().y-vy2o);
	g1.SetX(g1.GetCircle().x-vx1o);
	g1.SetY(g1.GetCircle().y-vy1o);




	//把速度旋转回去
	Point vel1F=myRotate(vel1.x,vel1.y,s,c,false);
	Point vel2F=myRotate(vel2.x,vel2.y,s,c,false);







	//这里直接设定vx,vy会有问题(对蜘蛛和毁灭者)
	//因为操纵vxvy时是直接设定值而非叠加

	g1.SetVX(vel1F.x);
	g1.SetVY(vel1F.y);
	g2.SetVX(vel2F.x);
	g2.SetVY(vel2F.y);
}

void GameEntity::MomentumHit_Half(GameEntity &g1,GameEntity &g2)
{
	//只适用于两个圆

	//g2固定物体,只要反一下相对坐标系中g1的速度
	//参考flash

	//确定已经碰撞后
	double vx1,vy1,vr1;
	

	g1.GetVelocity(vx1,vy1,vr1);

	double r1=g1.GetCircle().r,r2=g2.GetCircle().r;
	double dx=g2.GetCircle().x-g1.GetCircle().x;
	double dy=g2.GetCircle().y-g1.GetCircle().y;
	double dist=sqrt(dx*dx+dy*dy);






	double angle=atan2(dy,dx);
	double s=sin(angle);
	double c=cos(angle);

	Point pos1;
	pos1.x=0;
	pos1.y=0;
	//g2变成g1坐标系
	Point pos2=myRotate(dx,dy,s,c,true);


	//g1速度调整
	Point vel1=myRotate(vx1,vy1,s,c,true);
	


	//这样只有vx起作用，vy法向速度不用考虑


	//我质量都相等
	vel1.x=-vel1.x;

	/*
	//更新位置，防止吸住
	double absV=abs(vel1.x);
	double overlap=(r1+r2)-abs(pos1.x-pos2.x);	//如果我所有Robot（Bullet不发生动量碰撞）半径都一样又可简化
	pos1.x+=vel1.x/absV*overlap;
	*/
	double tmp=vel1.x>0 ? 1 : -1;		//防vel1.x=0的情况

	double overlap=(r1+r2)-abs(pos1.x-pos2.x);

	pos1.x+=tmp*overlap;


	//旋转回去
	Point pos1F=myRotate(pos1.x,pos1.y,s,c,false);
	

	//调整到屏幕坐标系
	
	g1.SetX(g1.GetCircle().x+pos1F.x);
	g1.SetY(g1.GetCircle().y+pos1F.y);

	//把速度旋转回去
	Point vel1F=myRotate(vel1.x,vel1.y,s,c,false);
	

	g1.SetVX(vel1F.x);
	g1.SetVY(vel1F.y);

}



/*
void GameEntity::HandleEvent(events msg, void* extraInfo)
{

}
*/


void GameEntity::Init_GameEntity()
{
	vx=0;
	vy=0;
	vr=0;
	rotation=0;

	//shapeType=S_Circle;
}




bool GameEntity::HitTest(GameEntity & ge)
{
	if(shapeType==S_Circle)
	{
		if(ge.GetShape()==S_Circle)
		{
			return HitTestCircles(GetCircle(),ge.GetCircle());
		}
		else if(ge.GetShape()==S_Box)
		{
			//这个暂时没做
			return false;
		}
		else if(ge.GetShape()==S_Beam)
		{
			return HitTestBeamCircle(ge.GetBeam(),circle);
		}
	}
	else if(shapeType==S_Box)
	{
		if(ge.GetShape()==S_Circle)
		{
			//这个暂时没做 circle box
			return false;
		}
		else if(ge.GetShape()==S_Box)
		{
			//这个暂时没做 box box
			return false;
		}
		else if(ge.GetShape()==S_Beam)
		{
			return HitTestBeamBox(ge.GetBeam(),box);
		}
	}
	else if(shapeType==S_Beam)
	{
		if(ge.GetShape()==S_Circle)
		{
			//beam circle
			return HitTestBeamCircle(beam,ge.GetCircle());
		}
		else if(ge.GetShape()==S_Box)
		{
			return HitTestBeamBox(beam,ge.GetBox());
		}
		else if(ge.GetShape()==S_Beam)
		{
			//这个暂时没做 beam beam
			return false;
		}
	}


	return false;
}