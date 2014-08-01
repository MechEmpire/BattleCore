
// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once






//底层逻辑代码的stdafx include

#include<fstream>

#include <string>
#include <map>
#include <vector>
#include <list>

#include <algorithm>



extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}


#include <stdio.h>
#include <iostream>


#include <stdlib.h>
#include <assert.h>



// TODO: 在此处引用程序需要的其他头文件

//#include "Common/2D/Vector2D.h"
#include "Basic_Battle/Vector2D.h"

#include "Basic_Battle/EventTypeName.h"
#include "Basic_Battle/struct.h"

#include "Basic_Battle/Robot/RobotAIstruct.h"

#include "Basic_Battle/BaseEntity.h"
#include "Basic_Battle/GameEntity.h"

#include "Basic_Battle/BattleMode.h"


#include "Basic_Battle/Trigger.h"
#include "Basic_Battle/Arsenal.h"

#include "Basic_Battle/Obstacle.h"

#include "Basic_Battle/Recordstruct.h"
#include "Basic_Battle/RecordManager.h"

#include "Basic_Battle/EntityManager.h"
#include "Basic_Battle/EventDispatcher.h"


#include "Basic_Battle/FunctionPointerForDllcpp.h"

//#include "Basic_Battle/AchievementManager.h"
//#include "Basic_Battle/AIManager.h"

#include "Basic_Battle/TraceManager.h"

#include "Basic_Battle/DataLoader.h"
//#include "Basic_Battle/DataGetter.h"

#include "Basic_Battle/Robot/RobotAI_Interface.h"

#include "Basic_Battle/Robot/Bullet/BulletData.h"

#include "Basic_Battle/Robot/Bullet/Bullet.h"
#include "Basic_Battle/Robot/Bullet/B_Cannonball.h"
#include "Basic_Battle/Robot/Bullet/B_MachinegunBall.h"
#include "Basic_Battle/Robot/Bullet/B_Prism_Laser.h"
#include "Basic_Battle/Robot/Bullet/B_RPGBall.h"
#include "Basic_Battle/Robot/Bullet/B_ShotgunBall.h"
#include "Basic_Battle/Robot/Bullet/B_PlasmaBall.h"
#include "Basic_Battle/Robot/Bullet/B_Tesla_Lightning.h"
#include "Basic_Battle/Robot/Bullet/B_TrackingMissile.h"
#include "Basic_Battle/Robot/Bullet/B_ElectricSaw.h"


#include "Basic_Battle/Robot/Engine/EngineData.h"

#include "Basic_Battle/Robot/Engine/Engine.h"
#include "Basic_Battle/Robot/Engine/E_Spider.h"
#include "Basic_Battle/Robot/Engine/E_Robotman.h"
#include "Basic_Battle/Robot/Engine/E_AFV.h"
#include "Basic_Battle/Robot/Engine/E_UFO.h"


#include "Basic_Battle/Robot/Weapon/WeaponData.h"

#include "Basic_Battle/Robot/Weapon/Weapon.h"
#include "Basic_Battle/Robot/Weapon/W_Cannon.h"
#include "Basic_Battle/Robot/Weapon/W_Machinegun.h"
#include "Basic_Battle/Robot/Weapon/W_Prism.h"
#include "Basic_Battle/Robot/Weapon/W_RPG.h"
#include "Basic_Battle/Robot/Weapon/W_Shotgun.h"
#include "Basic_Battle/Robot/Weapon/W_Tesla.h"
#include "Basic_Battle/Robot/Weapon/W_PlasmaTorch.h"
#include "Basic_Battle/Robot/Weapon/W_MissileLauncher.h"
#include "Basic_Battle/Robot/Weapon/W_ElectricSaw.h"

//...


#include "Basic_Battle/Robot/Robot.h"


#include "Basic_Battle/BattleMap.h"

#include "Basic_Battle/Battlefield.h"


#include "BattleCoreOutput.h"

//#include "resource.h"



////////////////////////////
