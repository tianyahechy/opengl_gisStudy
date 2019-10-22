#pragma once
#include "lifeiFrame.h"
#include "lifeiTimeStamp.hpp"
#include "CELLOpenGL.h"
#include "CELLTerrain.h"
#include "lifeiContext.h"
namespace CELL
{
    class CELLFrameBigMap :public lifeiFrame
    {
    public:
        lifeiTimeStamp  _timeStamp;
        aabb3dr         _aabb;
        real3           _basePoint;
        bool            _bLbuttonDown;
        int2            _lbuttonDown;
        Texture2dId     _textureId;
        CELLTerrain     _terrain;
		bool			_bMbuttonDown;
		int2			_mButtonDown;
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

        /// <summary>
        /// 鼠标左键按下
        /// </summary>
        virtual void    onLButtonDown(int x, int y);
        /// <summary>
        /// 鼠标左键提起
        /// </summary>
        virtual void    onLButtonUp(int x, int y);
		//右键
		virtual void onRButtonDown(int x, int y);
		virtual void onRButtonUp(int x, int y);
		//中键
		virtual void onMButtonDown(int x, int y);
		virtual void onMButtonUp(int x, int y);

        /// <summary>
        /// 鼠标移动事件
        /// </summary>
        virtual void    onMouseMove(int x, int y);

        /// <summary>
        /// 鼠标滚轮事件
        /// </summary>
        virtual void    onMouseWheel(int delta);
        /// <summary>
        /// 键盘事件
        /// </summary>
        virtual void    onKeyDown(int key);
        /// <summary>
        /// 键盘事件
        /// </summary>
        virtual void    onKeyUp(int key);
    protected:
        /// <summary>
        /// 返回鼠标点击出射线与场景的交点
        /// </summary>
        bool   getPointsFromScreen(int x,int y,real3& point);
		//平移场景
		void moveScene(const real3& worldPickup, const int2& ofScreen);

    };

}

