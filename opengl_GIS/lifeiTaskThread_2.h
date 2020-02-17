#pragma once
#include "lifeiThread_2.h"
namespace CELL
{
	class lifeiTaskSystem_2;
	class lifeiTaskThread_2 : public lifeiThread_2
	{
	public:
		lifeiTaskThread_2(lifeiTaskSystem_2* pSystem);
		~lifeiTaskThread_2();

	public:
		//退出标志
		bool _exitFlag;
		//要求的瓦片名称集合所在的系统
		lifeiTaskSystem_2* _system;

		//退出
		virtual void join();
		virtual bool onCreate();
		virtual bool onRun();
		virtual bool onDestroy();
	};
}
