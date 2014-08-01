#pragma once

class BulletData
{
protected:
	bullettypename type;

	string name;		//子弹的名字
	double speed;		//子弹飞行速度
	int damage;			//威力
	int flyTime;			//飞行时间
public:
	BulletData();
	BulletData(bullettypename);
	~BulletData();

	bullettypename getType(){return type;}
	string getName(){return name;}
	double getSpeed(){return speed;}
	int getDamage(){return damage;}
	int getFlyTime(){return flyTime;}

	void LoadStaticData(bullettypename);
};