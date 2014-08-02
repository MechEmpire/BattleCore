#pragma once
#include "Bullet.h"
#include "../RobotAIstruct.h"
#include "../../Obstacle.h"
class B_RPGBall :
	public Bullet
{
protected:
	double Explode_R;
	
	double acceleration_rpgball;	//火箭弹加速度

public:
	B_RPGBall(void);
	B_RPGBall(double x,double y,double rr,int launcherIDX);
	virtual ~B_RPGBall(void);
	virtual bullettypename GetType(){return BT_RPGBall;}
	virtual bool Hit(Robot &);		//火箭弹的碰撞后效果特殊
	virtual bool HitObstcale(Obstacle &);
	virtual bool HitFlyEnd();
	//virtual void AdjustDirection(Robot &);

	virtual void Update();	//火箭弹加速行进，覆盖GameEntity的
};

