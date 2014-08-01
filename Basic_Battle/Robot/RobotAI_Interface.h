#pragma once

using namespace std;


typedef void (*FP_TRACE)(string);
typedef string (*FP_GET_STRING_W)(weapontypename);
typedef int (*FP_GET_INT_W)(weapontypename);
typedef double (*FP_GET_DOUBLE_W)(weapontypename);
typedef string (*FP_GET_STRING_E)(enginetypename);
typedef int (*FP_GET_INT_E)(enginetypename);
typedef double (*FP_GET_DOUBLE_E)(enginetypename);
typedef string (*FP_GET_STRING_B)(bullettypename);
typedef int (*FP_GET_INT_B)(bullettypename);
typedef double (*FP_GET_DOUBLE_B)(bullettypename);

//#define TRACE (*trace)

#define get_weapon_name (*getWeaponName)
#define get_weapon_damage (*getWeaponDamage)
#define get_weapon_ammo (*getWeaponAmmo)
#define get_weapon_coolingTime (*getWeaponCoolingTime)
#define get_weapon_inaccuracy (*getWeaponInaccuracy)
#define get_weapon_rotationSpeed (*getWeaponRotationSpeed)
#define get_engine_name (*getEngineName)
#define get_engine_maxSpeed (*getEngineMaxSpeed)
#define get_engine_maxHp (*getEngineMaxHp)
#define get_engine_rotationSpeed (*getEngineRotationSpeed)
#define get_engine_acceleration (*getEngineAcceleration)
#define get_bullet_name (*getBulletName)
#define get_bullet_speed (*getBulletSpeed)
#define get_bullet_damage (*getBulletDamage)


//接口
class RobotAI_Interface
{
public:
	virtual ~RobotAI_Interface(){};


	//必须完成的方法
	//每个回合（帧）的操纵方法
	virtual void Update(RobotAI_Order& , const RobotAI_BattlefieldInformation&, int)=0;
	//选择装备方法（载入时调用，进入军火库调用）
	virtual void ChooseArmor(weapontypename&,enginetypename&,bool)=0;
	

	virtual string GetName()=0;
	virtual string GetAuthor()=0;

	//颜色样式改变器
	virtual int GetWeaponRed()=0;
	virtual int GetWeaponGreen()=0;
	virtual int GetWeaponBlue()=0;

	virtual int GetEngineRed()=0;
	virtual int GetEngineGreen()=0;
	virtual int GetEngineBlue()=0;
	///////////////////////////////////////


	//可供选择的功能方法
	//virtual string trace()=0;		//输出调试信息函数(这种方式不方便，争取做成个什么函数指针啥的)
	//void (*trace)(string);			//输出调试信息函数指针
	FP_TRACE trace;					//输出调试信息函数指针
									//调用时	(*trace)("info needed to be print")

									//赋值时：全局函数	trace=trace_global;
	//StaticDataGetter
	//weapon
	FP_GET_STRING_W getWeaponName;
	FP_GET_INT_W getWeaponDamage;
	FP_GET_INT_W getWeaponAmmo;
	FP_GET_INT_W getWeaponCoolingTime;
	FP_GET_DOUBLE_W getWeaponInaccuracy;
	FP_GET_DOUBLE_W getWeaponRotationSpeed;
	//engine
	FP_GET_STRING_E getEngineName;
	FP_GET_DOUBLE_E getEngineMaxSpeed;
	FP_GET_INT_E getEngineMaxHp;
	FP_GET_DOUBLE_E getEngineRotationSpeed;
	FP_GET_DOUBLE_E getEngineAcceleration;
	//bullet
	FP_GET_STRING_B getBulletName;
	FP_GET_DOUBLE_B getBulletSpeed;
	FP_GET_INT_B getBulletDamage;
	FP_GET_INT_B getBulletFlyTime;
	/////////////////////////////////////////////


	//Trigger Function
	virtual void onBattleStart(const RobotAI_BattlefieldInformation&,int)=0;		//一场战斗开始时被调用
	virtual void onBattleEnd(const RobotAI_BattlefieldInformation&,int)=0;			//一场战斗结束时被调用

	//这里还要加一些触发方法,应该要保证一定冗余
	//virtual void onReceiveDamage(..)=0		//被击中时调用
	
	virtual void onHit(int,bullettypename)=0;		//被击中时调用
};