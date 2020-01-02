#pragma once
#include "CELLTask.hpp"
namespace CELL
{
	class lifeiTaskObserver
	{
	public:
		//任务执行通知
		virtual void onTaskExe(CELLTask* task) = 0;
		//任务完成通知
		virtual void onTaskFinish(CELLTask* task) = 0;
		//任务取消通知
		virtual void onTaskCancel(CELLTask* task) = 0;
	};

}