#pragma once

//全局函数（供指针用）声明
void trace_global(string);
string getWeaponName(weapontypename wtn);
//int getWeaponDamage(weapontypename wtn);
int getWeaponAmmo(weapontypename wtn);
int getWeaponCoolingTime(weapontypename wtn);
double getWeaponInaccuracy(weapontypename wtn);
double getWeaponRotationSpeed(weapontypename wtn);

string getEngineName(enginetypename etn);
double getEngineMaxSpeed(enginetypename etn);
int getEngineMaxHp(enginetypename etn);
double getEngineRotationSpeed(enginetypename etn);
double getEngineAcceleration(enginetypename etn);

string getBulletName(bullettypename btn);
double getBulletSpeed(bullettypename btn);
int getBulletDamage(bullettypename btn);
int getBulletFlyTime(bullettypename btn);