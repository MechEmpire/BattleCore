#pragma once

class W_MineLayer :
	public Weapon
{
protected:
	int coolingTime_Tiny;
	int ammoConsumption_Miner;
public:
	W_MineLayer(void);
	virtual ~W_MineLayer(void);

	virtual weapontypename GetType(){return type;}
	virtual bool Fire(int mnplt);
};