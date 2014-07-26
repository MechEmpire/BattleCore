#pragma once

class WeaponData
{
protected:
	weapontypename type;

	string name;			//武器名字
	int damage;			//威力
	int Ammo;			//弹夹（最大弹药量）
	int coolingTime;	//冷却时间
	double inaccuracy;	//不准确度（关联发射角度）
	double rotationSpeed;	//炮塔旋转速度（最大？）

public:
	WeaponData();
	WeaponData(weapontypename);
	~WeaponData();

	weapontypename getType();
	string getName();
	int getDamage();
	int getAmmo();
	int getCoolingTime();
	double getInaccuracy();
	double getRotationSpeed();

	void LoadStaticData(weapontypename);
};