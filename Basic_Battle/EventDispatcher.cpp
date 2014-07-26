//#include "stdafx.h"
#include "../stdafx.h"
#include "EventDispatcher.h"


EventDispatcher::EventDispatcher(void)
{
}


EventDispatcher::~EventDispatcher(void)
{
}


EventDispatcher* EventDispatcher::Instance()
{
	
	static EventDispatcher instance;

	return &instance;
}


void EventDispatcher::DispatchEvent(int sender,int recevier,events msg,void* extraInfo)
{
	BaseEntity* pReceiver=pmngr->GetEntityFromID(recevier);
	if(pReceiver!=NULL)
	{
		//·¢ËÍÊÂ¼þ
		pReceiver->HandleEvent(msg,extraInfo);
	}
}