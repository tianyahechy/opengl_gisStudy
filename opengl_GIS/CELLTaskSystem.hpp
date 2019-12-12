#pragma once
#include "CELLTask.hpp"
#include "lifeiThread.h"
#include <list>
#include "lifeiSemaphore.h"
#include "lifeiMutex.h"
namespace CELL
{

	class CELLTaskObserver
	{
	public:
		//任务执行通知
		virtual void onTaskExe(CELLTask* task) = 0;
		//任务完成通知
		virtual void onTaskFinish(CELLTask* task) = 0;		
		//任务取消通知
		virtual void onTaskCancel(CELLTask* task) = 0;
	};
	class CELLTaskSystem
	{
	public:
		class TaskThread : public lifeiThread
		{
		public:
			//退出标志
			bool _exitFlag;
			CELLTaskSystem* _system;

		public:
			TaskThread( CELLTaskSystem* pSystem)
			{
				_exitFlag = true;
				_system = pSystem;
			}
			//退出
			virtual void join()
			{
				_exitFlag = true;
				lifeiThread::join();
			}
			virtual bool onCreate()
			{
				_exitFlag = false;
				return false;
			}
			virtual bool onRun()
			{
				while (!_exitFlag)
				{
					_system->run();
				}
				return false;
			}
			virtual bool onDestroy()
			{
				return false;
			}
		};
		typedef std::vector<lifeiThread* >	arrayThread;
		typedef std::list<CELLTask*>		arrayTask;
	public:
		CELLTaskObserver* _observer;
		arrayThread _threads;
		arrayTask _tasks;
		lifeiSemaphore _semphore;
		lifeiMutex _mutex;
	public:
		CELLTaskSystem()
		{
			_observer = 0;
			_threads.clear();
		}
		virtual~ CELLTaskSystem()
		{
			_threads.clear();
		}

		//设置观察者指针
		virtual void setObserver(CELLTaskObserver* observer)
		{
			_observer = observer;
		}
	public:
		//启动任务处理
		virtual void start(int threadNum = 4)
		{
			destroy();
			for (size_t i = 0; i < threadNum; i++)
			{
				TaskThread * pThread = new TaskThread(this);
				pThread->start();
				_threads.push_back(pThread);
			}
		}
		//销毁
		virtual void destroy()
		{
			for (int i = 0; i < _threads.size(); i++)
			{
				_threads[i]->join();
				delete _threads[i];
			}
			_threads.clear();
		}
		//添加任务接口
		virtual void addTask(CELLTask* task)
		{
			{
				lifeiMutex::ScopeLock lk(_mutex);
				_tasks.push_back(task);
			}
			
			_semphore.set(1);
		}

	public:
		virtual void run()
		{
			if (!_semphore.wait())
			{
				return;
			}
			CELLTask* pTask = 0;
			{
				lifeiMutex::ScopeLock lk(_mutex);
				bool taskEmpty = _tasks.empty();
				if (taskEmpty)
				{
					return;
				}
				//1，取数据
				pTask = _tasks.front();
				_tasks.pop_front();
			}

			//2,执行过程
			//3,通知过程
			if (_observer && pTask)
			{
				_observer->onTaskExe(pTask);
				_observer->onTaskFinish(pTask);
			}
		}
	};
}
