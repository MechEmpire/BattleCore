#pragma once

//2014/07/25
//一场战斗的统计数据
//改进原来胜者之类数据

class BattleStatistics
{
public:
	int numRobots;		//参战机甲数

	int winnerID;		//胜者ID（vec::pRobot中的下标）
	int winnerEntityID;	//胜者ID（Entity）
	int battleFrames;	//战斗进行帧数
	int numSurvivors;	//幸存者数
	//...


	BattleStatistics(){}

	//TODO:...
};