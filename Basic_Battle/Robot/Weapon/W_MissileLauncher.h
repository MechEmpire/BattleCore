#pragma once

class W_MissileLauncher :
	public Weapon
{
public:
	W_MissileLauncher(void);
	virtual ~W_MissileLauncher(void);

	//virtual weapontypename GetType(){return WT_MissileLauncher;}
	virtual bool Fire(int mnplt);
};