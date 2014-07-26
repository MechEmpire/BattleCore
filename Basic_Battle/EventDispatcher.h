#pragma once



#define pDispatcher EventDispatcher::Instance()
//单例模式
class EventDispatcher
{
private:
	EventDispatcher(void);
	~EventDispatcher(void);

public:
	static EventDispatcher* Instance();

	//发送消息，为求简单，先不搞延时
	void DispatchEvent(int sender,int recevier,events msg,void* extraInfo);
};

