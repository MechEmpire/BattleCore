#pragma once

class W_Cannon :
	public Weapon
{
private:
	//weapontypename type;
public:
	W_Cannon(weapontypename t=WT_Cannon);
	virtual ~W_Cannon(void);

	virtual weapontypename GetType(){return type;}
	virtual bool Fire(int mnplt);
};