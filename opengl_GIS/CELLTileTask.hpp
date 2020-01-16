#pragma once
#include "CELLTask.hpp"
#include "CELLMath.hpp"
#include "lifeiImage.h"
#include "lifeiTileId.h"
namespace CELL
{
	class lifeiQuadTree;
	class CELLTileTask : public CELLTask
	{
	public:
		lifeiQuadTree * _node;
		lifeiTileId		_tileId;
		lifeiImage		_image;
	};
}
