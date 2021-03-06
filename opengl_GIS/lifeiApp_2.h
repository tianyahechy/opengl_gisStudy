#pragma once
#include "lifeiFrame_2.h"
#include <Windows.h>

namespace CELL
{
	class lifeiApp_2
	{
	public:
		//创建窗口函数
		virtual bool createWindow(HWND hParantWnd, int width, int height, HINSTANCE hInst) = 0;
		//创建框架
		virtual lifeiFrame_2* createFrame() = 0;
		//入口函数
		virtual void main(int argc, char** argv) = 0;
	};
}