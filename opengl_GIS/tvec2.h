#pragma once
#include "lifeiMathUtil.h"

namespace CELL
{
	template <typename T>
	struct tvec2
	{
		T x;
		T y;

		T& operator[] (size_t i)
		{
			assert(i < this->length());
			return (&x)[i];
		}

		T const& operator[] (size_t i) const
		{
			assert(i < this->length());
			return (&x)[i];
		}

		tvec2()
		{
			x = T(0);
			y = T(0);
		}
		tvec2(T const& s1, T const& s2)
		{
			x = s1;
			y = s2;
		}

	};

	template <typename T>
	tvec2<T> operator + (tvec2<T> const & v1, tvec2<T> const& v2)
	{
		return tvec2<T>(v1.x + T(v2.x),
			v1.y + T(v2.y));
	}

	template <typename T>
	tvec2<T> operator - (tvec2<T> const & v1, tvec2<T> const& v2)
	{
		return tvec2<T>(v1.x - T(v2.x),
			v1.y - T(v2.y));
	}

	template <typename T>
	tvec2<T> operator * (tvec2<T> const & v1, T const& s)
	{
		return tvec2<T>(v1.x * T(s),
			v1.y * T(s));
	}

	typedef tvec2<short>				short2;
	typedef tvec2<unsigned short>		ushort2;
	typedef tvec2<unsigned int>			uint2;
	typedef tvec2<int>					int2;
	typedef tvec2<float>				float2;
	typedef tvec2<double>				double2;
	typedef tvec2<real>					real2;
	typedef tvec2<unsigned short>		half2;


}
