#include "lifeiFeaturePoint.h"
namespace CELL
{
	lifeiFeaturePoint::lifeiFeaturePoint(const char* name)
	{
		if (name)
		{
			strncmp(_name, name, sizeof(_name));
		}
		else
		{
			sprintf(_name, "%p", this);
		}
	}

	lifeiFeaturePoint::~lifeiFeaturePoint()
	{
	}

	//获取要素名称
	char* lifeiFeaturePoint::getName()
	{
		return _name;
	}

	//获取组的个数
	size_t lifeiFeaturePoint::getGroupCount()
	{
		return 0;
	}

	//获取组数据
	Group* lifeiFeaturePoint::getGroup(size_t index)
	{
		return 0;
	}

	//得到矢量包围盒
	aabb2dr lifeiFeaturePoint::getAABB()
	{
		return _aabb;
	}

	//返回点的个数
	size_t lifeiFeaturePoint::getPointCount()
	{
		return _points.size();
	}

	//返回指定点的信息
	real2 lifeiFeaturePoint::getPoint(size_t index)
	{
		return _points[index];
	}
}
