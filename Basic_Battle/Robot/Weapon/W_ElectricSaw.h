#pragma once

class W_ElectricSaw :
	public Weapon
{
public:
	W_ElectricSaw(void);
	virtual ~W_ElectricSaw(void);

	virtual weapontypename GetType(){return WT_ElectricSaw;}
	virtual bool Fire(int mnplt);
};