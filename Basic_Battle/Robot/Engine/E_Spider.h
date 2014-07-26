#pragma once


//÷©÷Î Ω

class E_Spider :
	public Engine
{
public:
	E_Spider(void);
	virtual ~E_Spider(void);

	virtual enginetypename GetType(){return ET_Spider;}
	virtual bool Run(int);
	virtual bool Turn(int);
};

