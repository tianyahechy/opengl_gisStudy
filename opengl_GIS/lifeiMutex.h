#pragma once
#include "lifeiObject_2.h"

namespace CELL
{
	class lifeiMutex 
	{
	protected:
		//ª•≥‚ÃÂ
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