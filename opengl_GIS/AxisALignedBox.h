#pragma once
#include "tvec3.h"

namespace CELL
{
	template <typename T>
	class AxisAlignedBox
	{
	public:
		enum Extent
		{
			EXTENT_NULL,
			EXTENT_FINITE,
			EXTENT_INFINITE
		};

	public:
		tvec3<T>	_minimum;
		tvec3<T>	_maximum;
		Extent		_extent;

	public:
		AxisAlignedBox()
		{
			_minimum = tvec3<T>(-0.5, -0.5, -0.5);
			_maximum = tvec3<T>(0.5, 0.5, 0.5);
			_extent = EXTENT_NULL;

		}
		~AxisAlignedBox()
		{

		}
		void setExtents(
			T mx, T my, T mz,
			T Mx, T My, T Mz
		)
		{
			_minimum.x = mx;
			_minimum.y = my;
			_minimum.z = mz;

			_maximum.x = Mx;
			_maximum.y = My;
			_maximum.z = Mz;

			_extent = EXTENT_FINITE;

		}

		tvec3<T> getCenter() const
		{
			return tvec3<T>(
				(_maximum.x + _minimum.x) * 0.5,
				(_maximum.y + _minimum.y) * 0.5,
				(_maximum.z + _minimum.z) * 0.5
				);
		}
		tvec3<T> getSize() const
		{
			return _maximum - _minimum;
		}
		tvec3<T> getHalfSize() const
		{
			return getSize() * T(0.5);
		}

	};

	typedef AxisAlignedBox<real>	aabb3dr;
	typedef AxisAlignedBox<float>   aabb3df;

}

