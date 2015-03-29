#pragma once

class E_UFO :
	public Engine
{
public:
	E_UFO(enginetypename t = ET_UFO);
	virtual ~E_UFO(void);


	virtual enginetypename GetType(){return type;}
	virtual bool Run(int);
	virtual bool Turn(int);
};

