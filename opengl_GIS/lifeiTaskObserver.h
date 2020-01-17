#pragma once
#include "lifeiTask.h"
namespace CELL
{
	class lifeiTaskObserver
	{
	public:
		//任务执行通知
		virtual void onTaskExe(lifeiTask* task) = 0;
		//任务完成通知
		virtual void onTaskFinish(lifeiTask* task) = 0;
		//任务取消通知
		virtual void onTaskCancel(lifeiTask* task) = 0;
	};

}