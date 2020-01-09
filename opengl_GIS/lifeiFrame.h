#pragma once

#include "lifeiContext.h"
#include "lifeiInput.h"

namespace CELL
{
	class lifeiFrame : public lifeiInput
	{
	public:
		lifeiContext&  _context;
	public:
		lifeiFrame(lifeiContext& context)
			: _context(context)
		{

		}
		virtual ~lifeiFrame()
		{

		}
		//加载场景
		virtual bool loadScene(const char* fileName) = 0;
		//更新数据
		virtual void update(lifeiContext& context) = 0;
		//开始绘制
		virtual void onFrameStart(lifeiContext& context) = 0;
		//结束绘制
		virtual void onFrameEnd(lifeiContext& context) = 0;
	};
}