#pragma once
#include "Bullet.h"
#include "../RobotAIstruct.h"
#include "../../Obstacle.h"

class B_Grenade :
	public Bullet
{
protected:
	double Explode_R;

public:
	B_Grenade(void);
	B_Grenade(double x,double y,double rr,int launcherIDX);
	virtual ~B_Grenade(void);
	virtual bullettypename GetType(){return type;}
	virtual bool HitObstcale(Obstacle& ob);
	virtual bool Hit(Robot &);
	virtual bool HitFlyEnd();

	void HitCircleBounce(GameEntity *);
};