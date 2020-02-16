#pragma once
#include "lifeiPlatform.h"
#include "lifeiObject_2.h"

namespace CELL
{
	class lifeiSemaphore 
	{
	protected:
		HANDLE _semaphore;
	public:
		lifeiSemaphore(long lMax = 0x7FFFFFFF, long lInit = 1)
		{
			_semaphore = ::CreateSemaphore(0, lInit, lMax, 0);
		}
		virtual ~lifeiSemaphore()
		{
			CloseHandle(_semaphore);
			_semaphore = 0;
		}
		
		virtual void create(long lMax = 0x7FFFFFFF, long lInit = 1)
		{
			destroy();
			_semaphore = ::CreateSemaphore(0, lInit, lMax, 0);
		}

		//消费信号量
		virtual bool wait(unsigned long ms = INFINITE)
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
		//释放信号量
		virtual bool set(long number = 1)
		{
			return ReleaseSemaphore(_semaphore, number, 0) == TRUE;
		}
		
		//销毁
		virtual void destroy()
		{
			CloseHandle(_semaphore);
			_semaphore = 0;
		}
	};
}