#pragma

#define TIME_LEFT_MAX 4000

class BattleMode
{
public:
	//指示单场战斗的模式参数
	bool limitTime;		//时间限制?
	int limit_time_frame;		//时间帧数

	bool record;		//是否生成录像

	bool debug_log;		//是否生成调试记录

	string record_name;

	BattleMode():record_name("Record_tmp")
	{
		limitTime=false;
		limit_time_frame=TIME_LEFT_MAX;
		record=false;

		debug_log=false;
	}

	//TODO:debug_log
	BattleMode(bool _is_limit_time,int _limit_time_frame,bool _is_record,string _record_name):record_name(_record_name)
	{
		limitTime=_is_limit_time;
		limit_time_frame=_limit_time_frame;
		record=_is_record;
	}
};
