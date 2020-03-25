#pragma once
#include "ILayer.h"
#include "shp/shapefil.h"
#include "AxisALignedBox2d.h"

namespace CELL
{
	class lifeiShpLayer : public ILayer
	{
	public:
		//保存所有的要素数据
		arrayFeature _features;

	public:
		//加载shp文件
		virtual bool loadShp(const char* shpName);
		//得到矢量要素个数
		virtual size_t getFeatureCount();
		//得到矢量要素
		virtual IFeature* getFeature(size_t index);
		//在图层添加矢量要素
		virtual void addFeature(IFeature* feature);
		//删除矢量要素
		virtual void removeFeature(IFeature* feature);
		//移除所有矢量要素
		virtual void removeAllFeatures();
		//删除所有矢量要素
		virtual void destroyAllFeatures();
		//根据矢量要素名称查询
		virtual IFeature* query(const char* name);
		//根据经纬度范围查找矢量要素
		virtual size_t query(const CELL::aabb2dr& aabb, arrayFeature& features);
	};
}
