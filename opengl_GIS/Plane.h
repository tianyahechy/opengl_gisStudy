#pragma once

#include "tvec3.h"

namespace CELL
{
	template<class T>
	class Plane
	{
	public:
		tvec3<T>		_normal;
		T				_distance;

	public:
		Plane()
		{
			_normal		= tvec3<T>(0, 0, 0);
			_distance	= 0.0f;
		}

		Plane(T x, T y, T z, T w)
		{
			_normal = tvec3<T>(x, y, z);
			T invLen = 1.0f / (_normal).length();
			_normal *= invLen;
			_distance = w * invLen;
		}

		//µ½µãµÄ¾àÀë
		T distance(const tvec3<T> &pos) const
		{
			return dot(_normal, pos) + _distance;
		}
	};
}