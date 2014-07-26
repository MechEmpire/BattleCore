#pragma once

class Obstacle :
	public GameEntity
{
public:
	Obstacle(void);
	virtual ~Obstacle(void);

	void SetR(double r){circle.r=r;}

	virtual void HandleEvent(events msg,void* extraInfo){}
};

