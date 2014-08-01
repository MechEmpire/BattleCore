#ifndef HEAD_EVENTTYPENAME
#define HEAD_EVENTTYPENAME

enum events{
	Add_Bullet
	,Remove_Bullet
	,Explode
	,Prism_Laser
	,Tesla_Lightning

	,Event_BulletHitTestAllBullet

	
	,Round_Start
	,Round_End
	,Battle_Start
	,Battle_End

	//Record related
	,R_RobotInfo,R_BulletInfo//此二事件已无用
	////////////
	
	,R_Fire
	,R_WeaponTurn
	,R_Run
	,R_EngineTurn
	,R_HitInfo

};


#endif