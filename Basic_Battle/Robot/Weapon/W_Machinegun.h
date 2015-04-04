#pragma once

class W_Machinegun :
	public Weapon
{
public:
	W_Machinegun(void);
	virtual ~W_Machinegun(void);

	//virtual weapontypename GetType(){return type;}
	virtual bool Fire(int mnplt);
};

