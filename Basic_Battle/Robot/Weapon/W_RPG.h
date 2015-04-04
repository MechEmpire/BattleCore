#pragma once

class W_RPG :
	public Weapon
{
public:
	W_RPG(void);
	virtual ~W_RPG(void);
	
	//virtual weapontypename GetType(){return WT_RPG;}
	virtual bool Fire(int mnplt);
};

