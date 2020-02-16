#include "lifeiTaskThread.h"
#include "lifeiTaskSystem.h"

namespace CELL
{
	lifeiTaskThread::lifeiTaskThread(lifeiTaskSystem* pSystem)
	{
		_exitFlag = true;
		_system = pSystem;
	}

	lifeiTaskThread::~lifeiTaskThread()
	{
	}
	//ÍË³ö
	void lifeiTaskThread::join()
	{
		_exitFlag = true;
		lifeiThread_2::join();
	}

	bool lifeiTaskThread::onCreate()
	{
		_exitFlag = false;
		return false;
	}

	bool lifeiTaskThread::onRun()
	{
		while (!_exitFlag)
		{
			_system->run();
		}
		return false;
	}
	bool lifeiTaskThread::onDestroy()
	{
		return false;
	}

}
