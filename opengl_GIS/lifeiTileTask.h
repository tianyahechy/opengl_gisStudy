#pragma once

#include "lifeiTask_2.h"
#include "lifeiImage.h"
#include "lifeiTileId.h"

namespace CELL
{
	class lifeiQuadTree;
	class lifeiTileTask : public lifeiTask_2 //应该是当前要处理的瓦片的内容
	{
	public:
		lifeiQuadTree * _node;
		lifeiTileId		_tileId;
		lifeiImage		_image;
	};
}
