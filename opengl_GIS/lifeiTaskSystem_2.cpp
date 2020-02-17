#include "lifeiTaskSystem_2.h"
#include "lifeiTaskThread_2.h"

namespace CELL
{
	lifeiTaskSystem_2::lifeiTaskSystem_2()
	{
		_observer = 0;
		_threads.clear();
	}

	lifeiTaskSystem_2::~lifeiTaskSystem_2()
	{
		_threads.clear();
	}

	void lifeiTaskSystem_2::setObserver(lifeiTaskObserver_2 * observer)
	{
		_observer = observer;
	}

	void lifeiTaskSystem_2::start(int threadNum)
	{
		destroy();
		for (size_t i = 0; i < threadNum; i++)
		{
			lifeiTaskThread_2* pThread = new lifeiTaskThread_2(this);
			pThread->start();
			_threads.push_back(pThread);
		}
	}

	void lifeiTaskSystem_2::destroy()
	{
		for (size_t i = 0; i < _threads.size(); i++)
		{
			_threads[i]->join();
			delete _threads[i];
		}
		_threads.clear();
	}

	void lifeiTaskSystem_2::addTask(lifeiTask_2* task)
	{
		//添加要求的瓦片数据名称
		{
			lifeiMutex_2::ScopeLock lk(_mutex);
			_tasks_requestTile.push_back(task);
		}

		//这时候有任务了，增加信号量
		_semphore.set(1);
	}

	void lifeiTaskSystem_2::run()
	{
		if ( !_semphore.wait())
		{
			return;
		}

		//取任务,根据瓦片名称进行加载瓦片，生成texture
		lifeiTask_2 * pTask = 0;
		{
			lifeiMutex_2::ScopeLock lk(_mutex);
			bool taskEmpty = _tasks_requestTile.empty();
			if (taskEmpty)
			{
				return;
			}
			//取数据
			pTask = _tasks_requestTile.front();
			_tasks_requestTile.pop_front();
		}

		//执行过程
		//通知过程
		if (_observer && pTask)
		{
			_observer->onTaskExe(pTask);   //转到terrain
			_observer->onTaskFinish(pTask);
		}
	}

}
