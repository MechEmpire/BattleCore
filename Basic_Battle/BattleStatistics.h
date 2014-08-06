#pragma once
#include "BattleMode.h"

//2014/07/25
//一场战斗的统计数据
//改进原来胜者之类数据

class BattleStatistics
{
public:
	int numRobots;		//参战机甲数

	int winnerID;		//胜者ID（vec::pRobot中的下标）
	
	int battleFrames;	//战斗进行帧数
	int numSurvivors;	//幸存者数
	
	//BattleMode battleMode;	//战斗模式参数
	
	//...
	//战斗时间日期
	//胜者机甲名
	//参战者Vector？
	//战斗比赛参数（测试赛，排位赛，联赛。。。）


	BattleStatistics(){}

	//TODO:...
	void ReplaceFlag(ofstream& out,const string & f);

	void Output(const char * filename);
};