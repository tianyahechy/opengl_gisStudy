#pragma once

#include "export.h"
#include "lifeiFrame.h"

namespace CELL
{
	class LifeiApp
	{
	public:
		//创建窗口函数
		virtual bool createWindow(HWND hParentWnd, int width, int height, HINSTANCE hInst) = 0;
		//创建框架
		virtual lifeiFrame* createFrame() = 0;
		//入口函数
		virtual void main(int argc, char** argv) = 0;
	};
}