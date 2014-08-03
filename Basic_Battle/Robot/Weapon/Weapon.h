#pragma once

//#include"../Engine/Engine.h"

class Engine;

//抽象类
class Weapon :
	public GameEntity,public WeaponData
{
protected:
	//性能指标（相对static）
	Robot* pRobot;		//指向父级指针

	//静态数据放进了WeaponData里

	static int coolingSpeed;	//冷却速度


	//当前属性
	int remainingAmmo;		//剩余子弹数
	int cooling;		//当前冷却值，[0, coolingTime] ,为0方可Fire()

	double engineRotation;	//基座引擎的rotation,由Robot类负责更新
							//炮塔实际指向：AnglePlus(rotation,engineRotation)

	//?
	bool manipulation;		//是否可以操控

public:
	Weapon(void);
	virtual ~Weapon(void);		//要虚析构吗？

	void SetEngineRotation(double rr){engineRotation=rr;}
	void SetpRobot(Robot* r){pRobot=r;};

	virtual weapontypename GetType()=0;

	int GetRemainingAmmo(){return remainingAmmo;}
	int GetCooling(){return cooling;}
	int GetMaxAmmo(){return Ammo;}

	double GetEngineRotation(){return engineRotation;}

	bool General_Fire(int mnplt);
	void Heating(){cooling=coolingTime;}

	//从脚本载入数据
	void LoadData(weapontypename);

	//部分数据初始化
	void InitData();

	void ReLoad();

	//virtual void Update();
	void Update_Weapon(Engine &);
	void AjustPosition(Engine &);		//校准xy坐标

	//操控方法
	virtual bool Fire(int mnplt)=0;		//最好要用到事件机制？(感觉不用事件，类之间又紧耦合了。。整个过程好像又得到Battlefield里实现？)
	virtual bool Turn(int);

	virtual void HandleEvent(events msg,void* extraInfo){};

	
};

