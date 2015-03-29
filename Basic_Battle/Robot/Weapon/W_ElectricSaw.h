#pragma once

class W_ElectricSaw :
	public Weapon
{
public:
	W_ElectricSaw(void);
	virtual ~W_ElectricSaw(void);

	virtual weapontypename GetType(){return type;}
	virtual bool Fire(int mnplt);
};