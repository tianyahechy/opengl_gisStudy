#pragma once
#include <vector>
#include "AxisALignedBox.h"

#include "AxisALignedBox2d.h"
//矢量图层
namespace CELL
{
	class IFeature;
	typedef std::vector<IFeature*> arrayFeature;
	class ILayer
	{
	public:
		//加载shp文件
		virtual bool loadShp(const char* shpName) = 0;
		//得到矢量要素个数
		virtual size_t getFeatureCount() = 0;
		//得到矢量要素
		virtual IFeature* getFeature(size_t index) = 0;
		//在图层添加矢量要素
		virtual void addFeature(IFeature* feature) = 0;
		//删除矢量要素
		virtual void removeFeature( IFeature* feature) = 0;
		//移除所有矢量要素
		virtual void removeAllFeatures() = 0;
		//删除所有矢量要素
		virtual void destroyAllFeatures() = 0;
		//根据矢量要素名称查询
		virtual IFeature* query(const char* name) = 0;
		//根据经纬度范围查找矢量要素
		virtual size_t query(const CELL::aabb2dr& aabb, arrayFeature& features) = 0;
	};

}

