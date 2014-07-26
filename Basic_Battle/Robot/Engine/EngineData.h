#pragma once

class EngineData
{
protected:
	//性能
	enginetypename type;	//枚举类型

	string name;		//引擎名字
	double maxSpeed;	//最大牵引速度(根号vx2+vy2)
	int maxHp;				//血量上限

	double rotationSpeed;	//最大旋转速度
	double acceleration;	//加速度（战锤坦克和UFO才有该属性）

public:
	EngineData();
	EngineData(enginetypename);
	~EngineData();

	enginetypename getType();
	string getName();
	double getMaxSpeed();
	int getMaxHp();
	double getRotationSpeed();
	double getAcceleration();

	void LoadStaticData(enginetypename);
};