#pragma once
#include "export.h"
#include "lifeiObject_2.h"

namespace CELL
{
	class lifeiThread_2 : public lifeiObject_2
	{
	public:
		DWORD		_threadId;
		HANDLE		_thread;

	protected:
		//线程入口函数
		static unsigned long __stdcall threadEnter(void* ptr);

	public:
		lifeiThread_2();
		virtual ~lifeiThread_2();
		DWORD threadId() const;
		bool isRun() const;
		//创建完成通知函数
		virtual bool onCreate();
		//线程执行函数
		virtual bool onRun();
		//结束函数
		virtual bool onDestroy();
		//启动线程函数
		virtual bool start();
		//等待退出函数
		virtual void join();
		//关闭
		virtual void close();
	};
}