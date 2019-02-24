#pragma once
namespace CELL
{
	class CELLInput
	{
	public:
		//鼠标左键按下
		virtual void onLButtonDown(int x, int y) = 0;
		//鼠标左键提起
		virtual void onLButtonUp(int x, int y) = 0;
		//鼠标移动
		virtual void onMouseMove(int x, int y) = 0;
		//鼠标滚轮事件
		virtual void onMouseWheel( int delta) = 0; 
		//键盘事件
		virtual void onKeyDown(int key) = 0;
		//键盘事件
		virtual void onKeyUp(int key) = 0;

	};
}