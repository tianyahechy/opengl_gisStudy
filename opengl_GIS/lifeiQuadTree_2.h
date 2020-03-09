#pragma once

#include "lifeiObject_2.h"
#include "lifeiContext_2.h"
#include "lifeiTerrainInterface_2.h"
#include "lifeiTileId.h"
#include "AxisALignedBox.h"

namespace CELL
{
	class lifeiQuadTree_2 : public lifeiObject_2
	{
	public:
		enum ChildID
		{
			CHILD_LT,
			CHILD_RT,
			CHILD_LB,
			CHILD_RB,
		};
		enum  
		{
			FLAG_HAS_IMAGE = 1 << 0,
			FLAG_HAS_CULL = 1 << 1,
			FLAG_RENDER	= 1 << 2,	
		};

	public:
		typedef std::vector<lifeiQuadTree_2*> arrayNode;

	public:
		lifeiTerrainInterface_2* _terrain;
		//对应瓦片ID
		lifeiTileId	_tileID;
		//数据标志
		uint _flag;
		//世界坐标范围
		real2	_startXY;
		real2	_endXY;

		//三维纹理中相对于根节点的uv坐标（根节点起始UV（0，0），终止UV（1，1））
		float2	_uvStart;
		float2	_uvEnd;

		//对应瓦片的范围(世界坐标）
		aabb3dr	_aabb;
		//当前瓦片的父节点
		lifeiQuadTree_2 * _parent;
		//纹理ID
		uint	_textureID;
		//当前瓦片的孩子节点数组
		lifeiQuadTree_2* _childs[4];

	public:
		lifeiQuadTree_2(lifeiTerrainInterface_2* pInterface,
			lifeiQuadTree_2* parent,
			const real2	startXY,
			const real2 endXY,
			int level,
			ChildID corner
		);
		~lifeiQuadTree_2();
		//获取可见节点
		virtual void getAllRenderableNode(arrayNode& nodes);
		//更新节点,根据距离进行四叉树分割
		void update(lifeiContext_2& context);
		//判断是否有子节点（目前只要判断一个即可，因为一同添加，一同销毁)
		bool hasChild();
		//判断是否存在图像
		bool hasImage();
		//判断是否存在标志
		bool hasFlag(uint flag);
		//判断是否没有标志
		bool hasNoFlag(uint flag);
		//纹理数据到达
		virtual void updateTexture(unsigned texID);

	};
}
