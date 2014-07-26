#pragma once
#include "Basic_Battle\Robot\RobotAIstruct.h"

struct Record_RobotInformation
{
	//用于RobotAI中Execute(..)方法的提供给参赛AI的Robot信息
	int id;		//Battlefield.pRobot的下标

	int entityID;	//用于MovieClip的唯一标识

	int style_Weapon;		//炮塔样式
	int style_Engine;		//引擎样式
	//long color		//颜色等
	/*
	int weapon_red;
	int weapon_green;
	int weapon_blue;
	int engine_red;
	int engine_green;
	int engine_blue;
	*/


	weapontypename weaponTypeName;	//武器名字
	enginetypename engineTypeName;	//引擎名字		//总感觉搞那些派生类毫无用处，最土的办法（用一个参数表示不同武器）最实用。。
	//其他属性根据这两个参数查表就行，看来DataLoader.h也要给RobotAIFactory一份

	//当前属性
	//Circle circle;		//engine的圆(x,y,radium)
	double x;
	double y;

	double engineRotation;	//引擎角度
	double weaponRotation;	//武器角度（独立）
	//double vx,vy,vr;
	
	int hp;

	int remainingAmmo;		
	int cooling;

	//当前帧动作属性(直接把操作码搞来)
	int fire;	//武器Fire(int mnplt)的操作码
	int wturn;	//武器Turn(int mnplt)的操作码
	int run;	//引擎Run(int mnplt)的操作码
	int eturn;	//引擎Turn(int mnplt)的操作码


	Record_RobotInformation(){fire=false;wturn=false;run=false;eturn=false;}
	void Init()
	{
		//部分使用时间更新的属性初始化
		fire=0;
		wturn=0;
		run=0;
		eturn=0;
	}
};


struct Record_BulletInformation
{
	//temp
	int entityID;	//用于MovieClip的唯一标识

	bullettypename type;		//子弹类型,属性数据查表获得

	//Circle circle;		//bullet的圆(x,y,radium)
	double x;
	double y;

	double rotation;	//引擎角度
	//double vx,vy,vr;

	int explode;		//是否集中而爆炸（或反弹之类）
};

struct Record_HitInformation
{
	int entityID;	//用于MovieClip的唯一标识

	bullettypename type;

	double x;
	double y;

	//直线型子弹专用
	double ex;
	double ey;
};

struct Record_ArsenalInformation
{
	int respawning_time_left;
};



struct Record_FrameInformation
{
	//Robot
	Record_RobotInformation robotInformation[Info_MaxRobots];

	//Bullet
	Record_BulletInformation bulletInformation[Info_MaxBullets];

	//Bullet击中效果
	Record_HitInformation hitInformation[Info_MaxBullets];

	//军火库帧信息
	Record_ArsenalInformation arsenalInformation[Info_MaxArsenals];


	//Obstacle Info
	//Circle obstacle[Info_MaxObstacles];		//障碍物
	//这个是否要在这呢
};