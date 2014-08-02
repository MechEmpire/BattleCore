#pragma once

class W_GrenadeThrower :
	public Weapon
{
public:
	W_GrenadeThrower(void);
	virtual ~W_GrenadeThrower(void);

	virtual weapontypename GetType(){return WT_GrenadeThrower;}
	virtual bool Fire(int mnplt);
};