//#include "stdafx.h"

#include <fstream>

#include "Basic_Battle/Robot/RobotAITest.h"

#include "stdafx.h"
#include "BattleCoreOutput.h"




void LoadGameData()
{
	pDataLoader->LoadDataFromLuaScript("GameData.lua");
}


void InitNewBattle()
{
	//播撒随机数种子
	SetSeed();

	//清扫之前的战场
	pBattlefield->SweepBattlefield(true,true,true,true);

}

/*
void SetBattleMode(const BattleMode & battleMode)
{
	pBattlefield->SetBattleMode(battleMode);
}
*/

void SetBattleModeWithConfigFile(const char * filename)
{
	pBattlefield->SetBattleModeWithConfigFile(filename);
}


int AddRobotAI(RobotAI_Interface* pAI)
{
	//向Battlefield添加AI
	//为pAI指向的AI创建新的机器人加入到战场
	
	
	//函数指针赋值
	pAI->trace=trace_global;		//调试输出函数指针
	
	pAI->getWeaponName=getWeaponName;
	//pAI->getWeaponDamage=getWeaponDamage;
	pAI->getWeaponAmmo=getWeaponAmmo;
	pAI->getWeaponCoolingTime=getWeaponCoolingTime;
	pAI->getWeaponInaccuracy=getWeaponInaccuracy;
	pAI->getWeaponRotationSpeed=getWeaponRotationSpeed;
	
	pAI->getEngineName=getEngineName;
	pAI->getEngineMaxSpeed=getEngineMaxSpeed;
	pAI->getEngineMaxHp=getEngineMaxHp;
	pAI->getEngineRotationSpeed=getEngineRotationSpeed;
	pAI->getEngineAcceleration=getEngineAcceleration;

	pAI->getBulletName=getBulletName;
	pAI->getBulletSpeed=getBulletSpeed;
	pAI->getBulletDamage=getBulletDamage;
	pAI->getBulletFlyTime=getBulletFlyTime;
	///////////////////
	

	//TODO:这里的index原来是AIManager中的AI下标
	//现在不需要了
	//封装：BattleCore不管外面链进来的AI的信息

	//只要返回当前加入AI在pRobot的下标
	return (pBattlefield->AddRobotAI(pAI,0));	//先0冗余一下
}

/*
AchievementData_Battle& GetAchievementData(int robotID)
{
	return (pBattlefield->GetAchievementData(robotID));
}
*/

/*
BattleStatistics& GetBattleStatistivs()
{
	return (pBattlefield->GetBattleStatistivs());
}
*/

void ReplaceFlag(ofstream& out,const string & f)
{
	if(f=="nr"){ out<<(pBattlefield->GetBattleStatistivs().numRobots);}
	else if(f=="wid"){out<<(pBattlefield->GetBattleStatistivs().winnerID);}
	else if(f=="bf"){out<<(pBattlefield->GetBattleStatistivs().battleFrames);}
	//TODO:...
}


//输出战斗信息的XML，供网站读取
//@filename: 输出的文件名和路径
void OutputBattleXML(const char * filename)
{
	//读取 battleStatics.xml (固定路径) 的格式信函文本
	//逐字符读取，替换掉 $bs$ 而照样输出其他部分
	//$...$ 的部分用switch来对应位置
	ofstream out;	//输出的XML
	out.open(filename);

	ifstream in;	//读入的格式信函文本（XML）
	in.open("battle_xml_format.xml");

	char c;
	while(!in.eof())
	{
		in.get(c);

		if(c=='$')
		{
			//替换标签
			string flag;
			do
			{
				in.get(c);
				flag.push_back(c);
			}while(c!='$');
			ReplaceFlag(out,flag);
		}
		else
		{
			out<<c;
		}

	}



	in.close();
	out.close();
}



bool LaunchBattle()
{
	pBattlefield->NewBattle();

	//temp
	return true;
}



#ifdef ROBOT_AI_TEST

void StartTestingBattleWithRandomEquipment()
{
	BattleMode defaultBattleMode(true,4000,true,"zTestingBattle");
	RobotAI_Interface* ai0=new RobotAITest();
	RobotAI_Interface* ai1=new RobotAITest();


	InitNewBattle();
	pBattlefield->SetBattleMode(defaultBattleMode);
	int id0=AddRobotAI(ai0);
	int id1=AddRobotAI(ai1);
	LaunchBattle();

	//TODO:打印一些战斗统计数据
	BattleStatistics& battleStatistics=pBattlefield->GetBattleStatistivs();

	cout<<"winner id: "<<battleStatistics.winnerID<<'\n';

	delete ai0;
	delete ai1;
}

void StartTestingBattleWithAssignedEquipment(int weapon0,int engine0,int weapon1,int engine1)
{
	BattleMode defaultBattleMode(true,4000,true,"zTestingBattle");
	
	RobotAI_Interface* ai0=new RobotAITest();
	((RobotAITest*)ai0)->m_weapon=(weapontypename)weapon0;
	((RobotAITest*)ai0)->m_engine=(enginetypename)engine0;

	RobotAI_Interface* ai1=new RobotAITest();
	((RobotAITest*)ai1)->m_weapon=(weapontypename)weapon1;
	((RobotAITest*)ai1)->m_engine=(enginetypename)engine1;


	InitNewBattle();
	pBattlefield->SetBattleMode(defaultBattleMode);
	int id0=AddRobotAI(ai0);
	int id1=AddRobotAI(ai1);
	LaunchBattle();

	//TODO:打印一些战斗统计数据
	BattleStatistics& battleStatistics=pBattlefield->GetBattleStatistivs();

	cout<<"winner id: "<<battleStatistics.winnerID<<'\n';

	delete ai0;
	delete ai1;
}


#endif