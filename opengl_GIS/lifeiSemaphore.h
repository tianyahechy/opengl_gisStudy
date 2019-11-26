#pragma once
#include "lifeiPlatform.h"
#include "lifeiObject.h"

#if LIFEI_PLATFORM == CELL_PLATFORM_WIN32
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
#elif LIFEI_PLATFORM == CELL_PLATFORM_LINUX
namespace CELL
{
	class lifeiSemaphore
	{
	protected:
		sem_t _semaphore;
	public:
		lifeiSemaphore(long lMax = 0x7FFFFFFF, long lInit = 1)
		{
			sem_init(&_semaphore, lInit, lMax);
		}
		virtual ~lifeiSemaphore()
		{
			destroy();
		}

		virtual void create(long lMax = 0x7FFFFFFF, long lInit = 1)
		{
			destroy();
			sem_init(&_semaphore, lInit, lMax);
		}

		//消费信号量
		virtual bool wait(unsigned long ms = INFINITE)
		{
			struct timespec abstime;
			struct timeval tv;
			gettimeofday(&tv, 0);
			abstime.tv_sec = tv.tv_sec + ms / 1000;
			abstime.tv_nsec = tv.tv_usec * 1000 + (ms % 1000) * 1000000;
			if (abstime.tv_nsec >= 1000000000)
			{
				abstime.tv_nsec -= 1000000000;
				abstime.tv_sec++;
			}
			return sem_timedwait(&_semaphore, abstime) == 0;
		}
		//释放信号量
		virtual bool set(long number = 1)
		{
			bool res = true;
			for (long i = 0; i < number; ++i)
			{
				if (sem_post(&_semaphore) != 0)
				{
					res = false;
					break;
				}
			}
			return res;
		}

		//销毁
		virtual void destroy()
		{
			sem_destroy(&_semaphore);
		}
	};
}
#endif