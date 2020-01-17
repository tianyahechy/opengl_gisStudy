#pragma once

#include "tvec3.h"

namespace CELL
{
	template <typename T>
	struct tvec4
	{
		T x, y, z, w;

		size_t length() const
		{
			return 4;
		}

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

		tvec4()
		{
			x = T(0);
			y = T(0);
			z = T(0);
			w = T(0);
		}

		tvec4(tvec3<T> const& v, T s)
		{
			x = v.x;
			y = v.y;
			z = v.z;
			w = s;
		}

		tvec4(T s1, T s2, T s3, T s4)
		{
			x = s1;
			y = s2;
			z = s3;
			w = s4;
		}

		template<typename U>
		tvec4<T> & operator /= (U const & s)
		{
			this->x /= T(s);
			this->y /= T(s);
			this->z /= T(s);
			this->w /= T(s);
			return *this;
		}
	};
	
	template<typename T>
	tvec4<T> operator+ (tvec4<T> const& v1, tvec4<T> const& v2)
	{
		return tvec4<T>(
			v1.x + v2.x,
			v1.y + v2.y,
			v1.z + v2.z,
			v1.w + v2.w
			);
	}

	template<typename T>
	tvec4<T> operator* (tvec4<T> const& v, T const& s)
	{
		return tvec4<T>(
			v.x * s,
			v.y * s,
			v.z * s,
			v.w * s
			);
	}

	template<typename T>
	tvec4<T> operator/ (tvec4<T> const& v, T const& s)
	{
		return tvec4<T>(
			v.x / s,
			v.y / s,
			v.z / s,
			v.w / s
			);
	}

	typedef tvec4<unsigned short>	ushort4;
	typedef tvec4<unsigned short>	half4;
	typedef tvec4<int>				int4;
	typedef tvec4<float>			float4;
	typedef tvec4<double>			double4;
	typedef tvec4<real>				real4;
}
