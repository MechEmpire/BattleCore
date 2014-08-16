//#include "stdafx.h"
#include "../stdafx.h"
#include "DataLoader.h"


DataLoader::DataLoader():weapon_data(Weapon_Number),engine_data(Engine_Number),bullet_data(Bullet_Number)
{
	GameData=new DataVessel;
	//pLuaState=lua_open();
	pLuaState=luaL_newstate();	//linux
	luaL_openlibs(pLuaState);
	luaopen_base(pLuaState);
	luaopen_string(pLuaState);
	luaopen_table(pLuaState);
	luaopen_math(pLuaState)	;
	//luaopen_io(pLuaState);

}


DataLoader::~DataLoader()
{
	//lua_close(pLuaState);
	delete GameData;
	GameData=NULL;	
}

void DataLoader::Close()
{
	lua_close(pLuaState);
}
DataLoader* DataLoader::getInstance()
{
	static DataLoader instance;
	return &instance;
}

DataVessel* DataLoader::GetGameData()
{
	return GameData;
}


template<typename T>
bool DataLoader::GetNumber(const char* varName,T& Dest)
{
	lua_settop(pLuaState,0);
	lua_getglobal(pLuaState,varName);
	if(!lua_isnumber(pLuaState,1))
	{
		cout<<"\n[C++]:ERROR:Invalid type!\n";
		return false;
	}
	Dest=(T)lua_tonumber(pLuaState,1);
	lua_pop(pLuaState,1);
	return true;
}
bool DataLoader::GetString(const char* varName, string& Dest)
{
	lua_settop(pLuaState,0);
	lua_getglobal(pLuaState,varName);
	if(!lua_isstring(pLuaState,1))
	{
		cout<<"\n[C++]:ERROR:Invalid type!\n";
		return false;
	}
	Dest=lua_tostring(pLuaState,1);
	lua_pop(pLuaState,1);
	return true;
}

template<typename T>
bool DataLoader::GetRawi_num(int key,T& result)
{
	lua_rawgeti(pLuaState,-1,key);
	if(!lua_isnumber(pLuaState,-1))
	{
		cout<<"\n[C++]:ERROR:Invalid type!\n";
		lua_pop(pLuaState,-1);
		return false;
	}
	result=(T)lua_tonumber(pLuaState,-1);
	lua_pop(pLuaState,1);
	return true;

}

bool DataLoader::GetRawi_str(int key,string& result)
{
	lua_rawgeti(pLuaState,-1,key);
	if(!lua_isstring(pLuaState,-1))
	{
		cout<<"\n[C++]:ERROR:Invalid type!\n";
		lua_pop(pLuaState,-1);
		return false;
	}
	result=lua_tostring(pLuaState,-1);
	lua_pop(pLuaState,1);
	return true;
}

template<typename T>
bool DataLoader::SetRawi_num(int index,const T& value)
{
	
	lua_pushnumber(pLuaState,(double)value);
	lua_rawseti(pLuaState,-2,index);
	return true;
}

bool DataLoader::SetRawi_str(int index, string value)
{
	lua_pushstring(pLuaState,value.c_str());
	lua_rawseti(pLuaState,-2,index);
	return true;
}

template<typename T>
bool DataLoader::LoadNumArray(const char* arrayName, int MaxNum, T* Dest)
{
	lua_getglobal(pLuaState,arrayName);
	if(!lua_istable(pLuaState,-1))
	{
		cout<<"\n[C++]:ERROR:Invalid type!\n";
		lua_pop(pLuaState,-1);
		return false;
	}
	for(int i=0;i<MaxNum;i++)
	{
		if(!GetRawi_num(i+1,Dest[i]))
			return false;
	}
	lua_pop(pLuaState,-1);
	return true;
}

bool DataLoader::LoadStrArray(const char* arrayName, int MaxNum, string* Dest)
{
	lua_getglobal(pLuaState,arrayName);
	if(!lua_istable(pLuaState,-1))
	{
		cout<<"\n[C++]:ERROR:Invalid type!\n";
		lua_pop(pLuaState,-1);
		return false;
	}
	for(int i=0;i<MaxNum;i++)
	{
		
		if(!GetRawi_str(i+1,Dest[i]))
			return false;
	}
	lua_pop(pLuaState,-1);
	return true;
}

bool DataLoader::LoadDataFromLuaScript(const char* fileName)
{
	//打开游戏文件
	if(int error=luaL_dofile(pLuaState,fileName)!=0)
	{
		cout<<"\n[C++]: ERROR("<<error<<"): Problem with loading lua script file!\n"<<endl;
		return false;
	}
	//重置栈索引
	//lua_gettop(pLuaState);
	lua_settop(pLuaState,0);
	//加载游戏数据

	//Weapon

	LoadStrArray("name_Weapon",Weapon_Number,GameData->name_Weapon);
	//LoadNumArray("damage_Weapon",Weapon_Number,GameData->damage_Weapon);
	LoadNumArray("Ammo_Weapon",Weapon_Number,GameData->Ammo_Weapon);
	LoadNumArray("coolingTime_Weapon",Weapon_Number,GameData->coolingTime_Weapon);
	LoadNumArray("inaccuracy_Weapon",Weapon_Number,GameData->inaccuracy_Weapon);
	LoadNumArray("rotationSpeed_Weapon",Weapon_Number,GameData->rotationSpeed_Weapon);
	
	LoadNumArray("radium_Weapon",Weapon_Number,GameData->radium_Weapon);
	
	GetNumber("coolingSpeed_AllWeapon",GameData->coolingSpeed_AllWeapon);

	GetNumber("burst_Shotgun",GameData->burst_Shotgun);
	GetNumber("gapRotation_Shotgun",GameData->gapRotation_Shotgun);

	GetNumber("coolingTime_Tiny_MineLayer",GameData->coolingTime_Tiny_MineLayer);
	GetNumber("ammoConsumption_Mine_MineLayer",GameData->ammoConsumption_Mine_MineLayer);
	//Bullet

	GetNumber("bounce_time",GameData->bounce_time);

	LoadStrArray("name_Bullet",Bullet_Number,GameData->name_Bullet);
	LoadNumArray("speed_Bullet",Bullet_Number,GameData->speed_Bullet);
	LoadNumArray("damage_Bullet",Bullet_Number,GameData->damage_Bullet);
	LoadNumArray("flyTime_Bullet",Bullet_Number,GameData->flyTime_Bullet);

	GetNumber("explodeR_RPGBall",GameData->explodeR_RPGBall);
	GetNumber("acceleration_RPGBall",GameData->acceleration_RPGBall);

	GetNumber("explodeR_Grenade",GameData->explodeR_Grenade);

	GetNumber("explodeR_Mine",GameData->explodeR_Mine);

	GetNumber("spinSpeed_TrackingMissile",GameData->spinSpeed);




	//Engine

	LoadStrArray("name_Engine",Engine_Number,GameData->name_Engine);
	LoadNumArray("maxSpeed_Engine",Engine_Number,GameData->maxSpeed_Engine);
	LoadNumArray("maxHp_Engine",Engine_Number,GameData->maxHp_Engine);
	LoadNumArray("rotationSpeed_Engine",Engine_Number,GameData->rotationSpeed_Engine);
	LoadNumArray("acceleration_Engine",Engine_Number,GameData->acceleration_Engine);

	LoadNumArray("radium_Engine",Engine_Number,GameData->radium_Engine);

	GetNumber("radium_Arsenal",GameData->radium_Arsenal);
	GetNumber("respawningTime_Arsenal",GameData->respawningTime_Arsenal);

	Close();

	//construct weapon,engine static data vector
	ConstructDataVector();


	return true;
}

void DataLoader::ConstructDataVector()
{
	//vector<WeaponData>::iterator iter;
	int i;
	for(i=0;i<Weapon_Number;i++)
	{
		weapon_data.at(i).LoadStaticData((weapontypename)i);
	}
	for(i=0;i<Engine_Number;i++)
	{
		engine_data.at(i).LoadStaticData((enginetypename)i);
	}
	for(i=0;i<Bullet_Number;i++)
	{
		bullet_data.at(i).LoadStaticData((bullettypename)i);
	}
}

WeaponData& DataLoader::getWeaponData(weapontypename wtn)
{
	WeaponData& w=weapon_data.at((int)wtn);
	return w;
}
EngineData& DataLoader::getEngineData(enginetypename etn)
{
	EngineData& e=engine_data.at((int)etn);
	return e;
}
BulletData& DataLoader::getBulletData(bullettypename btn)
{
	BulletData& b=bullet_data.at((int)btn);
	return b;
}