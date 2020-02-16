#pragma once
#include "lifeiTask_2.h"
#include "lifeiImage.h"
#include "lifeiTileId.h"

namespace CELL
{
	class lifeiQuadTree;
	class lifeiTileTask_2 : public lifeiTask_2 //当前要处理的瓦片的内容（各种属性）
	{
	public:
		lifeiQuadTree*	_node;
		lifeiTileId		_tileId;
		lifeiImage		_image;
	};
}