#pragma once
#include "tvec3.h"

namespace CELL
{
	template <typename T>	
	struct tmat3x3
	{
	private:
		tvec3<T> value[3];

	public:
		size_t length() const
		{
			return 3;
		}

		tmat3x3(T const& s)
		{
			T const Zero(0);
			this->value[0] = tvec3<T>(s, Zero, Zero);
			this->value[1] = tvec3<T>( Zero, s, Zero);
			this->value[2] = tvec3<T>(Zero, Zero, s);
		}

		tvec3<T> const& operator[] (size_t i) const
		{
			assert(i < this->length());
			return this->value[i];
		}

	};
	
	typedef tmat3x3<float>	matrix3;
	typedef tmat3x3<double>	matrix3d;
	typedef tmat3x3<real>	matrix3r;
}