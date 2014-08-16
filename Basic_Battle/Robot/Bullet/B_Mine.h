#pragma once
#include "Bullet.h"
#include "../RobotAIstruct.h"
#include "../../Obstacle.h"

class B_Mine :
	public Bullet
{
protected:
	double Explode_R;
public:
	B_Mine(void);
	B_Mine(double x,double y,double rr,int launcherIDX);
	virtual ~B_Mine(void);
	virtual bullettypename GetType(){return BT_Mine;}
	virtual bool HitObstcale(Obstacle &);
	virtual bool Hit(Robot &);
	virtual bool HitFlyEnd();

	void Explode();
};