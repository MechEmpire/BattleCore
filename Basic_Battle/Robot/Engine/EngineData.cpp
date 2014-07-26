//#include "stdafx.h"
#include "../../../stdafx.h"

EngineData::EngineData()
{
}

EngineData::EngineData(enginetypename)
{
}

EngineData::~EngineData()
{
}

void EngineData::LoadStaticData(enginetypename etn)
{
	type=etn;

	name=pDataLoader->GetGameData()->name_Engine[etn];
	maxSpeed=pDataLoader->GetGameData()->maxSpeed_Engine[etn];
	maxHp=pDataLoader->GetGameData()->maxHp_Engine[etn];
	rotationSpeed=pDataLoader->GetGameData()->rotationSpeed_Engine[etn];
	acceleration=pDataLoader->GetGameData()->acceleration_Engine[etn];
}

enginetypename EngineData::getType()
{
	return type;
}

string EngineData::getName()
{
	return name;
}

double EngineData::getMaxSpeed()
{
	return maxSpeed;
}
int EngineData::getMaxHp()
{
	return maxHp;
}
double EngineData::getRotationSpeed()
{
	return rotationSpeed;
}
double EngineData::getAcceleration()
{
	return acceleration;
}