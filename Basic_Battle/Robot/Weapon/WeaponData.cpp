//#include "stdafx.h"
#include "../../../stdafx.h"

WeaponData::WeaponData()
{
}


WeaponData::WeaponData(weapontypename wtn)
{
	LoadStaticData(wtn);
}

WeaponData::~WeaponData()
{
}

void WeaponData::LoadStaticData(weapontypename wtn)
{
	type=wtn;
	name=pDataLoader->GetGameData()->name_Weapon[wtn];
	damage=pDataLoader->GetGameData()->damage_Weapon[wtn];
	Ammo=pDataLoader->GetGameData()->Ammo_Weapon[wtn];
	coolingTime=pDataLoader->GetGameData()->coolingTime_Weapon[wtn];
	inaccuracy=pDataLoader->GetGameData()->inaccuracy_Weapon[wtn];
	rotationSpeed=pDataLoader->GetGameData()->rotationSpeed_Weapon[wtn];

	
}

weapontypename WeaponData::getType()
{
	return type;
}
string WeaponData::getName()
{
	return name;
}
int WeaponData::getDamage()
{
	return damage;
}
int WeaponData::getAmmo()
{
	return Ammo;
}
int WeaponData::getCoolingTime()
{
	return coolingTime;
}
double WeaponData::getInaccuracy()
{
	return inaccuracy;
}
double WeaponData::getRotationSpeed()
{
	return rotationSpeed;
}