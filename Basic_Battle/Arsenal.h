#pragma once
#include "Trigger.h"

//#define ARSENAL_MODE_CHANGE_ARMOR

//¾ü»ð¿â

class Arsenal:public Trigger
{

public:
	Arsenal();
	virtual ~Arsenal();
	virtual void LoadData();
	virtual void Touch(Robot&);

	virtual void HandleEvent(events msg,void* extraInfo){};
};