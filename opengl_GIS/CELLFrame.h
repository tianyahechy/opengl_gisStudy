#pragma once
#include "CELLContext.h"
namespace CELL
{
	class CELLFrame
	{
	public:
		CELLContext& _context;
	public:
		CELLFrame(CELLContext& context) : 
			_context (context)
		{}
		virtual ~CELLFrame()
		{

		}
		//开始绘制
		virtual void onFrameStart(CELLContext& context) = 0;
		//结束绘制
		virtual void onFrameEnd(CELLContext& context) = 0;
		//更新数据
		virtual void update(CELLContext& context) = 0;
	};
}