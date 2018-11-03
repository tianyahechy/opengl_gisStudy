#pragma once
#include "shp/shapefil.h"

#include"CELLFeature.h"
#include "CELLShader.hpp"

namespace CELL
{
	class CELLShpReader
	{
	public:
		arrayFeature	_features;
		float			_xMax;
		float			_yMax;
		float			_xMin;
		float			_yMin;

	public:
		bool read(const char * shpName)
		{
			SHPHandle hShpFile = SHPOpen(shpName, "rb");
			if (hShpFile == 0)
			{
				return false;
			}
			if (hShpFile == 0)
			{
				return false;
			}
			//写入图层数据到数据库中
			_xMax = (float)hShpFile->adBoundsMax[0];
			_yMax = (float)hShpFile->adBoundsMax[1];
			_xMin = (float)hShpFile->adBoundsMin[0];
			_yMin = (float)hShpFile->adBoundsMin[1];
			for (int i = 0; i < hShpFile->nRecords; i++)
			{
				SHPObject * psShape = SHPReadObject(hShpFile, i);
				CELLFeature * feature = new CELLFeature();
				feature->reserve(psShape->nVertices);

				Primative pri;
				if (psShape->nParts == 0)
				{
					pri._count = psShape->nVertices;
					pri._start = 0;
					pri._type = GL_LINE_STRIP;
					feature->_pris.push_back(pri);
				}
				for (int x = 0; x < psShape->nParts; x++)
				{
					pri._start = psShape->panPartStart[x];
					if (x == psShape->nParts - 1)
					{
						pri._count = psShape->nVertices - psShape->panPartStart[x];
					}
					else
					{
						pri._count = psShape->panPartStart[x + 1] - psShape->panPartStart[x];
					}
					switch (psShape->panPartType[x])
					{
					case SHPT_POINT:
					{
						pri._type = GL_LINE_STRIP;

					}
						break;

					case SHPT_ARC:
					{
						pri._type = GL_LINE_STRIP;
					}
						break;

					case SHPT_POLYGON:
					{
						pri._type = GL_LINE_STRIP;
					}
						break;
					default:
						pri._type = GL_LINE_STRIP;
						break;
					}
					feature->_pris.push_back(pri);
				}
				for (int j = 0; j < psShape->nVertices; j++)
				{
					float x = (float)psShape->padfX[j];
					float y = (float)psShape->padfY[j];
					feature->push_back(float2(x, y));
				}
				SHPDestroyObject(psShape);
				_features.push_back(feature);;
			}
			SHPClose(hShpFile);
		}
		
		void render(PROGRAM_P2_C4& shader)
		{
			glUniform4f(shader._color, 1, 0, 0, 1);
			for (size_t i = 0; i < _features.size(); i++)
			{
				CELLFeature * feature = _features[i];
				float2 * vertex = (float2 *)& feature->front();
				glVertexAttribPointer(shader._position, 2, GL_FLOAT, false, sizeof(float2), vertex);
				for (size_t j = 0; j < feature->_pris.size(); j++)
				{
					Primative pri = feature->_pris[j];
					glDrawArrays(pri._type, pri._start, pri._count);
				}
			}
		}
	
	};
}