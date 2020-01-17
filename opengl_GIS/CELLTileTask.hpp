#pragma once
#include "lifeiTask.h"
#include "CELLMath.hpp"
#include "lifeiImage.h"
#include "lifeiTileId.h"
namespace CELL
{
	class lifeiQuadTree;
	class CELLTileTask : public lifeiTask
	{
	public:
		lifeiQuadTree * _node;
		lifeiTileId		_tileId;
		lifeiImage		_image;
	};
}
