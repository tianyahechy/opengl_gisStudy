#pragma once
#include "CELLPlatform.hpp"
#include "CELLObject.h"
#if CELL_PLATFORM == CELL_PLATFORM_WIN32
namespace CELL
{
	class CELLThread : public CELLObject
	{
	public:
		DWORD _threadId;
		HANDLE _thread;
	public:
		CELLThread()
		{
			_thread = 0;
		}
	
		virtual ~CELLThread()
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
			if (_thread != 0 )
			{
				return false;
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
	protected:
		//线程入口函数
		static unsigned long __stdcall threadEnter(void * pVoid)
		{
			CELLThread * pThis = (CELLThread*)pVoid;
			if (pThis)
			{
				pThis->onCreate();
				pThis->onRun();
				pThis->onDestroy();
			}
		}

	private:

	};


}
#endif