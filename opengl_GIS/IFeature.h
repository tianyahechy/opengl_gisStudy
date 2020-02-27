#pragma once
#include "tvec2.h"
#include "AxisALignedBox.h"
namespace CELL
{
	class Group;
	//矢量要素信息
	class IFeature
	{
	public:
		virtual ~IFeature() {}

		//得到矢量包围盒
		virtual aabb3dr getAABB() = 0;
		//返回点的个数
		virtual size_t getPointCount() = 0;
		//返回指定点的信息
		virtual real2 getPoint(size_t index) = 0;
		//获取组的个数
		virtual size_t getGroupCount() = 0;
		//得到组
		virtual Group* getGroup() = 0;
	};

}