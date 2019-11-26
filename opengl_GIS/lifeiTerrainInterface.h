#pragma once
#include "CELLMath.hpp"
namespace CELL
{
	class lifeiQuadTree;
	class lifeiTerrainInterface
	{
	public:
		virtual ~lifeiTerrainInterface()
		{
		}
		//创建纹理
		virtual uint createTexture(const TileId& id) = 0;
		//释放纹理
		virtual void releaseTexture(uint texId) = 0;
		//请求数据
		virtual void request(lifeiQuadTree * node) = 0;
		//释放纹理
		virtual void cancelRequest(lifeiQuadTree* node) = 0;
	};
}