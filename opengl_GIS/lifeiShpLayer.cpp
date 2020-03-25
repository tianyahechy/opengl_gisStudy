#include "lifeiShpLayer.h"
#include "AxisALignedBox2d.h"
#include "IFeature.h"

namespace CELL
{
	bool lifeiShpLayer::loadShp(const char * shpName)
	{
		SHPHandle hShpFile = SHPOpen(shpName, "rb");
		if ( NULL == hShpFile)
		{
			return false;
		}

		//Ê¸Á¿ÀàÐÍ
		switch (hShpFile->nShapeType)
		{
		case SHPT_POINT:
		{

		}
		break;

		case SHPT_ARC:
		{

		}
		break;
		case SHPT_POLYGON:
		{

		}
		break;
		default:
			break;
		}
		for (int i = 0; i < hShpFile->nRecords; i++)
		{
			SHPObject* psShape = SHPReadObject(hShpFile, i);
			{

			}
		}
	}

	size_t lifeiShpLayer::getFeatureCount()
	{
		return _features.size();
	}

	IFeature * lifeiShpLayer::getFeature(size_t index)
	{
		return _features[index];
	}

	void lifeiShpLayer::addFeature(IFeature * feature)
	{
		_features.push_back(feature);
	}

	void lifeiShpLayer::removeFeature(IFeature * feature)
	{
		arrayFeature::iterator itr = std::find(_features.begin(), _features.end(), feature);
		if (itr == _features.end())
		{
			return;
		}
		_features.erase(itr);
	}

	void lifeiShpLayer::removeAllFeatures()
	{
		_features.clear();
	}

	void lifeiShpLayer::destroyAllFeatures()
	{
		for (size_t i = 0; i < _features.size(); i++)
		{
			delete _features[i];
		}
		_features.clear();
	}

	IFeature * lifeiShpLayer::query(const char * name)
	{
		for (size_t i = 0; i < _features.size(); i++)
		{
			if (strcmp(name, _features[i]->getName()))
			{
				continue;
			}
			return _features[i];
		}
		return NULL;
	}

	size_t lifeiShpLayer::query(const CELL::aabb2dr & aabb, arrayFeature & features)
	{
		for (size_t i = 0; i < _features.size(); i++)
		{
			aabb2dr fAABB = _features[i]->getAABB();
			if (fAABB.intersects(aabb))
			{
				features.push_back(_features[i]);
			}

		}
		return 0;
	}

}

