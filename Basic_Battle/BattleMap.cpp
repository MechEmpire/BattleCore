//#include "stdafx.h"
#include "../stdafx.h"


BattleMap::BattleMap():pObstacle(0,NULL),pArsenal(0,NULL)
{
}


void BattleMap::ConstructMap_Default()
{
	//temp, static map

	//首先是边界
	boundary.width=1366;
	boundary.height=680;
	boundary.x=boundary.width/2;
	boundary.y=boundary.height/2;

	
	B_Left=boundary.x-boundary.width/2;
	B_Right=boundary.x+boundary.width/2;
	B_Up=boundary.y-boundary.height/2;
	B_Down=boundary.y+boundary.height/2;
	

	//obstacle
	//temp中的temp(重复加载，delete等问题)
	num_obstacle=2;

	Obstacle* pO=new Obstacle();
	//
	pO->SetX(300);
	pO->SetY(250);
	pO->SetR(75);
	pO->SetShape(S_Circle);

	pObstacle.push_back(pO);

	pO=new Obstacle();
	pO->SetX(1066);
	pO->SetY(430);
	pO->SetR(75);
	pO->SetShape(S_Circle);

	pObstacle.push_back(pO);
	pO=NULL;

	//出生点
	birthPoint[0].x=B_Left+50;
	birthPoint[0].y=B_Up+50;
	birthPoint[1].x=B_Right-50;
	birthPoint[1].y=B_Down-50;


	//arsenal
	num_arsenal=2;
	Arsenal* pA;

	pA=new Arsenal();
	pA->SetX(50);
	pA->SetY(630);
	//pA->Set
	pArsenal.push_back(pA);

	pA=new Arsenal();
	pA->SetX(1316);
	pA->SetY(50);
	pArsenal.push_back(pA);

	pA=NULL;
}


BattleMap::~BattleMap()
{
	//交给Battlefield::Sweep做
	//真是越改越混乱。。

	//stl用原始指针new。。真傻比
}


void BattleMap::ConstructMap_Config(const char * filename)
{
	//Map config file format:
	//
	//info string: Boundary;obstacle
	//B_left B_Right B_Up B_Down
	//birth point (currently2)
	//1 x,y
	//2 x,y

	//num_obstacle
	//Obstacle1: x,y,r	(currently all round)
	//...
	
	//
	//num_arsenal
	//Arsenal1: x,y


	ifstream in;
	in.open(filename);

	string tmp;
	getline(in,tmp);	//第一行描述，下面各行功能，读了扔掉

	in>>B_Left>>B_Right>>B_Up>>B_Down;

	//TODO:异常处理

	boundary.width = B_Right - B_Left;
	boundary.height = B_Down - B_Up;
	boundary.x = (B_Left + B_Right) / 2;
	boundary.y = (B_Up + B_Down) / 2;

	//Birth point
	for (int i = 0;i<Info_MaxRobots;i++)
	{
		in>>birthPoint[i].x>>birthPoint[i].y;
	}



	//Obstacle
	in>>num_obstacle;
	
	for (int i = 0;i<num_obstacle;i++)
	{
		double x,y,r;
		in>>x>>y>>r;

		Obstacle* pO=new Obstacle();
		pO->SetX(x);
		pO->SetY(y);
		pO->SetR(r);
		pO->SetShape(S_Circle);

		pObstacle.push_back(pO);
	}


	//Arsenal
	in>>num_arsenal;
	
	for (int i = 0;i<num_arsenal;i++)
	{
		double x,y;
		in>>x>>y;

		Arsenal* pA=new Arsenal();
		pA->SetX(x);
		pA->SetY(y);

		pArsenal.push_back(pA);
	}


	in.close();
}