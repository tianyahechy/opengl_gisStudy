#pragma once

#include "lifeiPlatform.h"
#include "CELLFrame.hpp"

namespace CELL
{
	class LifeiApp
	{
	public:
		//创建窗口函数
		virtual bool createWindow(int width, int height, INSTANCE hInst) = 0;
		//创建框架
		virtual CELLFrame* createFrame() = 0;
		//入口函数
		virtual void main(int argc, char** argv) = 0;
	};
}