//#include "stdafx.h"
#include "../../../stdafx.h"
#include "../Robot.h"
#include "../RobotAIstruct.h"
#include "Weapon.h"

//int Weapon::coolingSpeed=pDataLoader->GetGameData()->coolingSpeed_AllWeapon;
int Weapon::coolingSpeed=1;

Weapon::Weapon(void)
{
	engineRotation=0;
}


Weapon::~Weapon(void)
{
	pRobot=NULL;
}



void Weapon::Update_Weapon(Engine & e)
{
	//不是自己跑，是跟着Engine跑
	//得在Engine的Update之后


	if(cooling>0)
	{
		cooling-=coolingSpeed;
	}
	else
	{
		cooling=0;
	}


	rotation=AnglePlus(rotation,vr);

	/*
#ifdef WEAPON_TURN_COMPLEX_MODE
	//2014_3_1 为降低难度，武器角度独立，不随引擎转动而改变
	engineRotation=e.GetRotation();
#endif
	*/

	AjustPosition(e);

}


void Weapon::AjustPosition(Engine & e)
{
	circle.x=e.GetCircle().x;
	circle.y=e.GetCircle().y;
}



bool Weapon::Turn(int mnplt)
{
	if(mnplt>0)
	{
		vr=rotationSpeed;
		return true;
	}
	else if(mnplt<0)
	{
		vr=-rotationSpeed;
		return true;
	}
	else
	{
		//mnplt==0
		vx=0;
		vy=0;
		vr=0;
		return false;
	}
}

bool Weapon::General_Fire(int mnplt)
{
	//操作码>0开火
	if(mnplt>0)
	{
		if(cooling<=0)
		{
			//冷却完成，可以开火
			cooling=coolingTime;	//枪管发热
			if(remainingAmmo>0)
			{
				remainingAmmo-=1;			//弹药减少
				return true;
			}
		}
	}
	return false;//没开火 or 开火失败
}


void Weapon::LoadData(weapontypename wtn)
{
	/*
	type=wtn;
	name=pDataLoader->GetGameData()->name_Weapon[wtn];
	damage=pDataLoader->GetGameData()->damage_Weapon[wtn];
	Ammo=pDataLoader->GetGameData()->Ammo_Weapon[wtn];
	coolingTime=pDataLoader->GetGameData()->coolingTime_Weapon[wtn];
	inaccuracy=pDataLoader->GetGameData()->inaccuracy_Weapon[wtn];
	rotationSpeed=pDataLoader->GetGameData()->rotationSpeed_Weapon[wtn];

	circle.r=pDataLoader->GetGameData()->radium_Weapon[wtn];
	*/
	type=pDataLoader->getWeaponData(wtn).getType();
	name=pDataLoader->getWeaponData(wtn).getName();
	//damage=pDataLoader->getWeaponData(wtn).getDamage();
	Ammo=pDataLoader->getWeaponData(wtn).getAmmo();
	coolingTime=pDataLoader->getWeaponData(wtn).getCoolingTime();
	inaccuracy=pDataLoader->getWeaponData(wtn).getInaccuracy();
	rotationSpeed=pDataLoader->getWeaponData(wtn).getRotationSpeed();

	circle.r=pDataLoader->GetGameData()->radium_Weapon[wtn];
}

void Weapon::InitData()
{
	ReLoad();
	cooling=0;
	engineRotation=0;

	//temp
	//circle.r=10;
}

void Weapon::ReLoad()
{
	remainingAmmo=Ammo;
}