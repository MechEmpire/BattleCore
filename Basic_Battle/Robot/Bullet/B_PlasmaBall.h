#pragma once
#include "Bullet.h"
#include "../RobotAIstruct.h"
#include "../../Obstacle.h"

class B_PlasmaBall :
	public Bullet
{
protected:
	int left_bounce_time;		//Ê£Óà·´µ¯´ÎÊý

public:
	B_PlasmaBall(void);
	B_PlasmaBall(double x,double y,double rr,int launcherIDX);
	virtual ~B_PlasmaBall(void);
	virtual bullettypename GetType(){return BT_PlasmaBall;}
	virtual bool HitObstcale(Obstacle& ob);
	virtual void Hit(Robot &);
	virtual void AdjustDirection(Robot &);
};