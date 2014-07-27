//#include "stdafx.h"
#include "../stdafx.h"

#include "BaseEntity.h"
#include "Robot\Robot.h"
#include "DataLoader.h"
//#include "Achievementstruct.h"
//#include "AchievementManager.h"

#include "Battlefield.h"

//此处修改了
Battlefield::Battlefield(void):pRobot(0,NULL),pBullet(0,NULL)//,pObstacle(0,NULL)
{
	//AchievementData
	
}


Battlefield::~Battlefield(void)
{
	SweepBattlefield(true,true,true,true);
}

Battlefield* Battlefield::Instance()
{
	static Battlefield instance;
	return &instance;
}




void Battlefield::HandleEvent(events msg, void* extraInfo)
{
	int i,k;
	switch(msg)
	{
	case Add_Bullet:
		//extraInfo是已处理好的Bullet,直接加到“显示对象列表中”
		pBullet.insert(pBullet.end(),(Bullet*)extraInfo);
		//注册EntityID
		//pmngr->RegisterEntity((Bullet*)extraInfo);
		break;
	
	case Explode:
		//火箭弹grenade爆炸
		//TODO:这个做成RPGBall的静态函数
		k=pRobot.size();
		for(i=0;i<k;i++)
		{
			if(HitTestCircles(pRobot[i]->GetEngine().GetCircle(),*((Circle*)extraInfo)))
			{
				//伤害,来自脚本读取类单例
				pRobot[i]->GetEngine().ModifyHp(-(pDataLoader->GetGameData()->damage_Bullet[BT_RPGBall]));//temp
			}
		}
		delete extraInfo;
		break;
	}

}



void Battlefield::BattleStart()
{
	//战斗开始调用

	int i;

	weapontypename wtn;
	enginetypename etn;


	Init_Map();


	//用for_each速度有的文章说不快，先图写着方便用传统的[]
	for(i=0;i<pRobot.size();i++)
	{
		pRobot.at(i)->GetAI().ChooseArmor(wtn,etn,false);
		pRobot.at(i)->SetWeapon(wtn);
		pRobot.at(i)->SetEngine(etn);
		pRobot.at(i)->Init();

		//定位到出生点
		pRobot.at(i)->SetX(birthPoint[i].x);
		pRobot.at(i)->SetY(birthPoint[i].y);


		//2014_3_1朝向 temp
		pRobot.at(i)->GetWeapon().SetRotation(180*i);
		pRobot.at(i)->GetEngine().SetRotation(180*i);
		//AchievementData_Battle初始化
		//pAchievementData_Battle.push_back(new AchievementData_Battle());
		//pAchievementData_Battle[i]->Init();
	}


	//设置初始时间
	if(battleMode.limitTime)
	{
		timeLeft=battleMode.limit_time_frame;
	}
	
	
	//TODO:battleStatistics.Init(...);
	
	
	
	//提供给AI的info初始化
	Init_Info();

	//2014-03-15
	Update_Info();

	
	//调用各个Robot的onBattleStart()
	for(i=0;i<pRobot.size();i++)
	{
		pRobot.at(i)->GetAI().onBattleStart(info,i);
		pRobot.at(i)->GetAchievementData().Init();
	}
	
	pDispatcher->DispatchEvent(GetID(),pRecordManager->GetID(),Battle_Start,NULL);

	//TODO:BattleStart的info
}

int Battlefield::BattleEnd()
{
	//2014-1-24 返回胜者在AIManager中的下标
	//新处理：时间到了，血最多的胜
	//确保每局都有胜者
	//血一样多怎么办？

	//单场成就处理到总成就里
	int max_hp=0;

	int num_Surviver=pRobot.size();
	int i,k=num_Surviver;

	int max_hp_idx=0;

	for(i=0;i<k;i++)
	{
		if(pRobot[i]->Survive()==false)
		{
			num_Surviver--;
		}
		else if(max_hp<pRobot.at(i)->GetEngine().GetHp())
		{
			max_hp=pRobot.at(i)->GetEngine().GetHp();
			max_hp_idx=i;
		}
	}

	//2014-2-24注释
	//pDispatcher->DispatchEvent(GetID(),pRecordManager->GetID(),Battle_End,&info);
	

	

	
	int winner_single_battle=-1;	//这个是单场战斗中vector<robot>的下标
	int winner=-1;//这个是AI下标的胜者
	//bool win;
	int rn=pRobot.size();


	if(num_Surviver==1)
	{
		//有且仅有一人生还
		//max_hp_idx是胜者
		winner_single_battle=max_hp_idx;
		winner=pRobot.at(winner_single_battle)->GetAIIndex();
		for(i=0;i<rn;i++)
		{
			//TODO:抽离战斗核心此处修改
			//pAchievement->Add_AchievementData(pRobot.at(i)->GetAchievementData(),pRobot.at(i)->GetAIIndex(),i==winner_single_battle);

			pRobot.at(i)->GetAI().onBattleEnd(info,i);
		}
	}
	else if(num_Surviver==0)
	{
		//死光了
		//全输，无胜者

		//淘汰赛重赛？
		cout<<"有一局死光了，淘汰赛重赛\n";

		for(i=0;i<rn;i++)
		{
			//TODO:抽离战斗核心此处修改
			//pAchievement->Add_AchievementData(pRobot.at(i)->GetAchievementData(),pRobot.at(i)->GetAIIndex(),false);

			pRobot.at(i)->GetAI().onBattleEnd(info,i);
		}


	}
	else
	{
		//多于一个人还活着


		//TODO:此处完善至多人
		//本届只考虑俩人
		if(rn==2)
		{
			//还是剩余血多的赢吧。。。

			//失血少的那个赢
			//若失血一样多，剩余子弹多的赢（淘汰赛）
			//int damage0=pRobot.at(0)->GetEngine().getMaxHp()-pRobot.at(0)->GetEngine().GetHp();
			//int damage1=pRobot.at(1)->GetEngine().getMaxHp()-pRobot.at(1)->GetEngine().GetHp();

			int hp0=pRobot.at(0)->GetEngine().GetHp();
			int hp1=pRobot.at(1)->GetEngine().GetHp();

			if(hp0>hp1)
			{
				winner_single_battle=0;
				winner=pRobot.at(winner_single_battle)->GetAIIndex();
			}
			else if(hp0<hp1)
			{
				winner_single_battle=1;
				winner=pRobot.at(winner_single_battle)->GetAIIndex();
			}
			else
			{
				//damage0==damage1
				//看弹药剩余
				int a0=pRobot.at(0)->GetWeapon().GetRemainingAmmo();
				int a1=pRobot.at(1)->GetWeapon().GetRemainingAmmo();

				if(a0>a1)
				{
					winner_single_battle=0;
					winner=pRobot.at(winner_single_battle)->GetAIIndex();
				}
				else if( a0<a1 )
				{
					winner_single_battle=1;
					winner=pRobot.at(winner_single_battle)->GetAIIndex();
				}
				else
				{
					//重赛吧
				}
			}
		}


		for(i=0;i<rn;i++)
		{
			//TODO:抽离战斗核心此处修改
			//pAchievement->Add_AchievementData(pRobot.at(i)->GetAchievementData(),pRobot.at(i)->GetAIIndex(),i==winner_single_battle);

			pRobot.at(i)->GetAI().onBattleEnd(info,i);
		}

		
	}

	
	

	//pDispatcher->DispatchEvent(GetID(),pRecordManager->GetID(),Battle_End,&info);
	if(battleMode.record)
	{
		pRecordManager->ReleaseRecord(winner_single_battle);
	}

	for(i=0;i<rn;i++)
	{
		pRobot.at(i)->GetAchievementData().Init();
	}

	//TODO:清理善后工作？
	SweepBattlefield(true,false,false,false);	//只清理子弹


	battleStatistics.winnerID=winner_single_battle;

	return winner;	//pAI中的AI下标(此处一期是AIManager中的下标)，若无胜者为-1
	
}




bool Battlefield::IsFinished()
{
	//2014-2-24 TODO:
	//这里加入胜者下标的信息的输出

	//临时

	//计时战斗指标
	if(battleMode.limitTime && timeLeft<=0)
	{
		return true;	//战斗结束
	}


	//正常最后生存者指标
	int num_Surviver=pRobot.size();
	int i,k=num_Surviver;
	for(i=0;i<k;i++)
	{
		if(pRobot[i]->Survive()==false)
		{
			num_Surviver--;
		}
	}
	if(num_Surviver<=1)
	{
		return true;
	}


	return false;
}







void Battlefield::Update()
{
	//相当于一帧
	pRecordManager->EnterFrame_Init();


	int i,j,k,l;
	Robot* pR=NULL;
	Robot* pRt=NULL;
	Obstacle* pO=NULL;
	Arsenal* pA=NULL;


	//Robot行为
	k=pRobot.size();
	//l=pObstacle.size();
	l=num_obstacle;

	//可改进：用迭代器来遍历for_each
	for(i=0;i<k;i++)
	{
		if(pRobot.at(i)->Survive())
		{
			pR=pRobot.at(i);
			pR->Update(i);
			//Robot间碰撞
			//!!!这里有一个问题，1号更新了位置就直接碰撞检测了，不是所有更新完才碰撞检测
			for(j=i+1;j<k;j++)
			{
				pRt=pRobot.at(j);
				
				if(pR->GetEngine().HitTest(pRt->GetEngine()))
				{
					//9-2 动量这里可能会有问题
					//应该是有飘移速度而非vx,vy,它们会被机甲改变
					GameEntity::MomentumHit(pR->GetEngine(),pRt->GetEngine());
					//Weapon复位校准
					pR->GetWeapon().AjustPosition(pR->GetEngine());
					pRt->GetWeapon().AjustPosition(pRt->GetEngine());
				}
			}

			//Robot与Obstacle之间碰撞检测
			//TODO:矩形
			for(j=0;j<l;j++)
			{
				pO=pObstacle[j];

				if(pR->GetEngine().HitTest(*pO))
				{
					GameEntity::MomentumHit_Half(pR->GetEngine(),*pO);
					//Weapon复位校准
					//pR->GetWeapon().AjustPosition(pR->GetEngine());
				}

			}


			//2013-9-2此处可封装，有待改进
			//Robot与边界的Box之间的碰撞
			double rx=pR->GetEngine().GetCircle().x;
			double ry=pR->GetEngine().GetCircle().y;
			double rr=pR->GetEngine().GetCircle().r;

			if(rx-rr<B_Left)
			{
				//碰到左边界
				pR->GetEngine().SetVX(-pR->GetEngine().GetVX());
				//pR->GetEngine().SetX(B_Left+rr);		//这样有没有黏住的可能？
				pR->SetX(B_Left+rr);
			}
			else if(rx+rr>B_Right)
			{
				//碰到右边界
				pR->GetEngine().SetVX(-pR->GetEngine().GetVX());
				//pR->GetEngine().SetX(B_Right-rr);		//这样有没有黏住的可能？
				pR->SetX(B_Right-rr);
			}

			if(ry-rr<B_Up)
			{
				//碰到上边界
				pR->GetEngine().SetVY(-pR->GetEngine().GetVY());
				//pR->GetEngine().SetY(B_Up+rr);		//这样有没有黏住的可能？
				pR->SetY(B_Up+rr);
			}
			else if(ry+rr>B_Down)
			{
				//碰到下边界
				pR->GetEngine().SetVY(-pR->GetEngine().GetVY());
				//pR->GetEngine().SetY(B_Down-rr);		//这样有没有黏住的可能？
				pR->SetY(B_Down-rr);
			}

			//这里做Weapon的位置校准
			pR->GetWeapon().AjustPosition(pR->GetEngine());



			//检测Arsenal
			for(j=0;j<num_arsenal;j++)
			{
				pA=pArsenal[j];
				if(pR->GetEngine().HitTest(*pA) && pA->IsActive())
				{
					pA->Touch(*pR);
				}
			}

			
		}
	}


	for(j=0;j<num_arsenal;j++)
	{
		pArsenal[j]->Update_Trigger();
	}



	//Bullet行为
	

	list<Bullet*>::iterator iter;

	//简单点了，大开小用
	//可能的碰撞点
	//Point hit_point[Info_MaxRobots+Info_MaxObstacles];
	//int robot_or_obstacle[Info_MaxRobots+Info_MaxObstacles];//记录击中碰撞的robot下标，如果是obstacle则-1

	Point hit_point_nearest;

	

	Point temp;
	int robot_or_obstacle;	//边界

	//int num_points;


	bool disappear;
	
	

	//子弹
	for(iter=pBullet.begin();iter!=pBullet.end();)
	{
		
		//TODO:此处最好封装好了，露在外面太丑陋

		if((*iter)->GetType()==BT_Prism_Laser || (*iter)->GetType()==BT_Tesla_Lightning)
		{
			//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			//直线瞬间型子弹
			//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			hit_point_nearest.x=9999;
			hit_point_nearest.y=9999;

			robot_or_obstacle=-2;
			//先与所有物体碰撞检测
			//有碰撞的计算出碰撞点
			//依照Beam的起点和rotation排序确定最近的那个
			//终点赋值给Beam，结算相关伤害（recordinfo里也要相关改动）
			

			//2014-3-17
			//防止光棱发射口伸入障碍物而导致的穿墙
			disappear=false;
			double tmp_x=(*iter)->GetBeam().x;
			double tmp_y=(*iter)->GetBeam().y;
			if(tmp_x<B_Left || tmp_x>B_Right || tmp_y<B_Up || tmp_y>B_Down)
			{
				disappear=true;
				(*iter)->SetEX(tmp_x);
				(*iter)->SetEY(tmp_y);
			}
			else
			{
				for(i=0;i<l;i++)
				{
					if(HitTestCirclePoint(pObstacle.at(i)->GetCircle(),tmp_x,tmp_y))
					{
						disappear=true;
						(*iter)->SetEX(tmp_x);
						(*iter)->SetEY(tmp_y);
						break;
					}
				}
			}
			///////////////////////////////




			//2014-3-17 穿墙还是时有发生

			if(!disappear)
			{

				//num_points=0;
				//Robot
				for(i=0;i<k;i++)
				{
					pR=pRobot[i];
					if(pR->Survive() && (*iter)->GetLauncher()!=pR->GetID())
					{

						if((*iter)->HitTest(pR->GetEngine()))
						{
							//可能碰撞，计算碰撞点
							temp=GetHitPoint((*iter)->GetBeam(),pR->GetEngine().GetCircle());
							//TODO
							if(abs(temp.x-(*iter)->GetBeam().x)<abs(hit_point_nearest.x-(*iter)->GetBeam().x))
							{
								hit_point_nearest=temp;
								//标下标
								robot_or_obstacle=i;
							}

						}
					}
				}

				//Obstacle
				for(i=0;i<l;i++)
				{
					pO=pObstacle[i];

					if((*iter)->HitTest(*pO))
					{
						temp=GetHitPoint((*iter)->GetBeam(),pO->GetCircle());
						if(abs(temp.x-(*iter)->GetBeam().x)<abs(hit_point_nearest.x-(*iter)->GetBeam().x))
						{
							hit_point_nearest=temp;
							//标下标
							robot_or_obstacle=-1;//obstacle
						}


					}

				}

				//已获得最近点
				if(robot_or_obstacle>=0)
				{
					//击中的是robot
					(*iter)->Hit(*pRobot[robot_or_obstacle]);
					(*iter)->SetEX(hit_point_nearest.x);
					(*iter)->SetEY(hit_point_nearest.y);

					//2014_03_01击中触发
					pR->GetAI().onHit((*iter)->GetType());
				}
				else if(robot_or_obstacle==-1)
				{
					//击中障碍
					(*iter)->SetEX(hit_point_nearest.x);
					(*iter)->SetEY(hit_point_nearest.y);
				}
				else
				{
					//击中边界
					//确定终点
					//TODO
					Beam bb=(*iter)->GetBeam();
					double rrrr=AngleToRadian(bb.rotation);
					double gap_up=0-bb.y;
					double gap_down=-bb.y+boundary.height;
					double gap_left=0-bb.x;
					double gap_right=-bb.x+boundary.width;

					double r_ur=atan2(gap_up,gap_right);	//up right
					double r_ul=atan2(gap_up,gap_left);	
					double r_dr=atan2(gap_down,gap_right);
					double r_dl=atan2(gap_down,gap_left);

					if(rrrr<=r_ur && rrrr>=r_ul)
					{
						//上
						(*iter)->SetEY(0);
						(*iter)->SetEX(gap_up/tan(rrrr)+bb.x);
					}
					else if(rrrr>r_ur && rrrr<=r_dr)
					{
						//右
						(*iter)->SetEY(gap_right*tan(rrrr)+bb.y);
						(*iter)->SetEX(boundary.width);
					}
					else if(rrrr>r_dr && rrrr<=r_dl)
					{
						//下
						(*iter)->SetEY(boundary.height);
						(*iter)->SetEX(gap_down/tan(rrrr)+bb.x);
					}
					else if(rrrr<=r_ul || rrrr>=r_dl)
					{
						//左
						(*iter)->SetEY(gap_left*tan(rrrr)+bb.y);
						(*iter)->SetEX(0);
					}
					else
					{
						(*iter)->SetEY(bb.x);
						(*iter)->SetEX(bb.y);
					}

				}

			}

			//删了它
			//这样的结果就导致激光只能用事件方式作为hitInfo了
			RemoveBulletFromBattlefield(iter,true);
		}
		else
		{
			//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			//其他子弹
			//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


			disappear=false;
			(*iter)->Update();
			//碰撞检测,与Robot
			//k=pRobot.size();
			for(i=0;i<k;i++)
			{
				pR=pRobot[i];
				if(pR->Survive() && (*iter)->GetLauncher()!=pR->GetID())
				{
					//跟踪导弹特殊
					//这里封装又不好了
					(*iter)->AdjustDirection(*pR);


					//bug 8-23 自己射出的子弹这里会先打到自己
					//通过加launcherID(Weapon)的方式解决
					//(*iter)->HitTest(pR->GetEngine())
					if((*iter)->HitTest(pR->GetEngine()))
					{
						//HitReact()
						(*iter)->Hit(*pR);

						//2014_03_01击中触发
						pR->GetAI().onHit((*iter)->GetType());


						//删除TODO
						RemoveBulletFromBattlefield(iter,true);
						disappear=true;
						break;
					}
				}
			}

			



			//碰撞检测，与Obstcal
			//l=pObstacle.size();
			if(!disappear)
			{
				for(i=0;i<l;i++)
				{
					pO=pObstacle[i];

					//圆形(还是用圆形吧，简单一点)
					//(*iter)->HitTest(*pO)
					if((*iter)->HitTest(*pO))
					{
						if((*iter)->HitObstcale(*pO))
						{
							RemoveBulletFromBattlefield(iter,true);
							disappear=true;
						}
						//TODO
						
						break;
					}

				}
			}



			if(!disappear)
			{
				double bx=(*iter)->GetCircle().x,by=(*iter)->GetCircle().y;
				double br=(*iter)->GetCircle().r;

				if(bx<B_Left+br || bx>B_Right-br || by<B_Up+br || by>B_Down-br)
				{
					//炸
					
					pO=new Obstacle();
					
					pO->SetR(0);	//设置其半径为0指示其为边界而非障碍
					pO->SetX(bx);
					pO->SetY(by);

					bool ddd=(*iter)->HitObstcale(*pO);
					delete pO;
					
					

					if(ddd)
					{
						RemoveBulletFromBattlefield(iter,true);
						disappear=true;
					}
				}
			}


			if(!disappear && (*iter)->GetType()==BT_ElectricSaw)
			{
				//近战子弹必须消失
				RemoveBulletFromBattlefield(iter,false);//不产生hit
				disappear=true;
			}

			if(!disappear)
			{
				iter++;
			}
		}

	}

	//更新战场信息
	//AI获得的战场信息总是前一帧的
	Update_Info();

	//RecordInfo的主要更新（除了开火爆炸啥的）
	//在这里更新应该比较好吧
	if(battleMode.record)
	{
		//Battlefield与RecordManager最好统一改成用事件，松耦合
		pRecordManager->Update_FrameInfo(info);
	}

	

	timeLeft--;

	

}


void Battlefield::RemoveBulletFromBattlefield(list<Bullet*>::iterator & ii,bool dis)
{
	//这里的事件机制就不完善了（为了方便）
	Record_HitInformation* hi=NULL;
	if(battleMode.record && dis)
	{

		//Record属性里
		//生成一个新hit效果
		hi=new Record_HitInformation;

		//bug 8-23 此时Bullet已被移除，迭代器找不到相关数据
		hi->type=(*ii)->GetType();
		

		if(hi->type==BT_Prism_Laser || hi->type==BT_Tesla_Lightning)
		{
			hi->x=(*ii)->GetBeam().x;
			hi->y=(*ii)->GetBeam().y;
			hi->ex=(*ii)->GetBeam().ex;
			hi->ey=(*ii)->GetBeam().ey;
		}
		else
		{
			hi->x=(*ii)->GetCircle().x;
			hi->y=(*ii)->GetCircle().y;
		}

		pDispatcher->DispatchEvent(GetID(),pRecordManager->GetID(),R_HitInfo,hi);
		delete hi;
		hi=NULL;

	}




	ii=pBullet.erase(ii);
	//Entity注册移除
	//pmngr->RemoveEntity(*ii);
}


void Battlefield::Init_Info()
{
	//Obstacle,Boundary
	info.boundary=boundary;
	info.num_obstacle=num_obstacle;
	info.num_arsenal=num_arsenal;
	int i;
	int k=num_obstacle;
	//int k=pObstacle.size();
	for(i=0;i<k;i++)
	{
		info.obstacle[i]=pObstacle[i]->GetCircle();
	}
	k=num_arsenal;
	for(i=0;i<k;i++)
	{
		info.arsenal[i].circle=pArsenal[i]->GetCircle();
		info.arsenal[i].respawning_time=pArsenal[i]->GetRespawningTime();
	}
}







void Battlefield::Update_Info()
{
	//更新info:RobotAI_BattlefieldInformation
	
	//int i,j;
	//pRobot[i]->
	int i,k,l;
	Robot* pR=NULL;
	Robot* pRt=NULL;
	Obstacle* pO=NULL;


	//RobotInfo
	k=pRobot.size();
	info.num_robot=k;
	l=pObstacle.size();
	for(i=0;i<k;i++)
	{
		pR=pRobot[i];
		info.robotInformation[i].entityID=pR->GetID();
		info.robotInformation[i].id=i;
		info.robotInformation[i].weaponTypeName=pR->GetWeapon().GetType();
		info.robotInformation[i].engineTypeName=pR->GetEngine().GetType();
		info.robotInformation[i].circle=pR->GetEngine().GetCircle();
		info.robotInformation[i].weaponRotation=pR->GetWeapon().GetRotation();
		info.robotInformation[i].engineRotation=pR->GetEngine().GetRotation();
		pR->GetEngine().GetVelocity(info.robotInformation[i].vx,
			info.robotInformation[i].vy,
			info.robotInformation[i].vr);
		info.robotInformation[i].hp=pR->GetEngine().GetHp();
		info.robotInformation[i].remainingAmmo=pR->GetWeapon().GetRemainingAmmo();
		info.robotInformation[i].cooling=pR->GetWeapon().GetCooling();
	}

	list<Bullet*>::iterator iter;

	i=0;
	for(iter=pBullet.begin();iter!=pBullet.end();iter++)
	{
		//判断i下标是否溢出
		if(i>=Info_MaxBullets)
		{
			//出错溢出
			//assert(i>=Info_MaxBullets)
		}
		info.bulletInformation[i].entityID=(*iter)->GetID();
		
		
		info.bulletInformation[i].type=(*iter)->GetType();

		info.bulletInformation[i].circle=(*iter)->GetCircle();
		
		info.bulletInformation[i].rotation=(*iter)->GetRotation();
		(*iter)->GetVelocity(info.bulletInformation[i].vx,
			info.bulletInformation[i].vy,
			info.bulletInformation[i].vr);







		//2014-3-16
		//折中解决没有launcherID的办法
		if((*iter)->GetLauncher()==0)
		{
			info.bulletInformation[i].circle.r=-999;
		}
		else if((*iter)->GetLauncher()==1)
		{
			info.bulletInformation[i].circle.r=999;
		}

		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!







		i++;
	}
	//把最后一个子弹的在后面一个设成特定标识，提供结束信息
	if(i<=Info_MaxBullets)
	{
		//补一个标识
		info.bulletInformation[i].type=BT_NULL;
	}
	info.num_bullet=i-1;

	//Boundary,Obstacle的信息只在BattleStart时刷新一次
	//不在Update()时再次刷新了


	//Arsenal
	for(i=0;i<num_arsenal;i++)
	{
		info.arsenal[i].respawning_time=pArsenal[i]->GetRespawningTime();
	}
}




//这个addRobot根本就用不着Robot作参数，不同的只是pRobotAI_Interface
bool Battlefield::AddRobot(Robot* newRobot)
{
	
	pRobot.push_back(newRobot);

	//temp
	return true;
}


int Battlefield::AddRobotAI(RobotAI_Interface* newRobotAI,int index)
{
	//对AI的操作要小心啊，仅此一件不要删了。。
	pRobot.push_back(new Robot(newRobotAI,index));

	return (pRobot.size()-1);
}

int Battlefield::NewBattle()
{
	//pBullet.clear();不安全且没必要BattleEnd时负责清理

	int winner;
	pRecordManager->SetFileName(battleMode.record_name);

	if(pRobot.size()>1)
	{
		BattleStart();


		while(!IsFinished())
		{
			Update();
		}

		winner=BattleEnd();

		return winner;
	}
	return -1;
}




void Battlefield::SweepBattlefield_Bullet()
{
	//int bn=pBullet.size();
	list<Bullet*>::iterator iter;
	for(iter=pBullet.begin();iter!=pBullet.end();iter++)
	{
		if((*iter)!=NULL)
		{
			delete (*iter);
			(*iter)=NULL;
		}
	}
	pBullet.clear();
}

void Battlefield::SweepBattlefield_Robot()
{
	int i;
	int rn=pRobot.size();
	for(i=0;i<rn;i++)
	{
		delete pRobot.at(i);
		pRobot.at(i)=NULL;
	}
	pRobot.clear();
}


//TODO
void Battlefield::SweepBattlefield_Map()
{
	//Sweep Obstacle


	//Sweep Arsenal


}

void Battlefield::SweepBattlefield(bool f_bullet=true,bool f_robot=true,bool f_obstacle=true,bool f_arsenal=true)
{
	//战斗结束后清理战场
	//f_*是否清理该部分
	int i;
	
	
	if(f_bullet)
	{
		SweepBattlefield_Bullet();
	}


	if(f_robot)
	{
		SweepBattlefield_Robot();
	}

	if(f_obstacle)
	{
		int on=pObstacle.size();
		for(i=0;i<on;i++)
		{
			delete pObstacle[i];
			pObstacle[i]=NULL;
		}
		pObstacle.clear();
	}

	if(f_arsenal)
	{
		int an=pArsenal.size();
		for(i=0;i<an;i++)
		{
			delete pArsenal[i];
			pArsenal[i]=NULL;
		}
		pArsenal.clear();
	}
}













void Battlefield::Init_Map()
{
	//初始化战场地图
	//周杨在写相关，是不是要做个接口？

	//清理障碍和军火库
	//TODO:以后地图类化规范以后还有出生点
	SweepBattlefield(false,false,true,true);


	Construct_Map();
	
	
	
}





string Battlefield::GetRobotInfo_Name(int index)
{
	return pRobot[index]->GetAI().GetName();
}

string Battlefield::GetRobotInfo_Author(int index)
{
	return pRobot[index]->GetAI().GetAuthor();
}

int Battlefield::GetRobotInfo_Weapon_Red(int index)
{
	return pRobot[index]->GetAI().GetWeaponRed();
}
int Battlefield::GetRobotInfo_Weapon_Green(int index)
{
	return pRobot[index]->GetAI().GetWeaponGreen();
}
int Battlefield::GetRobotInfo_Weapon_Blue(int index)
{
	return pRobot[index]->GetAI().GetWeaponBlue();
}

int Battlefield::GetRobotInfo_Engine_Red(int index)
{
	return pRobot[index]->GetAI().GetEngineRed();
}
int Battlefield::GetRobotInfo_Engine_Green(int index)
{
	return pRobot[index]->GetAI().GetEngineGreen();
}
int Battlefield::GetRobotInfo_Engine_Blue(int index)
{
	return pRobot[index]->GetAI().GetEngineBlue();
}

int Battlefield::GetRobotInfo_MaxHp(int index)
{
	return pRobot[index]->GetEngine().GetMaxHp();
}
int Battlefield::GetRobotInfo_MaxAmmo(int index)
{
	return pRobot[index]->GetWeapon().GetMaxAmmo();
}