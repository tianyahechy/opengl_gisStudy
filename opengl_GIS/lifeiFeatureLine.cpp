#include "lifeiFeatureLine.h"

namespace CELL
{
	lifeiFeatureLine::lifeiFeatureLine(const char* name)
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

	lifeiFeatureLine::~lifeiFeatureLine()
	{
	}

	//获取要素名称
	char* lifeiFeatureLine::getName()
	{
		return _name;
	}

	//获取组的个数
	size_t lifeiFeatureLine::getGroupCount()
	{
		return _groups.size();
	}

	//获取组数据
	Group* lifeiFeatureLine::getGroup(size_t index)
	{
		return &_groups[index];
	}

	//得到矢量包围盒
	aabb2dr lifeiFeatureLine::getAABB()
	{
		return _aabb;
	}

	//返回点的个数
	size_t lifeiFeatureLine::getPointCount()
	{
		return _points.size();
	}

	//返回指定点的信息
	real2 lifeiFeatureLine::getPoint(size_t index)
	{
		return _points[index];
	}
}
