#pragma once
#include "Bullet.h"
#include "../RobotAIstruct.h"
#include "../../Obstacle.h"

class B_ElectricSaw :
	public Bullet
{
public:
	B_ElectricSaw(void);
	B_ElectricSaw(double x,double y,double rr,int launcherIDX);
	virtual ~B_ElectricSaw(void);
	virtual bullettypename GetType(){return type;}
	virtual bool HitObstcale(Obstacle &);
	virtual bool Hit(Robot &);
	virtual bool HitFlyEnd();
	//virtual void AdjustDirection(Robot &);
};

