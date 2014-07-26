#pragma once

//¹âÀâËş
class W_Prism :
	public Weapon
{
public:
	W_Prism(void);
	virtual ~W_Prism(void);
	
	virtual weapontypename GetType(){return WT_Prism;}
	virtual bool Fire(int mnplt);
};

