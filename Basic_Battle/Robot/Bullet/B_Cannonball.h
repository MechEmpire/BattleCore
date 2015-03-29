#pragma once
#include "Bullet.h"
#include "../RobotAIstruct.h"
#include "../../Obstacle.h"

class B_Cannonball :
	public Bullet
{
private:
	//bullettypename type;
public:
	B_Cannonball(void);
	B_Cannonball(double x,double y,double rr,int launcherIDX,bullettypename t);
	virtual ~B_Cannonball(void);
	virtual bullettypename GetType(){return type;}
	virtual bool HitObstcale(Obstacle &);
	virtual bool Hit(Robot &);
	virtual bool HitFlyEnd();
};

