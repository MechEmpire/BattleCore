#pragma once

//对应于MovieClip+Moving Object

//虚基类
class GameEntity
	:public BaseEntity
{
protected:
	
	shapes shapeType;		//形状类型（以此区分，这里做得不太好）
						//最好搞成枚举

	Circle circle;		//circle好像可以代替point, x,y,r
	Box box;			//矩形
	Beam beam;			//射线


	double rotation;	//角度angle °

	
	//横纵轴速度，旋转速度
	double vx;
	double vy;
	double vr;
	


public:
	GameEntity(void);
	virtual ~GameEntity(void);

	virtual void Update();		//onEnterFrame()

	Circle GetCircle()const{return circle;};
	Box GetBox()const{return box;};
	Beam GetBeam()const{return beam;}
	void GetVelocity(double&x,double&y,double&r)const{x=vx;y=vy;r=vr;};
	double GetRotation()const{return rotation;}

	double GetVX(){return vx;}
	double GetVY(){return vy;}
	double GetVR(){return vr;}

	shapes GetShape(){return shapeType;}


	void SetCircle(Circle c){circle=c;}

	void SetX(double xx){circle.x=xx;}
	void SetY(double yy){circle.y=yy;}
	void SetRotation(double rr){rotation=rr;}

	void SetVX(double vv){vx=vv;}
	void SetVY(double vv){vy=vv;}
	void SetVR(double vv){vr=vv;}

	void SetVelocity(double x,double y,double r){vx=x;vy=y;vr=r;}

	void SetShape(shapes s){shapeType=s;}

	void Init_GameEntity();		//初始化



	bool HitTest(GameEntity &);	//碰撞检测


	void SetEX(double ex){beam.ex=ex;}
	void SetEY(double ey){beam.ey=ey;}

	//事件相关
	virtual void HandleEvent(events msg,void* extraInfo)=0;
	
	static void MomentumHit(GameEntity &g1,GameEntity &g2);		//动量碰撞
	static void MomentumHit_Half(GameEntity &g1, GameEntity &g2);	//半动量碰撞，g2固定的
};

