#include "../../../stdafx.h"
#include "Weapon.h"
#include "W_MineLayer.h"

W_MineLayer::W_MineLayer(void)
{
	coolingTime_Tiny=pDataLoader->GetGameData()->coolingTime_Tiny_MineLayer;
	ammoConsumption_Miner=pDataLoader->GetGameData()->ammoConsumption_Mine_MineLayer;

	LoadData(WT_MineLayer);
	InitData();
	Init_GameEntity();


}


W_MineLayer::~W_MineLayer(void)
{
}



bool W_MineLayer::Fire(int mnplt)
{
	if(mnplt==1)
	{
		//布雷
		if(cooling<=0)
		{
			//冷却完成，可以开火
			cooling=coolingTime;	//枪管发热
			if(remainingAmmo>0)
			{
				//TODO:地雷的耗弹量可以大于1
				remainingAmmo-=ammoConsumption_Miner;		//弹药减少

				pDispatcher->DispatchEvent(ID,pBattlefield->GetID(),
					Add_Bullet,
					new B_Mine(circle.x,circle.y,0,pRobot->GetBattlefieldID()));

				pRobot->GetAchievementData().Add_Fire();

				return true;
			}
		}
	}
	else if(mnplt==2)
	{
		//辅助子弹
		//TODO:辅助子弹的冷却时间量可以大于0
		if(cooling<=coolingTime-coolingTime_Tiny)
		{
			//冷却完成，可以开火
			cooling=coolingTime;	//枪管发热
			if(remainingAmmo>0)
			{
				remainingAmmo-=1;			//弹药减少

				double p=inaccuracy*(Random0_1()-0.5);//偏移角度
				double r=AnglePlus(rotation,p);
				double a=AngleToRadian(r);//弧度

				pDispatcher->DispatchEvent(ID,pBattlefield->GetID(),
					Add_Bullet,
					new B_TinyBall(circle.r*cos(a)+circle.x,circle.r*sin(a)+circle.y,r,pRobot->GetBattlefieldID()));

				pRobot->GetAchievementData().Add_Fire();


				return true;
			}
		}
	}

	return false;
}