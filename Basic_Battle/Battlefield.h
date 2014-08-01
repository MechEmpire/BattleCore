#pragma once
#include "BattleStatistics.h"




//单例模式？
#define pBattlefield Battlefield::Instance()






class Battlefield
	:public BaseEntity,public BattleMap
{
private:
	Battlefield(void);
	virtual ~Battlefield(void);


	


	//2013-9-15 优化：这个信息类每帧重写我觉得是浪费的
	//bulletinfo什么的struct可以集成在Bullet类里，以指针的方式指向数据
	//
	RobotAI_BattlefieldInformation info;	//战场信息


	

	//const static int maxRobots=2;		//战场最大机器人数
	//const static int initBullets=20;	//初始子弹list数量

	BattleMode battleMode;		//战斗模式标记

	int timeLeft;		//计时模式下时间剩余
	
	BattleStatistics battleStatistics;

	//2013-12-8 这。。拿stl容器还用指针+new行为真是脑残。。

	//容器

	vector<Robot*> pRobot;
	list<Bullet*> pBullet;
 

public:
	//对外方法
	static Battlefield* Instance();

	//RecordManager使用的获取信息函数
	//int GetMaxRobots(){return maxRobots;}
	string GetRobotInfo_Name(int);
	string GetRobotInfo_Author(int);
	int GetRobotInfo_Weapon_Red(int);
	int GetRobotInfo_Weapon_Green(int);
	int GetRobotInfo_Weapon_Blue(int);
	int GetRobotInfo_Engine_Red(int);
	int GetRobotInfo_Engine_Green(int);
	int GetRobotInfo_Engine_Blue(int);

	int GetRobotInfo_MaxHp(int);
	int GetRobotInfo_MaxAmmo(int);



	Box GetBoundary(){return boundary;}
	double Get_B_Left(){return B_Left;}
	double Get_B_Right(){return B_Right;}
	double Get_B_Up(){return B_Up;}
	double Get_B_Down(){return B_Down;}


	//const? &
	AchievementData_Battle & GetAchievementData(int index)
	{
		return pRobot.at(index)->GetAchievementData();
	}

	BattleStatistics & GetBattleStatistivs()
	{
		return battleStatistics;
	}

	Robot* GetRobotPointer(int id)
	{
		return pRobot.at(id);
	}
	

	//战斗参数设置
	void SetBattleMode(const BattleMode & battle_mode){battleMode=battle_mode;}

	void SetMode_LimitTime(bool a){battleMode.limitTime=a;}
	void SetMode_Record(bool a,string filename="Record_1"){battleMode.record=a;pRecordManager->SetFileName(filename);}



	//参战机器人设置
	int AddRobotAI(RobotAI_Interface*,int);	//添加参战AI，返回在pRobot中下标

	//开始战斗，返回战斗是否成功进行（防止Robot添加有误）外部的入口操纵
	//2014-1-24 返回胜者在AIManager中的下标
	//TODO:战斗信息：反应一场战斗的全部信息
	int NewBattle();



	///////////////////////////////////////////////////////////////////

	void BattleStart();
	int BattleEnd();	//返回胜者AIManager中的下标

	//TODO:这样的代码可读性差，把他们拆成四个函数
	void SweepBattlefield_Bullet();
	void SweepBattlefield_Robot();
	void SweepBattlefield_Map();
	//参数分别为是否清理pBullet,pRobot,pObstacle,pArsenal
	void SweepBattlefield(bool f_bullet,bool f_robot,bool f_obstacle,bool f_arsenal);	//打扫战场
	


	void Update();//round_start,round_end都在里头


	void Init_Map();		//初始化地图

	void Init_BattleStatistics();
	//void Finish_BattleStatistics();

	void Init_Info();	//初始化用于AI的info
	void Update_Info();	//更新战场信息

	bool IsFinished();	//判断一场战斗是否终止
	
	RobotAI_BattlefieldInformation& GetInfo(){return info;}


	void RemoveBulletFromBattlefield(list<Bullet*>::iterator & ii,bool);


	virtual void HandleEvent(events msg,void* extraInfo);
};

