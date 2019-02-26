#pragma once
#include "CELLFrame.h"
#include "CELLTimestamp.hpp"
#include "CELLMath.hpp"
namespace CELL
{
	class CELLFrameBigMap : public CELLFrame
	{
	public:
		float3 _min;
		double3 _max;
	public:
		CELLTimestamp _timeStamp;
	public:
		CELLFrameBigMap(CELLContext& context);
		virtual ~CELLFrameBigMap();
	public:
		//开始绘制
		virtual void onFrameStart(CELLContext& context);
		//结束绘制
		virtual void onFrameEnd(CELLContext& context);
		//更新数据
		virtual void update(CELLContext& context);
		//鼠标左键按下
		virtual void onLButtonDown(int x, int y);
		//鼠标左键提起
		virtual void onLButtonUp(int x, int y);
		//鼠标移动
		virtual void onMouseMove(int x, int y);
		//鼠标滚轮事件
		virtual void onMouseWheel(int delta);
		//键盘事件
		virtual void onKeyDown(int key);
		//键盘事件
		virtual void onKeyUp(int key);
		//计算包围盒数据
		template< class T>
		AxisAlignedBox<T> calcAabb(const tvec3<T>* pPos, uint nCount)
		{
			AxisAlignedBox<T> aabb;
			aabb._minimum.x = FLT_MAX;
			aabb._minimum.y = FLT_MAX;
			aabb._minimum.z = FLT_MAX;
			aabb._maximum.x = -FLT_MAX;
			aabb._maximum.y = -FLT_MAX;
			aabb._maximum.z = -FLT_MAX;
			aabb._extent = AxisAlignedBox<T>::EXTENT_FINITE;

			for (int i = 1; i < nCount; i++)
			{
				aabb._minimum.x = MIN(aabb._minimum.x, pPos[i].x);
				aabb._minimum.y = MIN(aabb._minimum.y, pPos[i].y);
				aabb._minimum.z = MIN(aabb._minimum.z, pPos[i].z);
				aabb._maximum.x = MAX(aabb._maximum.x, pPos[i].x);
				aabb._maximum.y = MAX(aabb._maximum.x, pPos[i].y);
				aabb._maximum.z = MAX(aabb._maximum.x, pPos[i].z);
			}
			return aabb;
		}
		//计算包围球数据
		template< class T>
		tvec4<T> calcSphere(const tvec3<T>* pPos, uint nCount)
		{
			//先计算包围盒
			AxisAlignedBox<T> aabb = calcAabb(pPos, nCount);
			tvec3<T> center = aabb.getCenter();
			T radius = aabb.getHalfSize();
			return tvec4<T>(center.x, center.y, center.z, radius);
		}

	};
}

