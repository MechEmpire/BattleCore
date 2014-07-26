#pragma once
//#include "RobotAI_Interface.h"
#include "../Achievementstruct.h"

//#include"Weapon\Weapon.h"
//#include "Engine\Engine.h"

class Weapon;
class Engine;

class Robot
	:public BaseEntity		//似乎它没必要作为GameEntity的子类
{
protected:
	RobotAI_Interface* pRobotAI;		
	Weapon* pWeapon;
	Engine* pEngine;

	AchievementData_Battle achievement_data;

	//TODO:与服务器等通信这里斟酌
	int AI_index;		//加载AI在AIManager::pAI中的下标

public:
	Robot(void);
	Robot(RobotAI_Interface*,int);
	//Robot(const Robot&);
	virtual ~Robot(void);

	virtual void Update(int);


	//void Damage(double dmg){pEngine->ModifyHp(-dmg);}

	//SetAI( 这里参数似乎应该是dll导出类的指针 )

	void SetAI(RobotAI_Interface*);

	void SetWeapon(weapontypename);
	void SetEngine(enginetypename);


	RobotAI_Interface& GetAI(){return *pRobotAI;}
	Weapon& GetWeapon(){return *pWeapon;}
	Engine& GetEngine(){return *pEngine;}
	
	AchievementData_Battle& GetAchievementData(){return achievement_data;}
	int GetAIIndex(){return AI_index;}

	bool Survive();
	
	void SetX(double);
	void SetY(double);



	void Init();

	virtual void HandleEvent(events msg,void* extraInfo);
};

