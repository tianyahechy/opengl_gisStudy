#include "lifeiSemaphore_2.h"

namespace CELL
{
	lifeiSemaphore_2::lifeiSemaphore_2(long lMax, long lInit)
	{
		_semaphore = ::CreateSemaphore(0, lInit, lMax, 0);
	}

	lifeiSemaphore_2::~lifeiSemaphore_2()
	{
		CloseHandle(_semaphore);
		_semaphore = 0;
	}

	void lifeiSemaphore_2::create(long lMax, long lInit)
	{
		destroy();
		_semaphore = ::CreateSemaphore(0, lInit, lMax, 0);
	}

	bool lifeiSemaphore_2::wait(unsigned long ms)
	{
		switch (WaitForSingleObject(_semaphore, ms))
		{
		case WAIT_OBJECT_0:
			return true;
		case WAIT_TIMEOUT:
			return false;
		default:
			return false;
		}
	}

	bool lifeiSemaphore_2::set(long number)
	{
		 
		return ReleaseSemaphore(_semaphore, number, 0);
	}

	void lifeiSemaphore_2::destroy()
	{
		CloseHandle(_semaphore);
		_semaphore = 0;
	}

}
