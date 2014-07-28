//#include "stdafx.h"
#include "../stdafx.h"
#include "Arsenal.h"
#include "GameEntity.h"
#include "Robot/Weapon/Weapon.h"
#include "Robot/Engine/Engine.h"
#include "DataLoader.h"
#include "struct.h"

Arsenal::Arsenal()
{
	LoadData();
	available=true;
}

Arsenal::~Arsenal()
{
}

void Arsenal::LoadData()
{
	respawning_time=0;

	respawning_time_max=pDataLoader->GetGameData()->respawningTime_Arsenal;
	circle.r=pDataLoader->GetGameData()->radium_Arsenal;
	shapeType=S_Circle;
}

void Arsenal::Touch(Robot& robot)
{
	
#ifdef ARSENAL_MODE_CHANGE_ARMOR
	//军火库的功能有待商议
	
	weapontypename weapon;
	enginetypename engine;
	robot.GetAI().ChooseArmor(weapon,engine,true);

	Circle temp=robot.GetWeapon().GetCircle();
	double tvx,tvy,tvr,tr,tre;

	robot.GetWeapon().GetVelocity(tvx,tvy,tvr);
	tr=robot.GetWeapon().GetRotation();
	tre=robot.GetWeapon().GetEngineRotation();
	//TODO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//这里有问题啊
	//?解决了吗？

	robot.SetWeapon(weapon);
	//robot.GetWeapon().ReLoad();
	robot.GetWeapon().SetCircle(temp);
	robot.GetWeapon().SetVelocity(tvx,tvy,tvr);
	robot.GetWeapon().SetRotation(tr);
	robot.GetWeapon().SetEngineRotation(tre);



	//更换Engine时的hp结算办法
	//暂时按同样比例?
	//robot.GetEngine().GetHp()/robot

	double ratio=robot.GetEngine().GetHpRatio();
	temp=robot.GetEngine().GetCircle();
	robot.GetEngine().GetVelocity(tvx,tvy,tvr);
	tr=robot.GetEngine().GetRotation();
	robot.SetEngine(engine);
	robot.GetEngine().SetHpByRatio(ratio);

	robot.GetEngine().SetCircle(temp);
	robot.GetEngine().SetVelocity(tvx,tvy,tvr);
	robot.GetEngine().SetRotation(tr);
	
#endif

	//2014_2_28,为了体现个性和简化，军火库智能补充弹药而不能更换武器和载具
	//另一个可能要修改的是武器角度不随载具而动，是独立的

#ifndef ARSENAL_MODE_CHANGE_ARMOR
	//不换武器只reload
	robot.GetWeapon().ReLoad();
#endif

	ResetRespawningTime();
}