#pragma once

#include    "CELLPlatform.hpp"
#include    "CELLObject.hpp"

#if CELL_PLATFORM == CELL_PLATFORM_WIN32


namespace   CELL
{
    class   CELLEvent :public CELLObject
    {
    protected:
        HANDLE  _handle;
    public:
        CELLEvent()
        {
            _handle =   CreateEvent(0,0,0,0);
        }
        virtual ~CELLEvent()
        {
            CloseHandle(_handle);
            _handle  =   0;
        }

        bool    set()
        {
            return  SetEvent(_handle) == TRUE;
        }

        bool    wait(DWORD ms = 0xFFFFFFFF)
        {
            switch (WaitForSingleObject(_handle, ms))
            {
            case WAIT_OBJECT_0:
                return  true;
            case WAIT_TIMEOUT:
                return  false;
            default:
                return  false;
            }
        }

        void    reset()
        {
            ResetEvent(_handle);
        }

    };
}

#elif CELL_PLATFORM == CELL_PLATFORM_LINUX

namespace CELL
{
    class CELLEvent
    {
    protected:
        volatile bool   _state;
        pthread_mutex_t _mutex;
        pthread_cond_t  _cond;
    public:

        CELLEvent()
        {
            if(pthread_mutex_init(&_mutex, NULL))
            {
                throw "can not create event (mutex)";
            }
            if(pthread_cond_init(&_cond, NULL))
            {
                throw "can not create event (condition)";
            }
        }
        ~CELLEvent()
        {
            pthread_cond_destroy(&_cond);
            pthread_mutex_destroy(&_mutex);
        }

        void    set()
        {
            if (pthread_mutex_lock(&_mutex))
            {
                throw "can not signal event (lock)";
            }
            _state = true;
            if (pthread_cond_broadcast(&_cond))
            {
                pthread_mutex_unlock(&_mutex);
                throw "can not signal event";
            }
            pthread_mutex_unlock(&_mutex);
        }

        void    wait()
        {
            if (pthread_mutex_lock(&_mutex))
            {
                throw "wait for event failed (lock)";
            }
            while (!_state)
            {
                if (pthread_cond_wait(&_cond, &_mutex))
                {
                    pthread_mutex_unlock(&_mutex);
                    throw "wait for event failed";
                }
            }
            _state = false;
            pthread_mutex_unlock(&_mutex);
        }

        void    reset()
        {
            if (pthread_mutex_lock(&_mutex))
                throw "cannot reset event";
            _state = false;
            pthread_mutex_unlock(&_mutex);
        }

    };
}


#endif
