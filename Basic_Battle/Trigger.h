#pragma once
#include "GameEntity.h"
#include "Robot/RobotAIstruct.h"
#include "Robot/RobotAI_Interface.h"
#include "Robot/Robot.h"
//触发器


class Trigger:public GameEntity
{
protected:
	bool available;		//可被接触
	int respawning_time;	//冷却时间
	int respawning_time_max;	//最大冷却时间


public:
	Trigger();
	virtual ~Trigger();

	void SetActive(bool b){available=b;}
	void ResetRespawningTime(){respawning_time=respawning_time_max;}

	int GetRespawningTime(){return respawning_time;}


	virtual void LoadData()=0;

	virtual void Touch(Robot&)=0;		//被碰到（触发）

	virtual void Update_Trigger();		//更新

	bool IsActive(){return available && respawning_time<=0;}
};