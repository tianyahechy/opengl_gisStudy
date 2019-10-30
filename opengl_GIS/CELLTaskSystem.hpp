#pragma once
namespace CELL
{
	class CELLTask
	{
	public:
		CELLTask()
		{

		}
		virtual ~CELLTask()
		{

		}
	};
	class CELLTaskSystem
	{
	public:
		//添加任务接口
		virtual void addTask(CELLTask * task)
		{

		}
	};
}
