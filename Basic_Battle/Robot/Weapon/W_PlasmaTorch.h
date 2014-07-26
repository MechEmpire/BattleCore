#pragma once

class W_PlasmaTorch :
	public Weapon
{
public:
	W_PlasmaTorch(void);
	virtual ~W_PlasmaTorch(void);

	virtual weapontypename GetType(){return WT_PlasmaTorch;}
	virtual bool Fire(int mnplt);
};