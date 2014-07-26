#pragma once

class W_Machinegun :
	public Weapon
{
public:
	W_Machinegun(void);
	virtual ~W_Machinegun(void);

	virtual weapontypename GetType(){return WT_Machinegun;}
	virtual bool Fire(int mnplt);
};

