#pragma once
#include "lifeiObject_2.h"
#include <Windows.h>

namespace CELL
{
	class lifeiMutex_2
	{
	protected:
		//ª•≥‚ÃÂ
		CRITICAL_SECTION _cs;

	public:
		lifeiMutex_2()
		{
			::InitializeCriticalSection(&_cs);
		}
		~lifeiMutex_2()
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
	public:
		class ScopeLock
		{
		protected:
			//ª•≥‚ÃÂ
			lifeiMutex_2& _mutex;

		public:
			ScopeLock(lifeiMutex_2& mutex)
				: _mutex(mutex)
			{
				_mutex.lock();
			}
			~ScopeLock()
			{
				_mutex.unlock();
			}
		};
	};
}
