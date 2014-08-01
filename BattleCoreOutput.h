#pragma once

//---------------------------------------
//定义BattleCore.lib的输出函数
//使用lib需要include此头文件
//和其他一些支持性的struct
//---------------------------------------


extern "C"
{

	void LoadGameData();

	void InitNewBattle(/*...*/);

	void SetBattleMode(const BattleMode & battleMode);

	int AddRobotAI(RobotAI_Interface* pAI);

	AchievementData_Battle& GetAchievementData(int robotID);

	BattleStatistics& GetBattleStatistivs();

	bool LaunchBattle();




#ifdef ROBOT_AI_TEST

void StartTestingBattle();

#endif

}