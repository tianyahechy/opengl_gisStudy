#pragma once
#include "lifeiTask.h"
#include "lifeiThread.h"
#include <vector>
#include <list>
#include "lifeiSemaphore.h"
#include "lifeiMutex.h"
#include "lifeiTaskObserver.h"
namespace CELL
{
	typedef std::vector<lifeiThread* >	arrayThread;
	typedef std::list<lifeiTask*>		arrayTask;
	class lifeiTaskSystem
	{
	public:
		lifeiTaskObserver * _observer;
		arrayThread _threads;
		arrayTask _tasks;
		lifeiSemaphore _semphore;
		lifeiMutex _mutex;
	public:
		lifeiTaskSystem();
		virtual ~lifeiTaskSystem();
	//设置观察者指针
		virtual void setObserver(lifeiTaskObserver * observer);
	public:
	//启动任务管理
		virtual void start(int threadNum = 4);
	//销毁
		virtual void destroy();
	//添加任务接口
		virtual void addTask(lifeiTask* task);
	public:
		virtual void run();
	};

}
