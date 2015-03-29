#pragma once


//AFV: armored fighting vehicle
//×°¼×Õ½³µ


class E_AFV :
	public Engine
{
public:
	E_AFV(enginetypename t=ET_AFV);
	virtual ~E_AFV(void);

	virtual enginetypename GetType(){return type;}

	virtual bool Run(int);
	virtual bool Turn(int);
};

