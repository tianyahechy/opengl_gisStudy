#pragma once
#include "lifeiPlatform.h"
#include "lifeiObject.h"

#if LIFEI_PLATFORM == CELL_PLATFORM_WIN32
namespace CELL
{
	class lifeiMutex 
	{
	protected:
		//»¥³âÌå
		CRITICAL_SECTION _cs;
	public:
		class ScopeLock
		{
		protected:
			lifeiMutex& _mutex;
		public:
			ScopeLock(lifeiMutex& mutex)
				: _mutex( mutex)
			{
				_mutex.lock();
			}
			~ScopeLock()
			{
				_mutex.unlock();
			}

		private:
			ScopeLock(const ScopeLock&);
			void operator = (const ScopeLock&);
		};
	public:
		lifeiMutex()
		{
			::InitializeCriticalSection(&_cs);
		}
		~lifeiMutex()
		{
			::DeleteCriticalSection(&_cs);
		}

		void lock()
		{
			::EnterCriticalSection(&_cs);
		}

		void unlock()
		{
			::LeaveCriticalSection(&_cs);
		}
		bool tryLock()
		{
			return TryEnterCriticalSection(&_cs) == TRUE;
		}
	};
}
#elif LIFEI_PLATFORM == CELL_PLATFORM_LINUX
namespace CELL
{
	class lifeiMutex : public lifeiObject
	{
	protected:
		//»¥³âÌå
		pthread_mutex_t _mutex;
	public:
		class ScopeLock
		{
		protected:
			lifeiMutex& _mutex;
		public:
			ScopeLock(lifeiMutex& mutex)
				: _mutex(mutex)
			{
				_mutex.lock();
			}
			~ScopeLock()
			{
				_mutex.unlock();
			}
		private:
			ScopeLock(const ScopeLock&);
			void operator = (const ScopeLock&);
		};
	public:
		lifeiMutex()
		{
			pthread_mutexattr_t attr;
			pthread_mutexattr_init(&attr);
			if (pthread_mutex_init(&_mutex, &attr))
			{
				pthread_mutexattr_destroy(&attr);
			}
			pthread_mutexattr_destroy(&attr);
		}
		virtual ~lifeiMutex()
		{
			pthread_mutex_destroy(&_mutex);
		}

		void lock()
		{
			int rc = pthread_mutex_lock(&_mutex);
			assert(rc == 0);
		}

		void unlock()
		{
			int rc = pthread_mutex_unlock(&_mutex);
			assert(rc == 0);
		}
		bool tryLock()
		{
			struct timespec abstime;
			struct timeval tv;
			gettimeofday(&tv, 0);
			abstime.tv_sec = tv.tv_sec;
			abstime.tv_nsec = tv.tv_usec * 1000 + 10000;
			if (abstime.tv_nsec >= 1000000000)
			{
				abstime.tv_nsec -= 1000000000;
				abstime.tv_sec++;
			}
			int rc = pthread_mutex_timedlock(&_mutex, &abstime);
			if (rc == 0)
			{
				return true;
			}
			else if (rc == ETIMEDOUT)
			{
				return false;
			}
			else
			{
				assert(rc == 0);
				return false;
			}
		}
	};
}
#endif