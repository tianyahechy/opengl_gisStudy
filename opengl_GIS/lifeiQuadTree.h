#pragma once
#include "CELLMath.hpp"
#include "lifeiObject.h"
#include "lifeiContext.h"
#include "lifeiTerrainInterface.h"
#include "lifeiTileId.h"
#include "AxisALignedBox.h"

namespace CELL
{
	class lifeiQuadTree : public  lifeiObject
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
			FLAG_HAS_IMAGE	= 1 << 0,
			FLAG_HAS_CULL	= 1 << 1,
			FLAG_RENDER		= 1 << 2,
		};
	public:
		typedef std::vector<lifeiQuadTree*> ArrayNode;
	public:
		lifeiTerrainInterface* _terrain;
		//对应瓦片id
		 lifeiTileId _tileID;
		//数据标志
		uint	_flag;
		//世界坐标范围
		real2 _vStart;
		real2 _vEnd;

		float2 _uvStart;
		float2 _uvEnd;
		//对应瓦片的范围（世界坐标）
		aabb3dr _aabb;
		//位置
		ChildID _cornerID;
		//当前瓦片的父节点
		lifeiQuadTree * _parent;
		//纹理ID
		uint			_textureID;
		//当前瓦片的孩子节点数组
		lifeiQuadTree * _childs[4];
	public:
		lifeiQuadTree( 
			lifeiTerrainInterface * pInterface,
			lifeiQuadTree* parent, 
			const real2 vStart, 
			const real2 vEnd,
			int level,
			ChildID corner);
		~lifeiQuadTree();
		//获取可见节点
		virtual void getAllRenderableNode(ArrayNode& nodes);
		//更新节点
		void update(lifeiContext& context);
		//判断是否有子节点（目前只要判断一个即可，因为一同添加，一同销毁）
		bool hasChild();
		//判断是否存在图像
		bool hasImage();
		//判断是否存在标志
		bool hasFlag(uint flag)
		{
			return (_flag & flag) ? true : false;
		}
		bool hasNoFlag(uint flag)
		{
			return !hasFlag(flag);
		}
		//纹理数据到达
		virtual void updateTexture(unsigned texID);
	};
}

