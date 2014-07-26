#pragma once
#include "Bullet.h"
#include "../RobotAIstruct.h"
#include "../../Obstacle.h"
class B_MachinegunBall :
	public Bullet
{
public:
	B_MachinegunBall(void);
	B_MachinegunBall(double x,double y,double rr,int launcherIDX);
	virtual ~B_MachinegunBall(void);
	virtual bullettypename GetType(){return BT_MachinegunBall;}
	virtual bool HitObstcale(Obstacle &);
	virtual void Hit(Robot &);
	virtual void AdjustDirection(Robot &);
};

