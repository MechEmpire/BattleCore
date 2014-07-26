#pragma once


//AFV: armored fighting vehicle
//×°¼×Õ½³µ


class E_AFV :
	public Engine
{
public:
	E_AFV(void);
	virtual ~E_AFV(void);

	virtual enginetypename GetType(){return ET_AFV;}

	virtual bool Run(int);
	virtual bool Turn(int);
};

