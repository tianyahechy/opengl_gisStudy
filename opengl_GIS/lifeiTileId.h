#pragma once
#include "lifeiMathUtil.h"

namespace CELL
{
	union lifeiTileId
	{
		struct
		{
			int64 _row : 28;
			int64 _col : 28;
			int64 _lev : 8;
		};
		int64 _index;
	};
}
