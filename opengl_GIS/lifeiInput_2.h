#pragma once
namespace CELL
{
	class lifeiInput_2
	{
	public:
		//鼠标左键按下
		virtual void onLButtonDown(int x, int y) = 0;
		//鼠标左键提起
		virtual void onLButtonUp(int x, int y) = 0;
		//鼠标右键按下
		virtual void onRButtonDown(int x, int y) = 0;
		//鼠标右键提起
		virtual void onRButtonUp(int x, int y) = 0;
		//鼠标中键按下
		virtual void onMButtonDown(int x, int y) = 0;
		//鼠标中键提起
		virtual void onMButtonUp(int x, int y) = 0;
		//鼠标移动事件
		virtual void onMouseMove(int x, int y) = 0;
		//鼠标滚轮事件
		virtual void onMouseWheel(int delta) = 0;
		//键盘按键按下事件
		virtual void onKeyDown(int key) = 0;
		//键盘按键抬起事件
		virtual void onKeyUp(int key) = 0;
	};
}
