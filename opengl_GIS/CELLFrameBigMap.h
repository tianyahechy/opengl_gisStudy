#pragma once
#include "CELLFrame.h"
namespace CELL
{
	class CELLFrameBigMap : public CELLFrame
	{
	public:
		CELLFrameBigMap(CELLContext& context);
		virtual ~CELLFrameBigMap();
	public:
		//开始绘制
		virtual void onFrameStart(CELLContext& context);
		//结束绘制
		virtual void onFrameEnd(CELLContext& context);
		//更新数据
		virtual void update(CELLContext& context);
	};
}

