#pragma once
#include "lifeiThread.h"
namespace CELL
{
	class lifeiTaskSystem;
	class lifeiTaskThread : public lifeiThread
	{
	public:
		lifeiTaskThread(lifeiTaskSystem* pSystem);
		~lifeiTaskThread();
	public:
		//退出标志
		bool _exitFlag;
		lifeiTaskSystem* _system;

		//退出
		virtual void join();
		virtual bool onCreate();
		virtual bool onRun();
		virtual bool onDestroy();
	};

}

