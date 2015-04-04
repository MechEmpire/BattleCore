#pragma once

class W_Tesla :
	public Weapon
{
public:
	W_Tesla(void);
	virtual ~W_Tesla(void);

	//virtual weapontypename GetType(){return WT_Tesla;}
	virtual bool Fire(int mnplt);
};

