#pragma once
#include "Bullet.h"
#include "../RobotAIstruct.h"
#include "../../Obstacle.h"

class B_TinyBall :
	public Bullet
{
public:
	B_TinyBall(void);
	B_TinyBall(double x,double y,double rr,int launcherIDX);
	virtual ~B_TinyBall(void);
	virtual bullettypename GetType(){return type;}
	virtual bool HitObstcale(Obstacle &);
	virtual bool Hit(Robot &);
	virtual bool HitFlyEnd();
};
