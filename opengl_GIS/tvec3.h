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
	
	template<typename T>
	typename tvec3<T>::value_type length(tvec3<T> const& v)
	{
		typename tvec3<T>::value_type sqr = v.x * v.x + v.y * v.y + v.z * v.z;
		return sqrt(sqr);
	}

	template <typename T>
	typename tvec3<T>::value_type dot(tvec3<T> const& x, tvec3<T> const& y)
	{
		return x.x * y.x + x.y * y.y + x.z * y.z;
	}

	template<typename T>
	tvec3<T> cross(tvec3<T> const& x, tvec3<T> const& y)
	{
		return tvec3<T>(
			x.y * y.z - y.y * x.z,
			x.z * y.x - y.z * x.x,
			x.x * y.y - y.x * x.y
			);
	}

	template <typename T>
	tvec3<T> normalize(tvec3<T> const & x)
	{
		typename tvec3<T>::value_type sqr = x.x * x.x + x.y * x.y + x.z * x.z;
		return x * inversesqrt(sqr);
	}

	
	//射线与三角形相交
	template <typename T>
	bool intersectTriangle(
		const tvec3<T>& origin,
		const tvec3<T>& dir,
		const tvec3<T>& v0,
		const tvec3<T>& v1,
		const tvec3<T>& v2,
		T * t,
		T * u,
		T * v
		)
	{
		tvec3<T> edge1 = v1 - v0;
		tvec3<T> edge2 = v2 - v0;

		tvec3<T> pvec = cross(dir, edge2);

		T det = dot(edge1, pvec);
		tvec3<T> tvec;
		if (det > 0)
		{
			tvec = origin - v0;
		}
		else
		{
			tvec = v0 - origin;
			det = -det;
		}

		if (det < 0.00000001)
		{
			return false;
		}

		*u = dot(tvec, pvec);
		if (*u < 0.0f || *u > det)
		{
			return false;
		}

		tvec3<T> qvec = cross(dir, edge1);
		*v = dot(dir, pvec);
		if (*v < T(0.0f) || *u + *v> det)
		{
			return false;
		}

		*t = dot(edge2, qvec);
		T fInvDet = T(1.0) / det;

		*t *= fInvDet;
		*u *= fInvDet;
		*v *= fInvDet;

		return true;
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
