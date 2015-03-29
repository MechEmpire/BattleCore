#pragma once
#include "Bullet.h"
#include "../RobotAIstruct.h"
#include "../../Obstacle.h"
class B_TrackingMissile :
	public Bullet
{
private:
	int chaseID;	//追踪的机甲下标

	double spinSpeed;	//旋转速度

public:
	B_TrackingMissile(void);
	B_TrackingMissile(double x,double y,double rr,int launcherIDX,int chaseIDX);
	virtual ~B_TrackingMissile(void);
	virtual bullettypename GetType(){return type;}
	virtual bool HitObstcale(Obstacle &);
	virtual bool Hit(Robot &);
	virtual bool HitFlyEnd();

	//矫正轨迹
	int GetChaseID();
	void AdjustDirection(Robot &);
};