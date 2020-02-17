#pragma once
namespace CELL
{
	class lifeiQuadTree;
	class lifeiCounts
	{
	public:
		unsigned int		_nodes;
		unsigned int		_drawNodes;
		unsigned int		_textCounts;
		unsigned int		_texUsed;
		unsigned int		_texFree;
	};

	class lifeiTerrainInterface_2
	{
	public:
		virtual ~lifeiTerrainInterface_2()
		{}

		//释放纹理
		virtual void releaseTexture(unsigned int texID) = 0;
		//请求数据
		virtual void request(lifeiQuadTree* node) = 0;
		//取消数据
		virtual void cancelRequest(lifeiQuadTree* node) = 0;
		//获取统计信息
		virtual lifeiCounts& getCounts() = 0;
	};
}