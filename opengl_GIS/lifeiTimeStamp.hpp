#pragma once
#include "export.h"

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
