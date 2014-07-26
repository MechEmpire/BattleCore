//#include "stdafx.h"
#include "../stdafx.h"
#include "Robot\RobotAIstruct.h"
#include "Battlefield.h"
#include "RecordManager.h"
#include "Recordstruct.h"


RecordManager::RecordManager(void)
{
	fileType=".txt";

#ifdef TEMP_TEST
	fileRoute="";
#endif

	Init();
}


RecordManager::~RecordManager(void)
{
}

RecordManager* RecordManager::Instance()
{
	static RecordManager instance;
	return &instance;
}

void RecordManager::HandleEvent(events msg,void* extraInfo)
{
	//处理事件
	switch(msg)
	{
	case Battle_Start:
		//extraInfo可能放与录像命名路径之类有关的东西
		Init();
		

		break;

	case Battle_End:
		//ReleaseRecord();
			
		//break;

		


	case Round_End:
		//回合（帧）结束，写此帧动画信息至文件？应该最后一起写吧
		



	/*
	case R_RobotInfo:
		//生成某机器人录像信息
		//extraInfo:Record_RobotInformation
		Record_RobotInformation* info=(Record_RobotInformation*)extraInfo;
		frameInfo[currentFrame].robotInformation[(*info).id]=(*info);

		//delete extraInfo;//?
		break;


	case R_BulletInfo:
		Record_BulletInformation* info=(Record_BulletInformation*)extraInfo;
		frameInfo[currentFrame].bulletInformation[(*info).id]=(*info);

		break;
		*/

	case R_HitInfo:
		/*
		//此时extraInfo是BulletInfo
		RobotAI_BulletInformation* info=(RobotAI_BulletInformation*)extraInfo;

		frameInfo[currentFrame].hitInformation[hitID].type=info->type;
		frameInfo[currentFrame].hitInformation[hitID].x=info->circle.x;
		frameInfo[currentFrame].hitInformation[hitID].y=info->circle.y;
		*/

		{
			//extraInfo是Record_HitInformation
			Record_HitInformation* ttt=(Record_HitInformation*)extraInfo;
			//frameInfo[currentFrame].hitInformation[hitID]=*ttt;浅复制？
			frameInfo[currentFrame].hitInformation[hitID].type=ttt->type;
			frameInfo[currentFrame].hitInformation[hitID].x=ttt->x;
			frameInfo[currentFrame].hitInformation[hitID].y=ttt->y;

			if(ttt->type==BT_Prism_Laser || ttt->type==BT_Tesla_Lightning)
			{
				frameInfo[currentFrame].hitInformation[hitID].ex=ttt->ex;
				frameInfo[currentFrame].hitInformation[hitID].ey=ttt->ey;
			}

			hitID++;
			break;
		}




	case R_Run:
		frameInfo[currentFrame].robotInformation[*(int*)extraInfo].run=true;
		break;

	case R_EngineTurn:
		frameInfo[currentFrame].robotInformation[*(int*)extraInfo].eturn=true;
		break;

	case R_Fire:
		frameInfo[currentFrame].robotInformation[*(int*)extraInfo].fire=true;
		break;

	case R_WeaponTurn:
		frameInfo[currentFrame].robotInformation[*(int*)extraInfo].wturn=true;
		break;

	}

	//delete extraInfo;
	//在各个分支视情况在哪里删
}


void RecordManager::Init()
{
	hitID=0;
	currentFrame=0;
}


void RecordManager::EnterFrame_Init()
{
	int i;
	for(i=0;i<pBattlefield->GetInfo().num_robot;i++)
	{
		frameInfo[currentFrame].robotInformation[i].Init();
	}
}





void RecordManager::Update_FrameInfo(RobotAI_BattlefieldInformation& battleInfo)
{
	//Robot,Bullet信息在此更新，hitInfo在Battlefield中以事件形式及时更新


	//这里没用const是为了一下用指针寻址方便，注意不要更改battleInfo
	int i;

	//hitID最后补一个结束标识符
	frameInfo[currentFrame].hitInformation[hitID].type=BT_NULL;



	//RobotInfo
	//int rn=pBattlefield->GetMaxRobots();
	//temp
	int rn=pBattlefield->GetInfo().num_robot;
	//不用vector而用简单数组的话，这里的size怎么处理
	RobotAI_RobotInformation* b;
	Record_RobotInformation* r;
	for(i=0;i<rn;i++)
	{
		b=&battleInfo.robotInformation[i];
		r=&frameInfo[currentFrame].robotInformation[i];

		r->entityID=b->entityID;
		r->id=b->id;
		r->weaponTypeName=b->weaponTypeName;
		r->engineTypeName=b->engineTypeName;

		r->x=b->circle.x;
		r->y=b->circle.y;
		r->weaponRotation=b->weaponRotation;
		r->engineRotation=b->engineRotation;

		r->hp=b->hp;
		r->remainingAmmo=b->remainingAmmo;
		r->cooling=b->cooling;
	}
	b=NULL;
	r=NULL;


	//BulletInfo
	//TODO:
	RobotAI_BulletInformation* bb;
	Record_BulletInformation* rb;
	i=0;
	while(battleInfo.bulletInformation[i].type!=BT_NULL && i<Info_MaxBullets)
	{
		bb=&battleInfo.bulletInformation[i];
		rb=&frameInfo[currentFrame].bulletInformation[i];

		rb->entityID=bb->entityID;
		rb->type=bb->type;
		rb->x=bb->circle.x;
		rb->y=bb->circle.y;
		rb->rotation=bb->rotation;
		
		//...

		i++;
	}
	//bulletInfo最后结束位置标识一下
	if(i<Info_MaxBullets)
	{
		frameInfo[currentFrame].bulletInformation[i].type=BT_NULL;
	}

	bb=NULL;
	rb=NULL;

	//arsenalInfo
	for(i=0;i<battleInfo.num_arsenal;i++)
	{
		frameInfo[currentFrame].arsenalInformation[i].respawning_time_left=battleInfo.arsenal[i].respawning_time;
	}




	hitID=0;//重置新一帧的hitID


	NextFrame();
	//
}


void RecordManager::ReleaseRecord(int winner)
{
	//生成录像
	//把frameInfo写入文件,no extraInfo?
	//TODO:路径构建
	BuildFileRoute();
	f.open(fileRoute_Final);
	//f.open("Record_1.txt");

	int i,j;

	Record_RobotInformation* pR;
	Record_BulletInformation* pB;
	Record_HitInformation* pH;
	Record_ArsenalInformation* pA;

	//int rn=pBattlefield->GetMaxRobots();
	int rn=pBattlefield->GetInfo().num_robot;
	int bn=Info_MaxBullets;
	int hn=Info_MaxBullets;
	int on=pBattlefield->GetInfo().num_obstacle;
	int an=pBattlefield->GetInfo().num_arsenal;

	//起头的general Data，第一行
	//robot
	for(i=0;i<rn;i++)
	{
		//抱歉，图省事，又紧耦合了
		//temp
		f<<pBattlefield->GetRobotInfo_Name(i)<<','
			<<pBattlefield->GetRobotInfo_Author(i)<<','
			<<pBattlefield->GetRobotInfo_Weapon_Red(i)<<','
			<<pBattlefield->GetRobotInfo_Weapon_Green(i)<<','
			<<pBattlefield->GetRobotInfo_Weapon_Blue(i)<<','
			<<pBattlefield->GetRobotInfo_Engine_Red(i)<<','
			<<pBattlefield->GetRobotInfo_Engine_Green(i)<<','
			<<pBattlefield->GetRobotInfo_Engine_Blue(i)<<','
			<<pBattlefield->GetRobotInfo_MaxHp(i)<<','
			<<pBattlefield->GetRobotInfo_MaxAmmo(i);

		if(i<rn-1)
		{
			f<<'*';		//robot之间分隔符
		}
	}

	f<<'|';		//分隔

	//战场、地图信息等其他信息
	//边界
	f<<pBattlefield->GetInfo().boundary.width<<','
		<<pBattlefield->GetInfo().boundary.height;

	f<<'|';		
	//Obstacle障碍
	for(i=0;i<on;i++)
	{
		f<<pBattlefield->GetInfo().obstacle[i].x<<','
			<<pBattlefield->GetInfo().obstacle[i].y<<','
			<<pBattlefield->GetInfo().obstacle[i].r;

		if(i<on-1)
		{
			f<<'*';
		}
	}

	f<<'|';

	//Arsenal军火库
	for(i=0;i<an;i++)
	{
		f<<pBattlefield->GetInfo().arsenal[i].circle.x<<','
			<<pBattlefield->GetInfo().arsenal[i].circle.y<<','
			<<pBattlefield->GetInfo().arsenal[i].circle.r;

		if(i<an-1)
		{
			f<<'*';
		}
	}


	f<<'|';

	//AchievementData统计信息
	for(i=0;i<rn;i++)
	{
		pBattlefield->GetAchievementData(i).Out(f);
		if(i<rn-1)
		{
			f<<'*';
		}
	}

	f<<'|';

	f<<winner;


	f<<'|';//保护

	/////////
	f<<'\n';
	//frameData(从第二行开始是第0帧）
	//不用vector而用简单数组的话，这里的size怎么处理
	for(i=0;i<currentFrame;i++)
	{
		for(j=0;j<rn;j++)
		{
			pR=&frameInfo[i].robotInformation[j];
			f<<pR->entityID<<','
				<<pR->id<<','
				<<pR->x<<','
				<<pR->y<<','
				<<pR->weaponRotation<<','
				<<pR->engineRotation<<','
				<<pR->hp<<','
				<<pR->weaponTypeName<<','
				<<pR->engineTypeName<<','
				<<pR->fire<<','
				<<pR->wturn<<','
				<<pR->run<<','
				<<pR->eturn<<','
				<<pR->remainingAmmo;
			//<<'*';		//'*'Robot间隔符

			if(j<rn-1)
			{
				f<<'*';			//'*'Robot间隔符
			}
		}
		pR=NULL;

		f<<'|';		//Robot与Bullet间隔符

		//Bullet信息
		//TODO


		for(j=0;j<bn;j++)
		{
			pB=&frameInfo[i].bulletInformation[j];
			if(pB->type==BT_NULL)
			{
				//数组结束
				break;
			}

			//不是NULL
			if(j>0)
			{
				f<<'*';
			}


			//临时
			f<<pB->entityID<<','
				<<pB->type<<','
				<<pB->x<<','
				<<pB->y<<','
				<<pB->rotation;
			//<<'*';


		}
		pB=NULL;

		f<<'|';		//Bullet与HitInfo间隔

		//Hit信息
		//TODO
		for(j=0;j<hn;j++)
		{
			pH=&frameInfo[i].hitInformation[j];
			if(pH->type==BT_NULL)
			{
				break;
			}

			//不是NULL
			if(j>0)
			{
				f<<'*';
			}

			//临时
			f<<pH->type<<','
				<<pH->x<<','
				<<pH->y;
			//<<'*';

			if(pH->type==BT_Prism_Laser || pH->type==BT_Tesla_Lightning)
			{
				f<<','<<pH->ex<<','<<pH->ey;
			}



		}
		pH=NULL;
		f<<'|';


		
		//Arsenal的respawningTime
		for(j=0;j<an;j++)
		{
			pA=&frameInfo[i].arsenalInformation[j];
			

			if(j>0)
			{
				f<<'*';
			}

			f<<pA->respawning_time_left;
			

		}


		f<<'|';		//保护用结束符


		if(i<currentFrame-1)
		{
			//帧间隔符'\n'
			f<<'\n';	//编码方式应该是MultiByte
		}
	}

	f.close();


}