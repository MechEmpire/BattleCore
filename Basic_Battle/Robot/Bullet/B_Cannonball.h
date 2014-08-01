#pragma once
#include "Bullet.h"
#include "../RobotAIstruct.h"
#include "../../Obstacle.h"

class B_Cannonball :
	public Bullet
{
public:
	B_Cannonball(void);
	B_Cannonball(double x,double y,double rr,int launcherIDX);
	virtual ~B_Cannonball(void);
	virtual bullettypename GetType(){return BT_Cannonball;}
	virtual bool HitObstcale(Obstacle &);
	virtual void Hit(Robot &);
	//virtual void AdjustDirection(Robot &);
};

