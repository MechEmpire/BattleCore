#pragma once
#include "Bullet.h"
#include "../RobotAIstruct.h"
#include "../../Obstacle.h"

//刻画一条线段的必备要素？
//关键是线段终点的获得

class B_Prism_Laser :
	public Bullet
{
protected:
	//Beam line;	//射线

public:
	B_Prism_Laser(void);
	B_Prism_Laser(double x,double y,double rr,int launcherIDX);
	virtual ~B_Prism_Laser(void);
	virtual bullettypename GetType(){return type;}
	virtual bool HitObstcale(Obstacle &);
	virtual bool Hit(Robot &);
	virtual bool HitFlyEnd();
	//virtual void AdjustDirection(Robot &);
};

