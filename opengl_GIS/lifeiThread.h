#pragma once
#include "export.h"
#include "lifeiObject_2.h"

namespace CELL
{
	class lifeiThread : public lifeiObject_2
	{
	public:
		DWORD			_threadId;
		HANDLE			_thread;

	protected:
		//线程入口函数
		static unsigned long __stdcall threadEnter(void * ptr)
		{
			lifeiThread* pThis = (lifeiThread *)ptr;
			if (pThis)
			{
				pThis->onCreate();
				pThis->onRun();
				pThis->onDestroy();
			}
			return 0;
		}

	public:
		lifeiThread()
		{
			_thread = 0;
		}
		virtual ~lifeiThread()
		{
			join();
		}
		DWORD threadId() const
		{
			return _threadId;
		}
		bool isRun() const
		{
			return _thread != 0;
		}
		//创建完成通知函数
		virtual bool onCreate()
		{
			return false;
		}
		//线程执行函数
		virtual bool onRun()
		{
			return false;
		}
		//结束函数
		virtual bool onDestroy()
		{
			return false;
		}
		//启动线程函数
		virtual bool start()
		{
			if (_thread != 0)
			{
				return false;
			}
			else
			{
				_thread = CreateThread(0, 0, &lifeiThread::threadEnter, this, HIGH_PRIORITY_CLASS, &_threadId);
				return true;
			}
		}

		//等待退出函数
		virtual void join()
		{
			if (_thread)
			{
				WaitForSingleObject(_thread, 0xFFFFFFFF);
				CloseHandle(_thread);
				_thread = 0;
			}
		}
		//关闭
		virtual void close()
		{
			CloseHandle(_thread);
			_thread = 0;
		}
	};
}
