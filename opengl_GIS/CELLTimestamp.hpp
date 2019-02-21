#pragma once

#include "CELLPlatform.hpp"

#if CELL_PLATFORM == CELL_PLATFORM_WIN32

namespace   CELL
{
    class CELLTimestamp
    {
    public:
        CELLTimestamp()
        {
            QueryPerformanceFrequency(&_frequency);
            QueryPerformanceCounter(&_startCount);
        }
        ~CELLTimestamp()
        {}

        void    update()
        {
            QueryPerformanceCounter(&_startCount);
        }
        /**
        *   获取当前秒
        */
        double getElapsedSecond()
        {
            return  getElapsedTimeInMicroSec() * 0.000001;
        }
        /**
        *   获取毫秒
        */
        double getElapsedTimeInMilliSec()
        {
            return this->getElapsedTimeInMicroSec() * 0.001;
        }
        /**
        *   获取微妙
        */
        double getElapsedTimeInMicroSec()
        {
            LARGE_INTEGER endCount;
            QueryPerformanceCounter(&endCount);

            double  startTimeInMicroSec =   _startCount.QuadPart * (1000000.0 / _frequency.QuadPart);
            double  endTimeInMicroSec   =   endCount.QuadPart * (1000000.0 / _frequency.QuadPart);

            return  endTimeInMicroSec - startTimeInMicroSec;
        }
    protected:
        LARGE_INTEGER   _frequency;
        LARGE_INTEGER   _startCount;
    };
}

#elif CELL_PLATFORM == CELL_PLATFORM_LINUX

namespace   CELL
{
    class CELLTimestamp
    {
    public:
        CELLTimestamp()
        {
            gettimeofday(&_startCount, NULL);
        }
        ~CELLTimestamp()
        {}

        void    update()
        {
            gettimeofday(&_startCount, NULL);
        }
        /**
        *   获取当前秒
        */
        double getElapsedSecond()
        {
            return  getElapsedTimeInMicroSec() * 0.000001;
        }
        /**
        *   获取毫秒
        */
        double getElapsedTimeInMilliSec()
        {
            return this->getElapsedTimeInMicroSec() * 0.001;
        }
        /**
        *   获取微妙
        */
        double getElapsedTimeInMicroSec()
        {
            timeval endCount;
            gettimeofday(&endCount, NULL);

            double  startTimeInMicroSec =   (_startCount.tv_sec * 1000000.0) + _startCount.tv_usec;
            double  endTimeInMicroSec   =   (endCount.tv_sec * 1000000.0) + endCount.tv_usec;
            return  endTimeInMicroSec - startTimeInMicroSec;
        }
    protected:
        timeval         _startCount;
    };
}

#endif