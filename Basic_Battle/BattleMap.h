#pragma once

class BattleMap
{
protected:
	double B_Left;
	double B_Right;
	double B_Up;
	double B_Down;
	Box boundary;		//战场边界是个矩形
	int num_obstacle;
	vector<Obstacle*> pObstacle;		//障碍物
	Point birthPoint[Info_MaxRobots];		//出生点
	int num_arsenal;
	vector<Arsenal*> pArsenal;			//军火库
public:
	BattleMap();
	~BattleMap();

	void ConstructMap_Default();


	//construct map according to map config
	void ConstructMap_Config(const char *);
};