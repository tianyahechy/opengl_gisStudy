#pragma once

#include "tvec4.h"
#include "tmat3x3.h"

namespace CELL
{ 
	template<typename T>
	struct tmat4x4
	{
		typedef T				value_type;
		typedef std::size_t		size_type;
		typedef tvec4<T>		col_type;
		typedef tvec4<T>		row_type;
		typedef tmat4x4<T>		type;
		typedef tmat4x4<T>		transpose_type;

	public:

		tmat4x4<T>  inverse() const
		{
			value_type subFactor00 = this->value[2][2] * this->value[3][3] - this->value[3][2] * this->value[2][3];
			value_type subFactor01 = this->value[2][1] * this->value[3][3] - this->value[3][1] * this->value[2][3];
			value_type subFactor02 = this->value[2][1] * this->value[3][2] - this->value[3][1] * this->value[2][2];
			value_type subFactor03 = this->value[2][0] * this->value[3][3] - this->value[3][0] * this->value[2][3];
			value_type subFactor04 = this->value[2][0] * this->value[3][2] - this->value[3][0] * this->value[2][2];
			value_type subFactor05 = this->value[2][0] * this->value[3][1] - this->value[3][0] * this->value[2][1];
			value_type subFactor06 = this->value[1][2] * this->value[3][3] - this->value[3][2] * this->value[1][3];
			value_type subFactor07 = this->value[1][1] * this->value[3][3] - this->value[3][1] * this->value[1][3];
			value_type subFactor08 = this->value[1][1] * this->value[3][2] - this->value[3][1] * this->value[1][2];
			value_type subFactor09 = this->value[1][0] * this->value[3][3] - this->value[3][0] * this->value[1][3];
			value_type subFactor10 = this->value[1][0] * this->value[3][2] - this->value[3][0] * this->value[1][2];
			value_type subFactor11 = this->value[1][1] * this->value[3][3] - this->value[3][1] * this->value[1][3];
			value_type SubFactor12 = this->value[1][0] * this->value[3][1] - this->value[3][0] * this->value[1][1];
			value_type subFactor13 = this->value[1][2] * this->value[2][3] - this->value[2][2] * this->value[1][3];
			value_type subFactor14 = this->value[1][1] * this->value[2][3] - this->value[2][1] * this->value[1][3];
			value_type subFactor15 = this->value[1][1] * this->value[2][2] - this->value[2][1] * this->value[1][2];
			value_type subFactor16 = this->value[1][0] * this->value[2][3] - this->value[2][0] * this->value[1][3];
			value_type subFactor17 = this->value[1][0] * this->value[2][2] - this->value[2][0] * this->value[1][2];
			value_type subFactor18 = this->value[1][0] * this->value[2][1] - this->value[2][0] * this->value[1][1];

			tmat4x4<T> res(
				+this->value[1][1] * subFactor00 - this->value[1][2] * subFactor01 + this->value[1][3] * subFactor02,
				-this->value[1][0] * subFactor00 + this->value[1][2] * subFactor03 - this->value[1][3] * subFactor04,
				+this->value[1][0] * subFactor01 - this->value[1][1] * subFactor03 + this->value[1][3] * subFactor05,
				-this->value[1][0] * subFactor02 + this->value[1][1] * subFactor04 - this->value[1][2] * subFactor05,

				-this->value[0][1] * subFactor00 + this->value[0][2] * subFactor01 - this->value[0][3] * subFactor02,
				+this->value[0][0] * subFactor00 - this->value[0][2] * subFactor03 + this->value[0][3] * subFactor04,
				-this->value[0][0] * subFactor01 + this->value[0][1] * subFactor03 - this->value[0][3] * subFactor05,
				+this->value[0][0] * subFactor02 - this->value[0][1] * subFactor04 + this->value[0][2] * subFactor05,

				+this->value[0][1] * subFactor06 - this->value[0][2] * subFactor07 + this->value[0][3] * subFactor08,
				-this->value[0][0] * subFactor06 + this->value[0][2] * subFactor09 - this->value[0][3] * subFactor10,
				+this->value[0][0] * subFactor11 - this->value[0][1] * subFactor09 + this->value[0][3] * SubFactor12,
				-this->value[0][0] * subFactor08 + this->value[0][1] * subFactor10 - this->value[0][2] * SubFactor12,

				-this->value[0][1] * subFactor13 + this->value[0][2] * subFactor14 - this->value[0][3] * subFactor15,
				+this->value[0][0] * subFactor13 - this->value[0][2] * subFactor16 + this->value[0][3] * subFactor17,
				-this->value[0][0] * subFactor14 + this->value[0][1] * subFactor16 - this->value[0][3] * subFactor18,
				+this->value[0][0] * subFactor15 - this->value[0][1] * subFactor17 + this->value[0][2] * subFactor18);

			value_type determinant =
				+this->value[0][0] * res[0][0]
				+ this->value[0][1] * res[1][0]
				+ this->value[0][2] * res[2][0]
				+ this->value[0][3] * res[3][0];

			res /= determinant;
			return res;
		}

	private:
		col_type value[4];

	public:
		size_type length() const
		{
			return 4;
		}

		size_type col_size()
		{
			return 4;
		}

		size_t row_size()
		{
			return 4;
		}

		T * dataPtr()
		{
			return (T*)value;
		}

		col_type& operator[] (size_type i)
		{
			assert(i < this->length());
			return this->value[i];
		}


		col_type const & operator[] (size_type i) const
		{
			assert(i < this->length());
			return this->value[i];
		}

		tmat4x4(tmat3x3<T> const& m)
		{
			this->value[0] = col_type(m[0], value_type(0));
			this->value[1] = col_type(m[1], value_type(0));
			this->value[2] = col_type(m[2], value_type(0));
			this->value[3] = col_type(value_type(0), value_type(0), value_type(0), value_type(1));
			
		}
		tmat4x4()
		{

		}

		tmat4x4(
			value_type const& x0, value_type const& y0, value_type const& z0, value_type const& w0,
			value_type const& x1, value_type const& y1, value_type const& z1, value_type const& w1,
			value_type const& x2, value_type const& y2, value_type const& z2, value_type const& w2,
			value_type const& x3, value_type const& y3, value_type const& z3, value_type const& w3
			)
		{
			this->value[0] = col_type(x0, y0, z0, w0);
			this->value[1] = col_type(x1, y1, z1, w1);
			this->value[2] = col_type(x2, y2, z2, w2);
			this->value[3] = col_type(x3, y3, z3, w3);
		}

		T const* data() const
		{
			return &this->value[0][0];
		}

		template< typename U>
		tmat4x4 & operator /= (U const& s)
		{
			this->value[0] /= s;
			this->value[1] /= s;
			this->value[2] /= s;
			this->value[3] /= s;
			return *this;
		}

		tmat4x4& rotate(T angle, tvec3<T> const& v)
		{
			T a = (T)DEG2RAD(angle);
			T c = cos(a);
			T s = sin(a);

			tvec3<T> axis = normalize(v);
			tvec3<T> temp = (T(1) - c) * axis;
			this->value[0][0] = c + temp[0] * axis[0];
			this->value[0][1] = 0 + temp[0] * axis[1] + s * axis[2];
			this->value[0][2] = 0 + temp[0] * axis[2] - s * axis[1];
			this->value[0][3] = 0;

			this->value[1][0] = 0 + temp[1] * axis[0] - s * axis[2];
			this->value[1][1] = c + temp[1] * axis[1];
			this->value[1][2] = 0 + temp[1] * axis[2] + s * axis[0];
			this->value[1][3] = 0;

			this->value[2][0] = 0 + temp[2] * axis[0] + s * axis[1];
			this->value[2][1] = 0 + temp[2] * axis[1] - s * axis[0];
			this->value[2][2] = c + temp[2] * axis[2];
			this->value[2][3] = 0;

			this->value[3][0] = 0;
			this->value[3][1] = 0;
			this->value[3][2] = 0;
			this->value[3][3] = 1;
			return  *this;

		}

		tmat4x4<T> transpose() const
		{
			return tmat4x4<T>(
				this->value[0][0], this->value[1][0], this->value[2][0], this->value[3][0],
				this->value[0][1], this->value[1][1], this->value[2][1], this->value[3][1],
				this->value[0][2], this->value[1][2], this->value[2][2], this->value[3][2],
				this->value[0][3], this->value[1][3], this->value[2][3], this->value[3][3]
				);
		}

	};

	typedef tmat4x4<float>			matrix4;
	typedef tmat4x4<double>			matrix4d;
	typedef tmat4x4<real>			matrix4r;

	template<typename T>
	tvec3<T> operator* (tvec3<T> const& v, tmat4x4<T> const& mat)
	{
		return tvec3<T>(
			v.x * mat[0][0] + v.y * mat[1][0] + v.z * mat[2][0] + 1 * mat[3][0],
			v.x * mat[0][1] + v.y * mat[1][1] + v.z * mat[2][1] + 1 * mat[3][1],
			v.x * mat[0][2] + v.y * mat[1][2] + v.z * mat[2][2] + 1 * mat[3][2]
			);
	}

	template< typename T>
	typename tmat4x4<T>::col_type operator * (tmat4x4<T> const& m, typename tmat4x4<T>::row_type const& v)
	{
		return typename tmat4x4<T>::col_type(
			m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z + m[3][0] * v.w,
			m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z + m[3][1] * v.w,
			m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z + m[3][2] * v.w,
			m[0][3] * v.x + m[1][3] * v.y + m[2][3] * v.z + m[3][3] * v.w
			);
	}

	template< typename T>
	typename tmat4x4<T>::row_type operator * ( typename tmat4x4<T>::col_type const& v, tmat4x4<T> const& m)
	{
		return typename tmat4x4<T>::row_type(
			m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w,
			m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w,
			m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w,
			m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w
			);	
	}	

	template<typename T>
	tmat4x4<T> operator * (tmat4x4<T> const& m1, tmat4x4<T> const& m2)
	{
		typename tmat4x4<T>::col_type const srcA0 = m1[0];
		typename tmat4x4<T>::col_type const srcA1 = m1[1];
		typename tmat4x4<T>::col_type const srcA2 = m1[2];
		typename tmat4x4<T>::col_type const srcA3 = m1[3];

		typename tmat4x4<T>::col_type const srcB0 = m2[0];
		typename tmat4x4<T>::col_type const srcB1 = m2[1];
		typename tmat4x4<T>::col_type const srcB2 = m2[2];
		typename tmat4x4<T>::col_type const srcB3 = m2[3];

		tmat4x4<T> res;
		res[0] = srcA0 * srcB0[0] + srcA1 * srcB0[1] + srcA2 * srcB0[2] + srcA3 * srcB0[3];
		res[1] = srcA0 * srcB1[0] + srcA1 * srcB1[1] + srcA2 * srcB1[2] + srcA3 * srcB1[3];
		res[2] = srcA0 * srcB2[0] + srcA1 * srcB2[1] + srcA2 * srcB2[2] + srcA3 * srcB2[3];
		res[3] = srcA0 * srcB3[0] + srcA1 * srcB3[1] + srcA2 * srcB3[2] + srcA3 * srcB3[3];
		return res;
	}
}