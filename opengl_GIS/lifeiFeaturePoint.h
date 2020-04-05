#pragma once
#include "IFeaturePoint.h"
#include "group.h"

namespace CELL
{
	class lifeiFeaturePoint : public IFeaturePoint
	{
	public:
		typedef std::vector<real2> pointArray;
	public:
		char _name[64];
		aabb2dr _aabb;
		pointArray _points;
	public:
		lifeiFeaturePoint(const char* name);
		~lifeiFeaturePoint();

		//获取要素名称
		virtual char* getName();
		//得到矢量包围盒
		virtual aabb2dr getAABB();
		//返回点的个数
		virtual size_t getPointCount();
		//返回指定点的信息
		virtual real2 getPoint(size_t index);
		//获取组的个数
		virtual size_t getGroupCount();
		//获取组数据
		virtual Group* getGroup( size_t index);
	};

}

