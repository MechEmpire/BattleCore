//这个也要与RobotAIFactory进行统一更新

//update: 2013-10-30

#pragma once
using namespace std;
#include <cmath>
#include <cstdlib>
#include <ctime>
#define PI 3.1415926535898



enum events{Add_Bullet,Remove_Bullet,Explode,Prism_Laser,Tesla_Lightning,
					Round_Start,Round_End,Battle_Start,Battle_End,

			//Record related
			R_RobotInfo,R_BulletInfo,//此二事件已无用
			////////////
			R_Fire,R_WeaponTurn,R_Run,R_EngineTurn,
			R_HitInfo

			};


enum shapes{S_Circle,S_Box,S_Beam};





//采用和flash相同的坐标系

//一些通用的类啥的

struct Point
{
	double x;
	double y;
};

struct Circle
{
	double x;
	double y;
	double r;
};

struct Box
{
	//矩形，中心为(x,y)
	double x;
	double y;
	double width;
	double height;
};


struct Segment
{
	//线段，方便as3绘制？
	double x1,y1;
	double x2,y2;
};

struct Beam
{
	//射线
	//起点(x,y)
	double x;
	double y;
	double rotation;	//角度

	//终点
	double ex,ey;
};


extern Point myRotate(double,double,double,double,bool);
extern double AngleAdjust(double &);
extern double AnglePlus(double,double);
extern double AngleToRadian(double);
extern double RadianToAngle(double);
extern bool HitTestCirclePoint(const Circle &,const double &x,const double &y);
extern bool HitTestCircles(const Circle &, const Circle &);
extern bool HitTestBeamCircle(const Beam &,const Circle &);
extern bool HitTestBeamBox(const Beam &,const Box &);
extern Point GetHitPoint(Beam,Circle);
extern void SetSeed();
extern double Random0_1();
extern int Random(int,int);