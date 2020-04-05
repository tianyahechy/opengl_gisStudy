#include "lifeiShpLayer.h"
#include "AxisALignedBox2d.h"
#include "IFeature.h"
#include "lifeiFeatureLine.h"
#include "lifeiFeaturePoint.h"

namespace CELL
{
	bool lifeiShpLayer::loadShp(const char * shpName)
	{
		SHPHandle hShpFile = SHPOpen(shpName, "rb");
		if ( NULL == hShpFile)
		{
			return false;
		}

		_aabb.setExtents(
			hShpFile->adBoundsMin[0],
			hShpFile->adBoundsMin[1],
			hShpFile->adBoundsMax[0],
			hShpFile->adBoundsMax[1]			
			);

		for (int i = 0; i < hShpFile->nRecords; i++)
		{
			SHPObject* psShape = SHPReadObject(hShpFile, i);

			char szName[64];
			sprintf(szName, "%d", psShape->nShapeId);
			//Ê¸Á¿ÀàÐÍ
			switch (hShpFile->nShapeType)
			{
			case SHPT_POINT:
			{

				lifeiFeaturePoint* pFeature = new lifeiFeaturePoint(szName);
				pFeature->_points.resize(psShape->nVertices);
				for (int j = 0; j < psShape->nVertices; j++)
				{
					pFeature->_points[j].x = psShape->padfX[j];
					pFeature->_points[j].y = psShape->padfY[j];
				}
				_features.push_back(pFeature);
			}
			break;

			case SHPT_ARC:
			{

				lifeiFeatureLine* pLine = new lifeiFeatureLine(szName);
				pLine->_points.resize(psShape->nVertices);
				for (int j = 0; j < psShape->nVertices; j++)
				{
					pLine->_points[j].x = psShape->padfX[j];
					pLine->_points[j].y = psShape->padfY[j];
				}
				_features.push_back(pLine);
			}
			break;
			case SHPT_POLYGON:
			{

				lifeiFeatureLine* pLine = new lifeiFeatureLine(szName);
				pLine->_points.resize(psShape->nVertices);
				for (int j = 0; j < psShape->nVertices; j++)
				{
					pLine->_points[j].x = psShape->padfX[j];
					pLine->_points[j].y = psShape->padfY[j];
				}
				_features.push_back(pLine);
			}
			break;
			default:
				break;
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

