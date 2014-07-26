#pragma once

class W_Cannon :
	public Weapon
{
public:
	W_Cannon(void);
	virtual ~W_Cannon(void);

	virtual weapontypename GetType(){return WT_Cannon;}
	virtual bool Fire(int mnplt);
};