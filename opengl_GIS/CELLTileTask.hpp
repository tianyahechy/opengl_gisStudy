#pragma once
#include "CELLTask.hpp"
#include "CELLMath.hpp"
#include "lifeiImage.h"
namespace CELL
{
	class lifeiQuadTree;
	class CELLTileTask : public CELLTask
	{
	public:
		lifeiQuadTree * _node;
		TileId			_tileId;
		lifeiImage		_image;
	};
}
