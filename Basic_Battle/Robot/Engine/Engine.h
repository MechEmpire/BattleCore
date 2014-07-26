#pragma once

class Engine :
	public GameEntity,public EngineData
{
protected:
	Robot* pRobot;


	

	//当前属性
	int hp;		//当前血量




	bool manipulation;		//是否可以操控?

public:
	Engine(void);
	virtual ~Engine(void);

	virtual enginetypename GetType()=0;

	void SetpRobot(Robot* r){pRobot=r;}


	bool Survive()			//hp是否大于0，是否还活着
	{
		//要不要发送一个挂了的事件
		return hp>0;
	}

	bool ModifyHp(int dhp)		//修改hp值，返回是否存活
	{
		hp+=dhp;
		if(dhp<0)
		{
			pRobot->GetAchievementData().Add_damage(-dhp);
		}
		return Survive();
	}

	int GetHp(){return hp;}
	int GetMaxHp(){return maxHp;}

	double GetHpRatio(){return (double)hp/(double)maxHp;}
	void SetHpByRatio(double ratio){hp=(int)(maxHp*ratio);}


	//从脚本载入数据
	void LoadData(enginetypename);
	//部分数据初始化
	void InitData();

	//操控函数
	virtual bool Run(int)=0;	//直线上速度操控
	virtual bool Turn(int)=0;	//方向旋转操控

	virtual void HandleEvent(events msg,void* extraInfo){};
};

