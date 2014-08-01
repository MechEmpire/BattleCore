#pragma once
#include "../Robot.h"
#include "../../GameEntity.h"
#include "../../struct.h"
#include "../RobotAIstruct.h"
class Bullet :
	public GameEntity, public BulletData
{
protected:

	//2014/8/1战场中pRobot下标
	int launcherID;		

	int remainingFlyTime;		//当前剩余飞行时间
	

public:
	Bullet(void);
	Bullet(double x,double y,double rr);
	virtual ~Bullet(void);


	void GeneralInit(double x,double y,double rr,int launcherIDX);

	//Update延续GameEntity的
	virtual bullettypename GetType()=0;


	virtual void Hit(Robot &)=0;
	virtual bool HitObstcale(Obstacle &)=0;
	virtual void HitFlyEnd()=0;


	void GeneralHit(Robot &);
	//返回是否消失
	bool GeneralHitObstcale(Obstacle &){return true;}

	//返回是否飞行时间耗尽
	bool UpdateFlyTime(){remainingFlyTime--;return remainingFlyTime<=0;}


	void Dispatch_Remove_Event();

	int GetLauncher(){return launcherID;}

	void LoadData(bullettypename);

	virtual void HandleEvent(events msg,void* extraInfo){};

	//virtual void AdjustDirection(Robot &)=0;
};

