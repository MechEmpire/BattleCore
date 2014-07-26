#pragma once

class BulletData
{
protected:
	bullettypename type;

	string name;		//子弹的名字
	double speed;		//子弹飞行速度
	int damage;			//威力
public:
	BulletData();
	BulletData(bullettypename);
	~BulletData();

	bullettypename getType();
	string getName();
	double getSpeed();
	int getDamage();

	void LoadStaticData(bullettypename);
};