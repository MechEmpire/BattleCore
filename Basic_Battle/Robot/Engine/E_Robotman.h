#pragma once


//人形机甲引擎(Robotman这个类名起得不好)
class E_Robotman :
	public Engine
{
public:
	E_Robotman(enginetypename t = ET_Robotman);
	virtual ~E_Robotman(void);


	virtual enginetypename GetType(){return type;}
	virtual bool Run(int);
	virtual bool Turn(int);
};

