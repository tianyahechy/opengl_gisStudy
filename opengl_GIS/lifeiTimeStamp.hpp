#pragma once
#include "lifeiPlatform.h"
#if  LIFEI_PLATFORM == CELL_PLATFORM_WIN32
namespace CELL
{
	class lifeiTimeStamp
	{
	private:
		LARGE_INTEGER	_frequency;
		LARGE_INTEGER	_startCount;
	public:
		lifeiTimeStamp()
		{
			QueryPerformanceFrequency(&_frequency);
			QueryPerformanceCounter(&_startCount);
		}
		~lifeiTimeStamp()
		{
			QueryPerformanceCounter(&_startCount);
		}
		void update()
		{
			QueryPerformanceCounter(&_startCount);
		}
		//获取微秒
		double getElapsedTimeInMicroSec()
		{
			LARGE_INTEGER endCount;
			QueryPerformanceCounter(&endCount);
			double startTimeInMicroSec = _startCount.QuadPart * (1000000.0 / _frequency.QuadPart);
			double endTimeInMicroSec = endCount.QuadPart * (1000000.0 / _frequency.QuadPart);
			return endTimeInMicroSec - startTimeInMicroSec;
		}
		//获取毫秒
		double getElapsedTimeInMilliSec()
		{
			return this->getElapsedTimeInMicroSec() * 0.001;
		}
		//获取当前秒
		double getElapsedSecond()
		{
			return this->getElapsedTimeInMicroSec() * 0.000001;
		}
		
	};
}
#elif LIFEI_PLATFORM == CELL_PLATFORM_LINUX
namespace CELL
{
	class lifeiTimeStamp
	{
	protected:
		timeval _startCount;
		lifeiTimeStamp()
		{
			gettimeofday(&_startCount, NULL);
		}
		~lifeiTimeStamp()
		{

		}
		void update()
		{
			gettimeofday(&_startCount, NULL);
		}
		//获取微秒
		double getElapsedTimeInMicroSec()
		{
			timeval endCount;
			gettimeofday(&endCount, NULL);
			double startTimeInMicroSec = (_startCount.tv_sec * 1000000.0) + _startCount.tv_usec;
			double endTimeInMicroSec = (endCount.tv_sec * 1000000.0) + endCount.tv_usec;
			return endTimeInMicroSec - startTimeInMicroSec;
		}
	};
}


#endif //  LIFEI_PLATFORM == CELL_PLATFORM_WIN32

