#pragma once
#include "tvec2.h"

namespace CELL
{
	template <typename T>
	class AxisAlignedBox2d
	{

	public:
		tvec2<T>	_minimum;
		tvec2<T>	_maximum;

	public:
		AxisAlignedBox2d()
		{
			_minimum = tvec2<T>(-0.5, -0.5);
			_maximum = tvec2<T>(0.5, 0.5);

		}
		~AxisAlignedBox2d()
		{

		}
		void setExtents(
			T mx, T my,
			T Mx, T My
		)
		{
			_minimum.x = mx;
			_minimum.y = my;

			_maximum.x = Mx;
			_maximum.y = My;
		}

		tvec2<T> getCenter() const
		{
			return tvec2<T>(
				(_maximum.x + _minimum.x) * 0.5,
				(_maximum.y + _minimum.y) * 0.5
				);
		}
		tvec2<T> getSize() const
		{
			return _maximum - _minimum;
		}
		tvec2<T> getHalfSize() const
		{
			return getSize() * T(0.5);
		}
		inline bool intersects(const AxisAlignedBox2d& b2) const
		{
			if (_maximum.x < b2._minimum.x)
			{
				return false;
			}
			if (_maximum.y < b2._minimum.y)
			{
				return false;
			}

			if (_minimum.x > b2._maximum.x)
			{
				return false;
			}
			if (_minimum.y > b2._maximum.y)
			{
				return false;
			}
			return true;
		}

	};

	typedef AxisAlignedBox2d<real>	aabb2dr;
	typedef AxisAlignedBox2d<float> aabb2df;

}

