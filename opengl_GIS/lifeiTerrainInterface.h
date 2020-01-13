#pragma once
#include "CELLMath.hpp"
namespace CELL
{
	class lifeiQuadTree;
	class lifeiCounts
	{
	public:
		uint _nodes;
		uint _drawNodes;
		uint _textCounts;
		uint _texUsed;
		uint _texFree;
	};
	class lifeiTerrainInterface
	{
	public:
		virtual ~lifeiTerrainInterface()
		{
		}
		//释放纹理
		virtual void releaseTexture(uint texId) = 0;
		//请求数据
		virtual void request(lifeiQuadTree * node) = 0;
		//释放纹理
		virtual void cancelRequest(lifeiQuadTree* node) = 0;
		//获取统计信息
		virtual lifeiCounts& getCounts() = 0;
	};
}