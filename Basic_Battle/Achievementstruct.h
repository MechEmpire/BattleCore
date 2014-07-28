#pragma once


//统计数据
#define MAX_INT 99999

//一个机甲：单场战斗的成就统计数据
class AchievementData_Battle
{
public:
	//int index;	//对应Battlefield中pRobot下标
	//没必要，pAchievmentData和pRobot的下标本就是对应的

	int fire;	//开火次数
	int hit;	//命中次数
	int damage;	//受到伤害
	int output;	//输出伤害

	//武器，引擎时间比例（这个更新起来拖速度吧）
	//...
	//存活时间，行走距离,...


	
	//temp
	void Print()
	{
		cout<<"Fire:"<<fire<<'\n'
			<<"Hit:"<<hit<<'\n'
			<<"Damage:"<<damage<<'\n'
			<<"Output:"<<output<<'\n';
	}

	void Out(ostream& out)
	{
		out<<fire<<','
			<<hit<<','
			<<damage<<','
			<<output;
	}



	void Add_Fire(){fire++;}
	void Add_hit(){hit++;}
	void Add_damage(int d){damage+=d;}
	void Add_output(int o){output+=o;}



	void Init()
	{
		fire=0;
		hit=0;
		damage=0;
		output=0;
	}


	AchievementData_Battle()
	{
		Init();
	}

	void Calculate_Avg(AchievementData_Battle& a,int battles)
	{
		//计算各参数的平均值
		fire=a.fire/battles;
		hit=a.hit/battles;
		damage=a.damage/battles;
		output=a.output/battles;
	}

	int bigger(int x,int y)
	{
		//返回较大值
		if(x>=y)
		{
			return x;
		}
		return y;
	}

	int smaller(int x,int y)
	{
		//返回较小值
		if(x<=y)
		{
			return x;
		}
		return y;
	}

	void Update_Best(AchievementData_Battle& a)
	{
		//最佳更新
		fire=bigger(fire,a.fire);
		hit=bigger(hit,a.hit);
		damage=smaller(damage,a.damage);
		output=bigger(output,a.output);
	}

	

	void Add(AchievementData_Battle& a)
	{
		//两个AchievementData_Battle相加
		fire+=a.fire;
		hit+=a.hit;
		damage+=a.damage;
		output+=a.output;
	}
};









//对一个AI而言
class AchievementData
{
public:
	//int index;		//在AIManager :: pAI中的下标


	//global --total
	int battle;		//战斗场次
	int win;		//胜利场次
	int lose;		//失败场次

	//rate	
	double win_rate;	//胜率
	double hit_rate;//命中率


	AchievementData_Battle data_global;

	AchievementData_Battle data_avg;

	AchievementData_Battle data_best;


	
	
	void Out(ostream& out)
	{
		out<<battle<<','
			<<win<<','
			<<lose<<','
			<<win_rate<<','
			<<hit_rate<<'|';
		data_global.Out(out);
		out<<'|';
		data_avg.Out(out);
		out<<'|';
		data_best.Out(out);
		out<<'|';
	}
	


	void Init()
	{
		//初始化
		battle=0;
		win=0;		//胜利场次
		lose=0;		//失败场次
		//rate	
		win_rate=0;	//胜率
		hit_rate=0;//命中率

		data_global.Init();
		data_avg.Init();
		data_best.Init();
		data_best.damage=MAX_INT;
	}

	AchievementData(/*int in*/)//:data_global(),data_avg(),data_max()
	{
		//index=in;		//该条目对应的AI在AIManager::pAI中的下标
		Init();
	}

	
	void Add_Battle(AchievementData_Battle& a,bool w)
	{
		//添加新一场战斗数据
		data_global.Add(a);
		data_best.Update_Best(a);
		battle+=1;
		
		if(w)
		{
			win+=1;
		}
		else
		{
			lose+=1;
		}
	}

	void Calculate()
	{
		//计算更新
		data_avg.Calculate_Avg(data_global,battle);		//场均数据
		win_rate=(double)win/(double) battle;
		if(data_global.fire>0)
		{
			hit_rate=(double)data_global.hit/(double)data_global.fire;
		}
		else
		{
			hit_rate=0;
		}
	}



	//l-less  g-greater  e-equal
	//a在b之前<=>true
	static bool g_battle(AchievementData * a,AchievementData * b)
	{
		return a->battle>b->battle;
	}

	//胜率降序
	static bool g_win_rate(AchievementData  * a,AchievementData * b)
	{
		return a->win_rate>b->win_rate;
	}

	//命中率降序
	static bool g_hit_rate(AchievementData * a,AchievementData * b)
	{
		return a->hit_rate>b->hit_rate;
	}


	//单场最佳命中
	static bool g_hit_best(AchievementData* a,AchievementData* b)
	{
		return a->data_best.hit>b->data_best.hit;
	}
};