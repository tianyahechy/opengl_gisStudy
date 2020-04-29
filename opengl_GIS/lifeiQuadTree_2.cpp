#include "lifeiQuadTree_2.h"
#include "lifeiSpatialReference_2.h"

namespace CELL
{
	lifeiQuadTree_2::lifeiQuadTree_2(
		lifeiTerrainInterface_2* pInterface,
		lifeiQuadTree_2* parent,
		const real2	startXY,
		const real2 endXY,
		int level,
		ChildID corner)
	{
		_aabb.setExtents(startXY.x, 0, startXY.y, endXY.x, 0, endXY.y);
		real3 vXCenter = _aabb.getCenter();
		lifeiSpatialReference_2 spr;
		real2 vWorld = spr.worldToLongLat(real2(vXCenter.x, vXCenter.z));
		int2 vTileID = spr.getKey(level, vWorld.x, vWorld.y);
		_tileID._lev = level;
		_tileID._col = vTileID.x;
		_tileID._row = vTileID.y;
		_parent = parent;
		_startXY = startXY;
		_endXY = endXY;

		for (int i = 0; i < 4; i++)
		{
			_childs[i] = 0;
		}
		_terrain = pInterface;
		_uvStart = float2(0, 0);
		_uvEnd = float2(1.0f, 1.0f);
		_terrain->getCounts()._nodes++;
		_flag = 0;
		_flag &= ~FLAG_HAS_IMAGE;
		//该四叉树节点如果没有父节点，说明当前四叉树节点为根节点，要求获取根节点
		if (NULL == parent)
		{
			_terrain->request(this);
			return;
		}

		//在三维纹理坐标系中计算相对根节点的uv坐标和中心点
		float2 vHalf = (_parent->_uvEnd - _parent->_uvStart) * 0.5f;
		float2 centerXYZ = (_parent->_uvStart + _parent->_uvEnd) * 0.5f;
		_textureID = _parent->_textureID;
		switch (corner)
		{
		case CELL::lifeiQuadTree_2::CHILD_LT:
			_uvStart = float2(centerXYZ.x - vHalf.x, centerXYZ.y);
			_uvEnd = float2(centerXYZ.x, centerXYZ.y + vHalf.y);
			break;

		case CELL::lifeiQuadTree_2::CHILD_RT:
			_uvStart = float2(centerXYZ.x, centerXYZ.y);
			_uvEnd = float2(centerXYZ.x + vHalf.x , centerXYZ.y + vHalf.y);
			break;

		case CELL::lifeiQuadTree_2::CHILD_LB:
			_uvStart = float2(centerXYZ.x - vHalf.x, centerXYZ.y - vHalf.y);
			_uvEnd = float2(centerXYZ.x, centerXYZ.y);
			break;

		case CELL::lifeiQuadTree_2::CHILD_RB:
			_uvStart = float2(centerXYZ.x, centerXYZ.y - vHalf.y);
			_uvEnd = float2(centerXYZ.x + vHalf.x, centerXYZ.y);
			break;
		default:
			break;
		}

		if (_parent->hasFlag(FLAG_HAS_IMAGE))
		{
			_flag |= FLAG_RENDER;
		}

		//如果不是根节点，则看看是否能生成纹理，不能生成，则用父节点的纹理
		_textureID = _parent->_textureID;
		_terrain->request(this);
	}

	lifeiQuadTree_2::~lifeiQuadTree_2()
	{
		_terrain->cancelRequest(this);
		_terrain->getCounts()._nodes--;
		if (_textureID != -1 && _flag & FLAG_HAS_IMAGE )
		{
			_terrain->releaseTexture(_textureID);
		}

		for (int i = 0; i < 4; i++)
		{
			if (_childs[i])
			{
				delete _childs[i];
			}
		}
	}

	void lifeiQuadTree_2::getAllRenderableNode(arrayNode & nodes)
	{
		if (hasChild())
		{
			_childs[0]->getAllRenderableNode(nodes);
			_childs[1]->getAllRenderableNode(nodes);
			_childs[2]->getAllRenderableNode(nodes);
			_childs[3]->getAllRenderableNode(nodes);
		}
		else
		{
			if (hasFlag(FLAG_RENDER))
			{
				nodes.push_back(this);
			}
		}
	}

	void lifeiQuadTree_2::update(lifeiContext_2 & context)
	{
		//判断包围盒是否与摄像机六棱锥相交
		CELL::real minX = _aabb._minimum.x;
		CELL::real maxX = _aabb._maximum.x;
		CELL::real minY = _aabb._minimum.y;
		CELL::real maxY = _aabb._maximum.y;
		CELL::real minZ = _aabb._minimum.z;
		CELL::real maxZ = _aabb._maximum.z;

		bool bIntersect = context._frustum.cubeInFrustum_2(minX, maxX, minY, maxY, minZ, maxZ);
		if ( bIntersect)
		{
			_flag &= ~FLAG_HAS_CULL;
		}
		else
		{
			_flag |= FLAG_HAS_CULL;
		}
		//如果剔除标志，则销毁子节点
		if(hasFlag(FLAG_HAS_CULL))
		{
			//收回子节点
			for (int i = 0; i < 4; i++)
			{
				if (NULL == _childs[i])
				{
					continue;
				}
				delete _childs[i];
				_childs[i] = NULL;
			}
			return;
		}
		//计算包围盒中心到摄像机的位置,
		lifeiCamera& camera = context._camera;
		real3 centerXYZ = _aabb.getCenter();
		real3 sizeXYZ = _aabb.getSize();

		real fSize = sizeXYZ.x;
		real dis = CELL::length(centerXYZ - camera._eye);
		//如果距离/瓦片大小太大，则不处理
		if (dis / fSize >= 3.0)
		{
			return;
		}
		//距离/瓦片大小，随距离进行裂分
		bool bHasChild = this->hasChild();		
		real3 halfSize = _aabb.getHalfSize();
		//如果没有子节点，且当前节点有纹理，则进行裂分子节点
		if (!bHasChild && hasImage())
		{
			_childs[CHILD_LT] = new lifeiQuadTree_2(
				_terrain,
				this,
				real2(centerXYZ.x - halfSize.x, centerXYZ.z),
				real2(centerXYZ.x, centerXYZ.z + halfSize.z),
				_tileID._lev + 1,
				CHILD_LT
				);
			_childs[CHILD_RT] = new lifeiQuadTree_2(
				_terrain,
				this,
				real2(centerXYZ.x, centerXYZ.z),
				real2(centerXYZ.x + halfSize.x, centerXYZ.z + halfSize.z),
				_tileID._lev + 1,
				CHILD_RT
			);
			_childs[CHILD_LB] = new lifeiQuadTree_2(
				_terrain,
				this,
				real2(centerXYZ.x - halfSize.x, centerXYZ.z - halfSize.z),
				real2(centerXYZ.x, centerXYZ.z ),
				_tileID._lev + 1,
				CHILD_LB
			);

			_childs[CHILD_RB] = new lifeiQuadTree_2(
				_terrain,
				this,
				real2(centerXYZ.x , centerXYZ.z - halfSize.z),
				real2(centerXYZ.x + halfSize.x, centerXYZ.z),
				_tileID._lev + 1,
				CHILD_RB
			);

			return;
		}
	
		//如果有子节点，则递归更新子节点，如果没有子节点，则说明是叶子节点，加上绘制标志，考虑到当前节点没有图片，可以使用父节点图片的情况
		//这里是4个子节点同时生成，所以不考虑细分某个子节点不存在而其他子节点存在的情形
		for (int i = 0; i < 4; i++)
		{
			if (NULL == _childs[i])
			{
				_flag &= FLAG_RENDER;
				break;
			}		
			_childs[i]->update(context);
		}
	
	}

	bool lifeiQuadTree_2::hasChild()
	{
		return _childs[0] ? true : false;
	}

	bool lifeiQuadTree_2::hasImage()
	{
		return (_flag & FLAG_HAS_IMAGE) ? true : false;
	}

	bool lifeiQuadTree_2::hasFlag(uint flag)
	{
		return (_flag & flag) ? true : false;
	}

	bool lifeiQuadTree_2::hasNoFlag(uint flag)
	{
		return !hasFlag(flag);
	}

	void lifeiQuadTree_2::updateTexture(unsigned texID)
	{
		_textureID = texID;
		_flag |= FLAG_HAS_IMAGE;
		_flag |= FLAG_RENDER;
		_uvStart = float2(0, 0);
		_uvEnd = float2(1.0f, 1.0f);
	}

}
