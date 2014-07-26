//#include "stdafx.h"
#include "../stdafx.h"
#include "Trigger.h"

Trigger::Trigger()
{
	//子类实现实现这些
	//vx=0;
	//vy=0;
	//vr=0;
	//LoadData
}

Trigger::~Trigger()
{
}

void Trigger::Update_Trigger()
{
	if(respawning_time>0)
	{
		respawning_time--;
	}
}
