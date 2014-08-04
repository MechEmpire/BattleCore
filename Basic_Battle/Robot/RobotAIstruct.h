//需要与RobotAIFactory同步

#pragma once

#define Info_MaxArsenals 2
#define Info_MaxObstacles 5
#define Info_MaxRobots 2
#define Info_MaxBullets 200



enum weapontypename
{
	WT_Cannon
	,WT_Shotgun
	,WT_RPG
	,WT_Machinegun
	,WT_Prism
	,WT_Tesla
	,WT_PlasmaTorch
	,WT_MissileLauncher
	,WT_ElectricSaw

	//二期
	,WT_GrenadeThrower
};

enum enginetypename
{
	ET_Spider
	,ET_Robotman
	,ET_AFV
	,ET_UFO
};

enum bullettypename
{
	BT_Cannonball
	,BT_ShotgunBall
	,BT_RPGBall
	,BT_MachinegunBall
	,BT_Prism_Laser
	,BT_Tesla_Lightning
	,BT_PlasmaBall
	,BT_TrackingMissile
	,BT_ElectricSaw
	
	//在这里添加游戏玩家可见(应该是武器直接发射的)类型
	,BT_Grenade
	


	//以下是功能性的类型
	
	,BT_NULL
};



struct RobotAI_Order
{
	//用于RobotAI中Execute(..)方法的对机器人下达的操作命令
	int fire;	//武器Fire(int mnplt)的操作码
	int wturn;	//武器Turn(int mnplt)的操作码
	int run;	//引擎Run(int mnplt)的操作码
	int eturn;	//引擎Turn(int mnplt)的操作码

	RobotAI_Order(){fire=0;wturn=0;run=0;eturn=0;}
};


struct RobotAI_RobotInformation
{
	//用于RobotAI中Execute(..)方法的提供给参赛AI的Robot信息
	int entityID;

	int id;		//Battlefield.pRobot的下标

	weapontypename weaponTypeName;	//武器名字
	enginetypename engineTypeName;	//引擎名字		//总感觉搞那些派生类毫无用处，最土的办法（用一个参数表示不同武器）最实用。。
	//其他属性根据这两个参数查表就行，看来DataLoader.h也要给RobotAIFactory一份

	//当前属性
	Circle circle;		//engine的圆(x,y,radium)
	double engineRotation;	//引擎角度
	double weaponRotation;	//武器角度（相对引擎）
	double vx,vy,vr;
	
	int hp;

	//这两个是不提供吗？
	int remainingAmmo;		
	int cooling;

	//bool manipulation;		//是否可操纵（还活着吗）
};

struct RobotAI_BulletInformation
{
	//用于RobotAI中Execute(..)方法的提供给参赛AI的Bullet信息
	int entityID;

	//导弹发射者的下标
	int launcherID;
	

	//temp
	bullettypename type;		//子弹类型,属性数据查表获得

	Circle circle;		//bullet的圆(x,y,radium)
	double rotation;	//引擎角度
	double vx,vy,vr;
};


struct RobotAI_ArsenalInformation
{
	Circle circle;
	int respawning_time;
};

struct RobotAI_BattlefieldInformation
{
	//2013-8-30修改

	//用于RobotAI中Execute(..)方法的提供给参赛AI的Battlefield信息

	//就使用最基本的数组了，因为是要面向参赛者的

	//Robot
	int num_robot;	//包括已经挂了的

	RobotAI_RobotInformation robotInformation[Info_MaxRobots];

	//Bullet
	int num_bullet;

	RobotAI_BulletInformation bulletInformation[Info_MaxBullets];

	//Obstacle Info
	int num_obstacle;

	Circle obstacle[Info_MaxObstacles];		//障碍物

	//Arsenal Info
	int num_arsenal;

	RobotAI_ArsenalInformation arsenal[Info_MaxArsenals];


	//boundary
	Box boundary;		//边界
};