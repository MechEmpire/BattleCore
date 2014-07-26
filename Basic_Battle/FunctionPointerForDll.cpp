//#include "stdafx.h"
#include "../stdafx.h"
#include "FunctionPointerForDllcpp.h"

//给dll的函数指针部分

//temp
void trace_global(string s)
{
	//cout<<s<<'\n';
	pTraceManager->AddText(s);
}

//getWeaponData
string getWeaponName(weapontypename wtn)
{
	return pDataLoader->getWeaponData(wtn).getName();
}

int getWeaponDamage(weapontypename wtn)
{
	return pDataLoader->getWeaponData(wtn).getDamage();
}

int getWeaponAmmo(weapontypename wtn)
{
	return pDataLoader->getWeaponData(wtn).getAmmo();
}

int getWeaponCoolingTime(weapontypename wtn)
{
	return pDataLoader->getWeaponData(wtn).getCoolingTime();
}

double getWeaponInaccuracy(weapontypename wtn)
{
	return pDataLoader->getWeaponData(wtn).getInaccuracy();
}

double getWeaponRotationSpeed(weapontypename wtn)
{
	return pDataLoader->getWeaponData(wtn).getRotationSpeed();
}

//getEngineData
string getEngineName(enginetypename etn)
{
	return pDataLoader->getEngineData(etn).getName();
}

double getEngineMaxSpeed(enginetypename etn)
{
	return pDataLoader->getEngineData(etn).getMaxSpeed();
}

int getEngineMaxHp(enginetypename etn)
{
	return pDataLoader->getEngineData(etn).getMaxHp();
}

double getEngineRotationSpeed(enginetypename etn)
{
	return pDataLoader->getEngineData(etn).getMaxSpeed();
}

double getEngineAcceleration(enginetypename etn)
{
	return pDataLoader->getEngineData(etn).getAcceleration();
}
