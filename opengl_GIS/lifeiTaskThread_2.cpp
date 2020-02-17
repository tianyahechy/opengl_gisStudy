#include "lifeiTaskThread_2.h"
#include "lifeiTaskSystem_2.h"

namespace CELL
{
	lifeiTaskThread_2::lifeiTaskThread_2(lifeiTaskSystem_2 * pSystem)
	{
		_exitFlag = true;
		_system = pSystem;
	}

	lifeiTaskThread_2::~lifeiTaskThread_2()
	{
	}

	void lifeiTaskThread_2::join()
	{
		_exitFlag = true;
		lifeiThread_2::join();
	}

	bool lifeiTaskThread_2::onCreate()
	{
		_exitFlag = false;
		return false;
	}

	bool lifeiTaskThread_2::onRun()
	{
		while (!_exitFlag)
		{
			_system->run();
		}
		return false;
	}

	bool lifeiTaskThread_2::onDestroy()
	{
		return false;
	}

}
