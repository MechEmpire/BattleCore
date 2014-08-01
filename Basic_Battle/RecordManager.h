#pragma once


#define FRAME_NUM 10000

#define pRecordManager RecordManager::Instance()

class RecordManager :
	public BaseEntity
{
private:
	string fileType;	//文件后缀名
	string fileName;	//当前录像名称

	string fileRoute;	//路径
	string fileRoute_Final;	//最终路径

	ofstream f;			//文档
	

	int hitID;			//当前帧hitInfo的下标

	int currentFrame;

	Record_FrameInformation frameInfo[FRAME_NUM];


	RecordManager(void);
	virtual ~RecordManager(void);
public:
	static RecordManager* Instance();

	void Init();		//初始化

	void Update_FrameInfo(RobotAI_BattlefieldInformation&);

	void NextFrame(){currentFrame+=1;}

	void SetFileName(string s){fileName=s;}

	void BuildFileRoute(){fileRoute_Final=fileRoute+fileName+fileType;}

	virtual void HandleEvent(events msg,void* extraInfo);

	void ReleaseRecord(int winner);	//生成录像文件

	void EnterFrame_Init();

	int GetCurFrame(){return currentFrame;}
};

