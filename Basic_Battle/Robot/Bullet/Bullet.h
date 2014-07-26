#pragma once
#include "../Robot.h"
#include "../../GameEntity.h"
#include "../../struct.h"
#include "../RobotAIstruct.h"
class Bullet :
	public GameEntity, public BulletData
{
protected:
	//静态属性

	int launcherID;		//发射者Robot的ID,改过了（原来是Weapon的,这样换武器后有小BUG）


	/*
	bullettypename type;

	string name;		//子弹的名字
	double speed;		//子弹飞行速度
	int damage;			//威力		
	*/

public:
	Bullet(void);
	Bullet(double x,double y,double rr);
	virtual ~Bullet(void);


	void GeneralInit(double x,double y,double rr,int launcherIDX);

	//Update延续GameEntity的
	virtual bullettypename GetType()=0;


	virtual void Hit(Robot &)=0;		//如果要做成就系统说什么也要引入事件机制！！！
	virtual bool HitObstcale(Obstacle &)=0;

	void Dispatch_Remove_Event();

	int GetLauncher(){return launcherID;}

	void LoadData(bullettypename);

	virtual void HandleEvent(events msg,void* extraInfo){};

	virtual void AdjustDirection(Robot &)=0;
};

