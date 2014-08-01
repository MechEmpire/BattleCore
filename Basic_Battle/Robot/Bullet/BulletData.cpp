//#include "stdafx.h"
#include "../../../stdafx.h"

BulletData::BulletData()
{
}


BulletData::BulletData(bullettypename btn)
{
	LoadStaticData(btn);
}

BulletData::~BulletData()
{
}

void BulletData::LoadStaticData(bullettypename btn)
{
	type=btn;

	name=pDataLoader->GetGameData()->name_Bullet[btn];
	speed=pDataLoader->GetGameData()->speed_Bullet[btn];
	damage=pDataLoader->GetGameData()->damage_Bullet[btn];
	flyTime=pDataLoader->GetGameData()->flyTime_Bullet[btn];
}



