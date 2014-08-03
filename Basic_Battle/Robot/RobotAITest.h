#pragma once


#define ROBOT_AI_TEST


#ifdef ROBOT_AI_TEST
#include<string>
#include<vector>

#include "../struct.h"
#include "RobotAIstruct.h"
#include "RobotAI_Interface.h"

class RobotAITest:public RobotAI_Interface
{
protected:
	//TODO:可以在这里添加你自己的成员变量


public:

	//测试机甲用
	weapontypename m_weapon;
	enginetypename m_engine;



	//************************************************
	//这一段函数声明别乱动啊，否则机甲抛锚了别怪我

	RobotAITest();
	virtual ~RobotAITest();



	//-----------------------------------------------------
	//1.必须完成的战斗核心
	//-----------------------------------------------------

	//帧操纵函数
	//功能：在每一帧被调用，完成你的机甲在这一帧的动作决策
	//参数：order	...	机甲操纵指令，你在函数体中给它赋值以操纵机甲在这一帧的行为
	//		info	...	战场信息
	//		myID	... 自己机甲在info中robot数组对应的下标
	//		(这几个参数的详细说明在开发手册可以找到，你也可以在RobotAIstruct.h中直接找到它们的代码)
	virtual void Update(RobotAI_Order& order,const RobotAI_BattlefieldInformation& info,int myID);



	//挑选装备函数
	//功能：在战斗开始时为你的机甲选择合适的武器炮塔和引擎载具
	//参数：weapon	...	代表你选择的武器，在函数体中给它赋值
	//		engine	...	代表你选择的引擎，在函数体中给它赋值
	//tip:	括号里的参数是枚举类型 weapontypename 或 enginetypename
	//		开发文档中有详细说明，你也可以在RobotAIstruct.h中直接找到它们的代码
	//tip:	最后一个bool是没用的。。那是一个退化的器官
	virtual void ChooseArmor(weapontypename& weapon,enginetypename& engine,bool);


	//-----------------------------------------------------






	//-----------------------------------------------------
	//2.个性信息
	//-----------------------------------------------------

	//返回你的机甲的名字
	virtual string GetName();
	
	//返回机甲制作人或团队的名字
	virtual string GetAuthor();



	//返回一个(-255,255)之间的机甲武器炮塔的颜色偏移值（红、绿、蓝）
	//你可以在flash客户端的参数预览中预览颜色搭配的效果
	virtual int GetWeaponRed();
	virtual int GetWeaponGreen();
	virtual int GetWeaponBlue();

	//返回一个(-255,255)之间的机甲引擎载具的颜色偏移值（红、绿、蓝）
	//你可以在flash客户端的参数预览中预览颜色搭配的效果
	virtual int GetEngineRed();
	virtual int GetEngineGreen();
	virtual int GetEngineBlue();

	//-----------------------------------------------------




	//-----------------------------------------------------
	//3.用不用随你的触发函数
	//-----------------------------------------------------


	//一场战斗开始时被调用，可能可以用来初始化
	//参数：info	...	战场信息
	//		myID	... 自己机甲在info中robot数组对应的下标
	virtual void onBattleStart(const RobotAI_BattlefieldInformation& info,int myID);
	
	
	
	//一场战斗结束时被调用，可能可以用来析构你动态分配的内存空间（如果你用了的话）
	//参数：info	...	战场信息
	//		myID	... 自己机甲在info中robot数组对应的下标
	virtual void onBattleEnd(const RobotAI_BattlefieldInformation& info,int myID);			
	
	
	//有机甲开火时被调用
	//参数：fireID	... 开火的机甲下标
	virtual void onSomeoneFire(int fireID);


	//被子弹击中时被调用
	//参数：launcherID 发射者下标
	//		btn	...	击中你的子弹种类（枚举类型）
	virtual void onHit(int launcherID,bullettypename btn);

	//-------------------------------------------------------------



	//***************************************************************



	//TODO:可以在这里添加你自己的函数声明,并在RobotAI.cpp中编写相应的函数定义







};


#endif