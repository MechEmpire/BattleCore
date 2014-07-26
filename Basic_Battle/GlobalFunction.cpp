//#include "stdafx.h"
#include "../stdafx.h"
#include "struct.h"

//last update: 2013-10-30	optimize Circle的碰撞检测


Point myRotate(double x,double y,double s,double c,bool re)
{
	Point result;
	if(re)
	{
		result.x=x*c+y*s;
		result.y=y*c-x*s;
	}
	else
	{
		result.x=x*c-y*s;
		result.y=y*c+x*s;
	}
	return result;
}




double AngleAdjust(double &c)
{
	while(c>180)
	{
		c-=360;
	}
	while(c<=-180)
	{
		c+=360;
	}
	return c;
}

double AnglePlus(double a,double b)
{
	//角度相加减
	double c=a+b;
	AngleAdjust(c);
	return c;
}

double AngleToRadian(double angle)
{
	//角度转弧度
	return angle/180*PI;
}

double RadianToAngle(double radian)
{
	return radian/PI*180;
}


bool HitTestCirclePoint(const Circle &c,const double &x,const double &y)
{
	//返回点(x,y)是否在圆c内
	//newly added 2013-10-30
	double dx=c.x-x,	dy=c.y-y;

	if(abs(dx)>c.r || abs(dy)>c.r)
	{
		return false;
	}

	double dis2=dx*dx+dy*dy;
	return (c.r*c.r>dis2);
}


bool HitTestCircles(const Circle &c1, const Circle &c2)
{
	//返回两圆是否相交，相切算作相交

	//2013-10-30优化
	//标准测试前先做粗略测试
	
	double xx=c1.x-c2.x,	yy=c1.y-c2.y;
	double rr=c1.r+c2.r;

	if(abs(xx)>rr || abs(yy)>rr)
	{
		return false;
	}

	double dis2=xx*xx+yy*yy;
	
	return (rr*rr>=dis2);
}

bool HitTestBeamCircle(const Beam &b,const Circle &c)
{
	/*
	//2014_3_1 改 原来是b.x>c.y
	if(b.x>c.x && b.rotation>=-90 && b.rotation<=90)
	{
		//方向反
		return false;
	}
	else if(b.x<c.x && (b.rotation<=-90 || b.rotation>=90))
	{
		//方向反
		return false;
	}
	*/
	double br=AngleToRadian(b.rotation);
	double k=tan(br);
	double g=k*c.x-c.y-k*b.x+b.y;	//直线一般式的值
	double d2=g*g/(k*k+1);			//圆心到直线距离平方
	//return (c.r*c.r>=d2);
	if(c.r*c.r>=d2)
	{
		//直线与圆已经相交，下面判断方向
		double dy=c.y-b.y;
		//double dx=c.x-b.x;
		double ss=sin(br);
		
		//2014-3-19 修复
		if(abs(ss)>0.707)	//root2/2  45o
		{
			//2014-3-19
			//问题在这里！！！！！
			//k->0时这两个符号可能相反但是击中目标的
			if((ss>0 && dy>0)||(ss<0 && dy<0))
			{
				return true;
			}
		}
		else
		{
			double dx=c.x-b.x;
			double cc=cos(br);
			if((cc>0 && dx>0)||(cc<0 && dx<0))
			{
				return true;
			}
		}
	}
	return false;
}

bool HitTestBeamBox(const Beam &bm,const Box &bx)
{
	//不是很完善，边界和y=m,x=n
	double k=tan(AngleToRadian(bm.rotation));
	double x1,y1,x2,y2;
	if(k>0)
	{
		x1=bx.x+bx.width/2;
		y1=bx.y-bx.height/2;

		x2=bx.x-bx.width/2;
		y2=bx.y+bx.height/2;
	}
	else if(k<0)
	{
		x1=bx.x+bx.width/2;
		y1=bx.y+bx.height/2;

		x2=bx.x-bx.width/2;
		y2=bx.y-bx.height/2;
	}
	else
	{
		//k==0	y=m
	}

	double v1=k*x1-y1-k*bm.x+bm.y;
	double v2=k*x2-y2-k*bm.x+bm.y;

	//贴边不算相交?
	if((v1>0 && v2<0) ||(v1<0 && v2>0))
	{
		return true;
	}


	return false;

}


Point GetHitPoint(Beam b,Circle c)
{
	Point p;
	p.x=0;
	p.y=0;

	Vector2D co;		//圆心
	co.x=c.x;
	co.y=c.y;

	Vector2D bb;		//射线起点
	bb.x=b.x;
	bb.y=b.y;

	//2014-3-17
	//当年太弱，明显用向量啊
	Vector2D bs_to_c;	//射线起点到圆心
	Vector2D bs;		//射线到垂足

	bs_to_c.x=c.x-b.x;
	bs_to_c.y=c.y-b.y;


	double brr=AngleToRadian(b.rotation);
	double k=tan(brr);//直线斜率
	double g=k*c.x-c.y-k*b.x+b.y;	//直线一般式的值
	double d_2=g*g/(k*k+1);			//圆心到直线距离平方

	


	double dbc_2=bs_to_c.LengthSq();	//圆心到射线起点距离平方
	double d=sqrt(dbc_2-d_2);			//射线起点到垂足长度


	bs.x=cos(brr)*d;
	bs.y=sin(brr)*d;



	Vector2D c_to_v=bs-bs_to_c;		//圆心到垂足

	
	double gap=sqrt(c.r*c.r-d_2);		//射线方向滑动距离

	Vector2D b_slide=bs.GetReverse();		//与射线平行反向的滑动向量
	b_slide.Normalize();
	b_slide*=gap;

	Vector2D hit_point=co+c_to_v+b_slide;

	p.x=hit_point.x;
	p.y=hit_point.y;

	/*
	//TODO..
	//已经确保二者相交
	//找到b与c的交点

	//暂未考虑rotation=90的情况
	double brr=AngleToRadian(b.rotation);
	double k=tan(brr);//直线斜率
	double g=k*c.x-c.y-k*b.x+b.y;	//直线一般式的值
	double d=abs(g)/sqrt(k*k+1);			//圆心到直线距离
	
	double rr=AnglePlus(b.rotation,90);		//垂线角度(由圆心发出可能反向)
	//问题可能在这，方向可能反了
	


	double rrr=AngleToRadian(rr);
	
	double gap=sqrt(c.r*c.r-d*d);	//射线上滑动距离/2

	double sign;
	if(g>0)
	{
		//y系数为负，g>0圆心在直线下方，往上移
		sign=1;
	}
	else
	{
		sign=-1;
	}


	//垂足坐标
	double xc=c.x+sign*d*cos(rrr);
	double yc=c.y+sign*d*sin(rrr);

	//double x1=xc+gap*cos(brr);
	//double x2=xc-gap*cos(brr);

	if(b.x<xc)
	{
		if(cos(brr)>0)
		{
			p.x=xc-gap*cos(brr);
			p.y=yc-gap*sin(brr);
		}
		else
		{
			p.x=xc+gap*cos(brr);
			p.y=yc+gap*sin(brr);
		}
	}
	else
	{
		if(cos(brr)>0)
		{
			p.x=xc+gap*cos(brr);
			p.y=yc+gap*sin(brr);
		}
		else
		{
			p.x=xc-gap*cos(brr);
			p.y=yc-gap*sin(brr);
		}
	}

	//1.首先找c的圆心作b的垂线与b的交点
	//2.勾股定理算出另一直角边长度
	*/

	return p;
}











void SetSeed()
{
	//每次程序运行前撒种子
	srand( (unsigned)time( 0 )+7); 
}

double Random0_1(){
	//产生0-1的随机数的函数,//zz种子
	int temp;
	double r;

	//其实种子分配每一次运行工程撒一次就行了
	temp=rand()%1000;
	r=(double)temp/1000;
	return r;
}

int Random(int minv,int maxv)
{
	//产生[minv,maxv]之间整数的随机函数

	//2014-1-22
	//可以考虑用蒙特卡洛方法
	if(maxv<minv)
	{
		int temp=maxv;
		maxv=minv;
		minv=temp;
	}

	double r=Random0_1();
	int num_gap=maxv-minv+1;
	double gap=1/(double)num_gap;
	int i;
	double current=gap;

	for(i=0;i<num_gap;i++)
	{
		if(current>r)
		{
			return minv+i;
		}
		current+=gap;
	}
	
	assert("随机数出错了" && 0);
	
	return 0;
	//return rand()%(maxv-minv+1)+minv;

	
}