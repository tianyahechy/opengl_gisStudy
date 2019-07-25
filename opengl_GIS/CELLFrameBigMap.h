#pragma once
#include "lifeiFrame.h"
#include "CELLTimestamp.hpp"
namespace CELL
{
    class CELLFrameBigMap :public lifeiFrame
    {
    public:
        CELLTimestamp   _timeStamp;
        aabb3dr         _aabb;
        real3           _basePoint;
        bool            _bLbuttonDown;
        int2            _lbuttonDown;
    public:
		CELLFrameBigMap(lifeiContext& context);

        virtual ~CELLFrameBigMap();

        /// <summary>
        /// 更新数据
        /// </summary>
		virtual void    update(lifeiContext& context);
        /// <summary>
        /// 开始绘制
        /// </summary>
		virtual void    onFrameStart(lifeiContext& context);

        /// <summary>
        /// 结束绘制
        /// </summary>
		virtual void    onFrameEnd(lifeiContext& context);


	public:
		//鼠标左键按下
		virtual void onLButtonDown(int x, int y);
		//鼠标左键提起
		virtual void onLButtonUp(int x, int y);
		//鼠标右键按下
		virtual void onRButtonDown(int x, int y);
		//鼠标右键提起
		virtual void onRButtonUp(int x, int y);
		//鼠标中键按下
		virtual void onMButtonDown(int x, int y);
		//鼠标中键提起
		virtual void onMButtonUp(int x, int y) ;
		//鼠标移动事件
		virtual void onMouseMove(int x, int y);
		//鼠标滚轮事件
		virtual void onMouseWheel(int delta);
		//键盘按键按下事件
		virtual void onKeyDown(int key);
		//键盘按键抬起事件
		virtual void onKeyUp(int key);
    protected:
        /// <summary>
        /// 返回鼠标点击出射线与场景的交点
        /// </summary>
        bool   getPointsFromScreen(int x,int y,real3& point);

    };

}

