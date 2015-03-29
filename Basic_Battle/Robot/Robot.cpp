//include"../stdafx.h"
//#include "stdafx.h"
#include "../../stdafx.h"
#include "../GameEntity.h"
#include "Engine/Engine.h"
#include "Weapon/Weapon.h"
#include "RobotAIstruct.h"
#include "RobotAI_Interface.h"
#include "Robot.h"
#include "../Battlefield.h"


Robot::Robot(void):achievement_data()
{
	pWeapon=NULL;
	pEngine=NULL;
}

Robot::Robot(RobotAI_Interface* ai,int index):achievement_data()
{
	pRobotAI=ai;
	pWeapon=NULL;
	pEngine=NULL;

	AI_index=index;
}



Robot::~Robot(void)
{
	//delete pRobotAI;
	pRobotAI=NULL;	//指向的是加载的AI，由AIManager负责删
	delete pWeapon;
	delete pEngine;
}


bool Robot::Survive()
{
	if(pEngine!=NULL)
	{
		return pEngine->Survive();
	}
	return false;
}


void Robot::Update(int myID)
{
	//根据得到的a,b,c,d等参数对武器和引擎进行操控
	//switch(a){ case x: pWeapon->Fire();...}
	//pEngine->Turn(b)...
	RobotAI_Order order;


	//AI思考，获得操控参数order
	pRobotAI->Update(order,pBattlefield->GetInfo(),myID);

	//对武器Weapon的开火操控
	if(pWeapon->Fire(order.fire))
	{
		pDispatcher->DispatchEvent(GetID(),pRecordManager->GetID(),R_Fire,&myID);
		pDispatcher->DispatchEvent(GetID(),pBattlefield->GetID(),R_Fire,&myID);
	}
	
	//对引擎Engine的行进Run，旋转Turn操控（改变速度）
	if(pEngine->Run(order.run))
	{
		pDispatcher->DispatchEvent(GetID(),pRecordManager->GetID(),R_Run,&myID);
	}
	if(pEngine->Turn(order.eturn))
	{
		pDispatcher->DispatchEvent(GetID(),pRecordManager->GetID(),R_EngineTurn,&myID);
	}

	//对武器Weapon的旋转Turn操控
	if(pWeapon->Turn(order.wturn))
	{
		pDispatcher->DispatchEvent(GetID(),pRecordManager->GetID(),R_WeaponTurn,&myID);
	}

	//Robot行进（改变位置等）
	pEngine->Update();
	pWeapon->Update_Weapon(*pEngine);
	
}

void Robot::SetWeapon(weapontypename wtn)
{
	if(pWeapon!=NULL)
	{
		delete pWeapon;
	}

	switch(wtn)
	{
	case WT_Cannon:
		pWeapon=new W_Cannon();
		break;

	case WT_Machinegun:
		pWeapon=new W_Machinegun();
		break;

	case WT_Prism:
		pWeapon=new W_Prism();
		break;

	case WT_Tesla:
		pWeapon=new W_Tesla();
		break;

	case WT_RPG:
		pWeapon=new W_RPG();
		break;

	case WT_Shotgun:
		pWeapon=new W_Shotgun();
		break;


	case WT_PlasmaTorch:
		pWeapon=new W_PlasmaTorch();
		break;
		//...
	case WT_MissileLauncher:
		pWeapon=new W_MissileLauncher();
		break;

	case WT_ElectricSaw:
		pWeapon=new W_ElectricSaw();
		break;

	case WT_GrenadeThrower:
		pWeapon=new W_GrenadeThrower();
		break;

	case WT_MineLayer:
		pWeapon = new W_MineLayer();
		break;

	case WT_Apollo:
		pWeapon = new W_Cannon(WT_Apollo);
		break;

	default:
		//AI送的数据有问题
		//默认第一个
		cout<<"Weapon Select Error!\nGet Default Weapon...\n";
		pWeapon=new W_Cannon();
		break;
	}
	pWeapon->SetpRobot(this);
}


void Robot::SetEngine(enginetypename etn)
{
	if(pEngine!=NULL)
	{
		delete pEngine;
	}


	switch(etn)
	{
	case ET_Spider:
		pEngine=new E_Spider();
		break;

	case ET_Robotman:
		pEngine=new E_Robotman();
		break;

	case ET_AFV:
		pEngine=new E_AFV();
		break;

	case ET_UFO:
		pEngine=new E_UFO();
		break;

	default:
		//AI送的数据有问题
		//默认第一个
		cout<<"Engine Select Error!\nGet Default Engine...\n";
		pEngine=new E_Spider();
		break;
	}

	pEngine->SetpRobot(this);
}


void Robot::SetAI(RobotAI_Interface* ai)
{
	pRobotAI=ai;
	//AI_index=index;
}


void Robot::Init()
{
	pEngine->InitData();
	pWeapon->InitData();
}



void Robot::HandleEvent(events msg,void* extraInfo)
{

}

void Robot::SetX(double xx)
{
	pEngine->SetX(xx);
	pWeapon->SetX(xx);
}

void Robot::SetY(double yy)
{
	pEngine->SetY(yy);
	pWeapon->SetY(yy);
}