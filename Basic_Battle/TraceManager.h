#pragma once
#include "BaseEntity.h"
/*
AI输出调试信息的管理器
仿照流的形式，缓冲存储每一帧输出的调试信息
当一帧结束时输出给窗口，并清空缓存

与trace_global联合使用
*/

//单例模式
#define pTraceManager TraceManager::Instance()


class TraceManager
	:public BaseEntity
{
private:
	string text;


	TraceManager();
	virtual ~TraceManager();


public:
	static TraceManager* Instance();

	void AddText(string t);
	string OutputText();

	void Clear();

	virtual void HandleEvent(events msg,void* extraInfo);
};