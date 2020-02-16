#pragma once
#include "lifeiTask_2.h"
namespace CELL
{
	class lifeiTaskObserver
	{
	public:
		//任务执行通知
		virtual void onTaskExe(lifeiTask_2* task) = 0;
		//任务完成通知
		virtual void onTaskFinish(lifeiTask_2* task) = 0;
		//任务取消通知
		virtual void onTaskCancel(lifeiTask_2* task) = 0;
	};

}