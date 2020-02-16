#include "lifeiThread_2.h"

namespace CELL
{
	lifeiThread_2::lifeiThread_2()
	{
		_thread = 0;
	}

	lifeiThread_2::~lifeiThread_2()
	{
		join();
	}

	DWORD lifeiThread_2::threadId() const
	{
		return _threadId;
	}

	bool lifeiThread_2::isRun() const
	{
		return _thread != 0;
	}

	bool lifeiThread_2::onCreate()
	{
		return false;
	}

	bool lifeiThread_2::onRun()
	{
		return false;
	}

	bool lifeiThread_2::onDestroy()
	{
		return false;
	}

	bool lifeiThread_2::start()
	{
		if ( NULL != _thread)
		{
			return false;
		}
		_thread = CreateThread(0, 0, &lifeiThread_2::threadEnter, this, HIGH_PRIORITY_CLASS, &_threadId);
		return true;
	}

	void lifeiThread_2::join()
	{
		if (NULL == _thread)
		{
			return;
		}
		WaitForSingleObject(_thread, 0xFFFFFFFF);
		CloseHandle(_thread);
		_thread = 0;
	}

	void lifeiThread_2::close()
	{
		CloseHandle(_thread);
		_thread = 0;
	}

	unsigned long lifeiThread_2::threadEnter(void * ptr)
	{
		lifeiThread_2 * pThis = (lifeiThread_2*)ptr;
		if (pThis)
		{
			pThis->onCreate();
			pThis->onRun();
			pThis->onDestroy();
		}
		return 0;
	}

}
