#pragma once

#include <time.h>
#include <fstream>
#include <string>
using namespace std;

#define TIME_LEFT_MAX 4000


class BattleMode
{
public:
	//指示单场战斗的模式参数
	string battleTypeName;
	bool limitTime;		//时间限制?
	int limit_time_frame;		//时间帧数

	bool record;		//是否生成录像

	//bool debug_log;		//是否生成调试记录

	string record_name;		//录像名称和路径

	bool statistics;		//是否生成战斗统计
	string battle_statistics_name;			//BattleStatistics路径名称

	BattleMode():record_name("Record_tmp")
	{
		battleTypeName="undef";
		limitTime=false;
		limit_time_frame=TIME_LEFT_MAX;
		record=false;
		statistics=false;
		//debug_log=false;
	}


	BattleMode(bool _is_limit_time,int _limit_time_frame,bool _is_record,string _record_name):record_name(_record_name)
	{
		battleTypeName="undef";
		limitTime=_is_limit_time;
		limit_time_frame=_limit_time_frame;
		record=_is_record;
		statistics=false;
	}

	//filename  文件包括路径
	void SetByConfigFile(const char * filename)
	{
		//BattleModeConfig.conf格式
		//战斗模式名，冗余待用
		//是否限制时间
		//时间限制帧数
		//是否生成录像
		//录像路径
		//是否生成战斗统计信息
		//BattleStatistics输出路径
		



		ifstream in;
		in.open(filename);
		string tmp;
		getline(in,tmp);	//第一行描述，下面各行功能，读了扔掉


		getline(in,battleTypeName);	//战斗模式名，冗余待用
		in>>limitTime;				//是否限制时间
		in>>limit_time_frame;		//时间限制帧数
		in>>record;					//是否生成录像
		in>>record_name;			//!!仅是录像路径
		in>>statistics;				//是否生成战斗统计信息
		in>>battle_statistics_name;//!!此处仅是战斗统计的输出路径

		in.close();

		string tstr=TimeString();
		record_name+=tstr+"_battleRecord.txt";
		battle_statistics_name+=tstr+"_battleStatistics.xml";
	}

	string TimeString(/*...*/)
	{
		time_t t=time(0);
		char tmp[25];
		strftime(tmp,sizeof(tmp),"%y-%m-%d-%H-%M-%S",localtime(&t));
		string tmp2=tmp;

		return tmp2;
	}

};
