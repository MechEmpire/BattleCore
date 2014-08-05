#pragma once

//---------------------------------------
//定义BattleCore.lib的输出函数
//使用lib需要include此头文件
//和其他一些支持性的struct
//尽量减少支持性struct的使用
//---------------------------------------

#define ROBOT_AI_TEST

#include <string>
#include "Basic_Battle/Robot/RobotAI_Interface.h"

using namespace std;

extern "C"
{

	void LoadGameData();

	void InitNewBattle(/*...*/);

	//void SetBattleMode(const BattleMode & battleMode);
	void SetBattleModeWithConfigFile(const char * filename);

	int AddRobotAI(RobotAI_Interface* pAI);

	//AchievementData_Battle& GetAchievementData(int robotID);

	//BattleStatistics& GetBattleStatistivs();

	//void OutputBattleXML(const char * filename);

	bool LaunchBattle();




#ifdef ROBOT_AI_TEST

void StartTestingBattleWithRandomEquipment();
void StartTestingBattleWithAssignedEquipment(int weapon0=0,int engine0=0,int weapon1=4,int engine1=1);

#endif

}