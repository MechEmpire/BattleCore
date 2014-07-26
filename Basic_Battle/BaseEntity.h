#pragma once
class BaseEntity
{
protected:
	int ID;			//

public:
	BaseEntity(void);
	virtual ~BaseEntity(void);

	void SetID(int s){ID=s;}
	int GetID(){return ID;}

	virtual void HandleEvent(events msg,void* extraInfo)=0;
};

