//#include "stdafx.h"
#include "../../../stdafx.h"
#include "../../GameEntity.h"
#include "../../struct.h"
#include "Engine.h"


Engine::Engine(void)
{

}


Engine::~Engine(void)
{
	pRobot=NULL;
}




void Engine::LoadData(enginetypename etn)
{
	type=etn;

	name=pDataLoader->GetGameData()->name_Engine[etn];
	maxSpeed=pDataLoader->GetGameData()->maxSpeed_Engine[etn];
	maxHp=pDataLoader->GetGameData()->maxHp_Engine[etn];
	rotationSpeed=pDataLoader->GetGameData()->rotationSpeed_Engine[etn];
	acceleration=pDataLoader->GetGameData()->acceleration_Engine[etn];

	circle.r=pDataLoader->GetGameData()->radium_Engine[etn];
}

void Engine::InitData()
{
	hp=maxHp;

	rotation=0;

	//temp

	//circle.r=10;
}