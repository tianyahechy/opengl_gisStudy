#include "lifeiTaskSystem.h"
#include "lifeiTaskThread_2.h"

namespace CELL
{
	lifeiTaskSystem::lifeiTaskSystem()
	{
		_observer = 0;
		_threads.clear();
	}
	lifeiTaskSystem::~lifeiTaskSystem()
	{
		_threads.clear();
	}
	void lifeiTaskSystem::setObserver(lifeiTaskObserver * observer)
	{
		_observer = observer;
	}
	void lifeiTaskSystem::start(int threadNum)
	{
		destroy();
		for (size_t i = 0; i < threadNum; i++)
		{
			lifeiTaskThread_2 * pThread = new lifeiTaskThread_2(this);
			pThread->start();
			_threads.push_back(pThread);
		}
	}
	void lifeiTaskSystem::destroy()
	{
		for (int i = 0; i < _threads.size(); i++)
		{
			_threads[i]->join();
			delete _threads[i];
		}
		_threads.clear();
	}
	void lifeiTaskSystem::addTask(lifeiTask_2* task)
	{
		{
			lifeiMutex::ScopeLock lk(_mutex);
			_tasks.push_back(task);
		}
		//这时候应该有一个任务了
		_semphore.set(1);
	}
	void lifeiTaskSystem::run()
	{
		if (!_semphore.wait())
		{
			return;
		}

		//取数据任务
		lifeiTask_2* pTask = 0;
		{
			lifeiMutex::ScopeLock lk(_mutex);
			bool taskEmpty = _tasks.empty();
			if (taskEmpty)
			{
				return;
			}
			//取数据
			pTask = _tasks.front();
			_tasks.pop_front();
		}
		//2执行过程
		//3通知过程
		if (_observer && pTask)
		{
			_observer->onTaskExe(pTask);
			_observer->onTaskFinish(pTask);
		}
	}

}

