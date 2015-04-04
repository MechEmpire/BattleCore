#pragma once

class W_Shotgun :
	public Weapon
{
protected:
	static int burst;		//一次射出几发子弹(读脚本)(奇数)
	static double gapRotation;	//两颗子弹间隔角度

public:
	W_Shotgun(void);
	virtual ~W_Shotgun(void);
	
	//virtual weapontypename GetType(){return WT_Shotgun;}
	virtual bool Fire(int mnplt);
};

