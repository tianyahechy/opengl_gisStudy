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

	};
}