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
	virtual bullettypename GetType(){return BT_ElectricSaw;}
	virtual bool HitObstcale(Obstacle &);
	virtual void Hit(Robot &);
	virtual void HitFlyEnd();
	//virtual void AdjustDirection(Robot &);
};

