//#include "stdafx.h"

#include "Basic_Battle\Robot\RobotAITest.h"

#include "stdafx.h"
#include "BattleCoreOutput.h"


void LoadGameData()
{
	pDataLoader->LoadDataFromLuaScript("GameData.lua");
}


void InitNewBattle()
{
	//播撒随机数种子
	SetSeed();

	//清扫之前的战场
	pBattlefield->SweepBattlefield(true,true,true,true);


	/*
	pAIManager->AddToBattlefield(ai0);
	pAIManager->AddToBattlefield(ai1);

	pBattlefield->SetBattleMode(battle_mode);
	
	pBattlefield->NewBattle();

	pAchievement->Calculate_Single(ai0);
	pAchievement->Calculate_Single(ai1);

	pBattlefield->SweepBattlefield(true,true,true,true);
	*/
}


void SetBattleMode(const BattleMode & battleMode)
{
	pBattlefield->SetBattleMode(battleMode);
}



int AddRobotAI(RobotAI_Interface* pAI)
{
	//向Battlefield添加AI
	//为pAI指向的AI创建新的机器人加入到战场
	
	
	//函数指针赋值
	pAI->trace=trace_global;		//调试输出函数指针
	
	pAI->getWeaponName=getWeaponName;
	pAI->getWeaponDamage=getWeaponDamage;
	pAI->getWeaponAmmo=getWeaponAmmo;
	pAI->getWeaponCoolingTime=getWeaponCoolingTime;
	pAI->getWeaponInaccuracy=getWeaponInaccuracy;
	pAI->getWeaponRotationSpeed=getWeaponRotationSpeed;
	
	pAI->getEngineName=getEngineName;
	pAI->getEngineMaxSpeed=getEngineMaxSpeed;
	pAI->getEngineMaxHp=getEngineMaxHp;
	pAI->getEngineRotationSpeed=getEngineRotationSpeed;
	pAI->getEngineAcceleration=getEngineAcceleration;
	///////////////////
	

	//TODO:这里的index原来是AIManager中的AI下标
	//现在不需要了
	//封装：BattleCore不管外面链进来的AI的信息

	//只要返回当前加入AI在pRobot的下标
	return (pBattlefield->AddRobotAI(pAI,0));	//先0冗余一下
}

AchievementData_Battle& GetAchievementData(int robotID)
{
	return (pBattlefield->GetAchievementData(robotID));
}


BattleStatistics& GetBattleStatistivs()
{
	return (pBattlefield->GetBattleStatistivs());
}


bool LaunchBattle()
{
	pBattlefield->NewBattle();

	//temp
	return true;
}



#ifdef ROBOT_AI_TEST

void StartTestingBattle()
{
	BattleMode defaultBattleMode(true,4000,true,"zTestingBattle");
	RobotAI_Interface* ai0=new RobotAITest();
	RobotAI_Interface* ai1=new RobotAITest();


	InitNewBattle();
	SetBattleMode(defaultBattleMode);
	int id0=AddRobotAI(ai0);
	int id1=AddRobotAI(ai1);
	LaunchBattle();

	//TODO:打印一些战斗统计数据
	BattleStatistics& battleStatistics=pBattlefield->GetBattleStatistivs();

	cout<<"winner id: "<<battleStatistics.winnerID<<'\n';

	delete ai0;
	delete ai1;
}

#endif