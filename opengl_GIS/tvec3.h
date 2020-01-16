#pragma once
#include "lifeiMathUtil.h"

namespace CELL
{
	template <typename T>
	struct tvec3
	{
		typedef T           value_type;

		T x;
		T y;
		T z;

		size_t length() const
		{
			return 3;
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

		inline tvec3()
		{
			x = T(0);
			y = T(0);
			z = T(0);
		}
		inline tvec3(T s)
		{
			x = s;
			y = s;
			z = s;
		}

		template<typename A, typename B, typename C>
		tvec3(A a, B b, C c)
		{
			x = T(a);
			y = T(b);
			z = T(c);
		}

		template<typename U>
		tvec3<T>& operator += (tvec3<U> const& v)
		{
			this->x += T(v.x);
			this->y += T(v.y);
			this->z += T(v.z);
			return *this;
		}

		template<typename U>
		tvec3<T>& operator -= (tvec3<U> const& v)
		{
			this->x -= T(v.x);
			this->y -= T(v.y);
			this->z -= T(v.z);
			return *this;
		}

		template<typename U>
		tvec3<T>& operator *= (U const& s)
		{
			this->x *= T(s);
			this->y *= T(s);
			this->z *= T(s);
			return *this;
		}
	};

	template <typename T>
	tvec3<T> operator + (tvec3<T> const & v1, tvec3<T> const& v2)
	{
		return tvec3<T>(
			v1.x + T(v2.x),
			v1.y + T(v2.y),
			v1.z + T(v2.z));
	}

	template <typename T>
	tvec3<T> operator - (tvec3<T> const & v1, tvec3<T> const& v2)
	{
		return tvec3<T>(
			v1.x - T(v2.x),
			v1.y - T(v2.y),
			v1.z - T(v2.z));
	}

	template <typename T>
	tvec3<T> operator * (tvec3<T> const & v1, T const& s)
	{
		return tvec3<T>(
			v1.x * T(s),
			v1.y * T(s),
			v1.z * T(s));
	}

	template <typename T>
	tvec3<T> operator * ( T const& s, tvec3<T> const & v1)
	{
		return tvec3<T>(
			T(s) * v1.x,
			T(s) *v1.y,
			T(s) *v1.z );
	}
	typedef tvec3<unsigned char>		uchar3;
	typedef tvec3<byte>					byte3;
	typedef tvec3<unsigned short>		ushort3;

	typedef tvec3<unsigned int>			uint3;
	typedef tvec3<int>					int3;
	typedef tvec3<unsigned>				uint3;

	typedef tvec3<float>				float3;
	typedef tvec3<double>				double3;
	typedef tvec3<real>					real3;
	typedef tvec3<unsigned short>		half3;

}
