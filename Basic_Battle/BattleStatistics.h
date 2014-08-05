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
	void ReplaceFlag(ofstream& out,const string & f)
	{
		if(f=="nr"){ out<<numRobots;}
		else if(f=="wid"){out<<winnerID;}
		else if(f=="bf"){out<<battleFrames;}
		//TODO:...
	}

	void Output(const char * filename)
	{
		//读取 battleStatics.xml (固定路径) 的格式信函文本
		//逐字符读取，替换掉 $bs$ 而照样输出其他部分
		//$...$ 的部分用switch来对应位置
		ofstream out;	//输出的XML
		out.open(filename);

		ifstream in;	//读入的格式信函文本（XML）
		in.open("battle_xml_format.xml");

		char c;
		while(!in.eof())
		{
			in.get(c);

			if(c=='$')
			{
				//替换标签
				string flag;
				in.get(c);
				while(c!='$')
				{
					flag.push_back(c);
					in.get(c);
				}
				ReplaceFlag(out,flag);
			}
			else
			{
				out<<c;
			}

		}

		in.close();
		out.close();
	}
};