#pragma once


//÷©÷Î Ω

class E_Spider :
	public Engine
{
public:
	E_Spider(enginetypename t=ET_Spider);
	virtual ~E_Spider(void);

	virtual enginetypename GetType(){return type;}
	virtual bool Run(int);
	virtual bool Turn(int);
};

