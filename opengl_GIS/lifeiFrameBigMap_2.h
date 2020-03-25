#pragma once
#include "lifeiFrame_2.h"
#include "lifeiOpengl.h"
#include "lifeiTimeStamp.hpp"
#include "lifeiTerrain_2.h"
#include "lifeiContext_2.h"

namespace CELL
{
	class lifeiFrameBigMap_2 : public lifeiFrame_2
	{
		lifeiTimeStamp		_timeStamp;
		real3				_basePoint;
		bool				_bLbuttonDown;
		int2				_lbuttonDown;
		lifeiTerrain_2		_terrain;
		bool				_bMbuttonDown;
		int2				_mButtonDown;

	public:
		lifeiFrameBigMap_2(lifeiContext_2& context);
		virtual ~lifeiFrameBigMap_2();

		//加载场景
		virtual bool loadScene(const char* fileName);
		//更新数据
		virtual void update(lifeiContext_2& context);
		//开始绘制
		virtual void onFrameStart(lifeiContext_2& context);
		//结束绘制
		virtual void onFrameEnd(lifeiContext_2& context);
		//鼠标左键提起
		virtual void onLButtonUp(int x, int y);
		virtual void onLButtonDown(int x, int y);
		//鼠标右键
		virtual void onRButtonUp(int x, int y);
		virtual void onRButtonDown(int x, int y);
		//中键
		virtual void onMButtonUp(int x, int y);
		virtual void onMButtonDown(int x, int y);
		//鼠标移动事件
		virtual void onMouseMove(int x, int y);
		//鼠标滚轮事件
		virtual void onMouseWheel(int delta);

		//键盘事件
		virtual void onKeyDown(int key);
		virtual void onKeyUp(int key);

	protected:
		//返回鼠标点击出射线与场景的交点
		//bool getPointsFromScreen(int x, int y, real3& point);
		//平移场景
		void moveScene(const real3& worldPickup, const int2& ofScreen);

	};
}