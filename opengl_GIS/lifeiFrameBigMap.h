/*
#pragma once
#include "lifeiFrame.h"
#include "lifeiOpengl.h"
#include "lifeiTimeStamp.hpp"
#include "CELLTerrain.h"
#include "lifeiContext.h"

namespace CELL
{
	class lifeiFrameBigMap : public lifeiFrame
	{
		lifeiTimeStamp		_timeStamp;
		real3				_basePoint;
		bool				_bLbuttonDown;
		int2				_lbuttonDown;
		CELLTerrain			_terrain;
		bool				_bMbuttonDown;
		int2				_mButtonDown;

	public:
		lifeiFrameBigMap(lifeiContext& context);
		virtual ~lifeiFrameBigMap();

		//加载场景
		virtual bool loadScene(const char* fileName);
		//更新数据
		virtual void update(lifeiContext& context);
		//开始绘制
		virtual void onFrameStart(lifeiContext& context);
		//结束绘制
		virtual void onFrameEnd(lifeiContext& context);

		//鼠标左键提起
		virtual void onLButtonUp(int x, int y);
		//右键
		virtual void onRButtonDown(int x, int y);
		virtual void onRButtonUp(int x, int y);
		//中键
		virtual void onMButtonDown(int x, int y);
		virtual void onMButtonUp(int x, int y);

		//鼠标移动事件
		virtual void onMouseMove(int x, int y);
		//鼠标滚轮事件
		virtual void onMouseWheel(int delta);
		//键盘事件
		virtual void onKeyDown(int key);
		virtual void onKeyUp(int key);
		
	protected:
		//返回鼠标点击出射线与场景的交点
		bool getPointsFromScreen(int x, int y, real3& point);
		//平移场景
		void moveScene(const real3& worldPickup, const int2& ofScreen);
		
	};
}
*/