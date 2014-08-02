#pragma once
#include "Bullet.h"
#include "../RobotAIstruct.h"
#include "../../Obstacle.h"
class B_Tesla_Lightning :
	public Bullet
{
protected:
	//Beam line;	//…‰œﬂ

public:
	B_Tesla_Lightning(void);
	B_Tesla_Lightning(double x,double y,double rr,int launcherIDX);
	virtual ~B_Tesla_Lightning(void);
	virtual bullettypename GetType(){return BT_Tesla_Lightning;}
	virtual bool HitObstcale(Obstacle &);
	virtual bool Hit(Robot &);
	virtual bool HitFlyEnd();
	//virtual void AdjustDirection(Robot &);
};