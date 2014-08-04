#pragma once

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

	bool debug_log;		//是否生成调试记录

	string record_name;

	BattleMode():record_name("Record_tmp")
	{
		battleTypeName="undef";
		limitTime=false;
		limit_time_frame=TIME_LEFT_MAX;
		record=false;

		debug_log=false;
	}

	//TODO:debug_log
	BattleMode(bool _is_limit_time,int _limit_time_frame,bool _is_record,string _record_name):record_name(_record_name)
	{
		battleTypeName="undef";
		limitTime=_is_limit_time;
		limit_time_frame=_limit_time_frame;
		record=_is_record;
	}

	//filename  文件包括路径
	void SetByConfigFile(const char * filename)
	{
		ifstream in;
		in.open(filename);
		string tmp;
		getline(in,tmp);

		in>>limitTime;
		in>>limit_time_frame;
		in>>record;
		in>>record_name;

		in.close();
	}

	void GenerateRecordName(/*...*/)
	{
		//TODO
		//根据战斗机甲名称和时间等信息生成
	}

};
