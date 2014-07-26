#pragma once

class E_UFO :
	public Engine
{
public:
	E_UFO(void);
	virtual ~E_UFO(void);


	virtual enginetypename GetType(){return ET_UFO;}
	virtual bool Run(int);
	virtual bool Turn(int);
};

