#pragma once
#include "lifeiMathUtil.h"

namespace CELL
{

    template <typename T>
    struct tvec2
    {
        typedef T               value_type;
        typedef std::size_t     size_type;
        typedef tvec2<T>        type;

        value_type  x;
        value_type  y;

        value_type & operator[](size_type i)
        {
            assert(i < this->length());
            return (&x)[i];
        }

        value_type const & operator[]( size_type i ) const
        {
            assert(i < this->length());
            return (&x)[i];
        }
        
		tvec2() :
            x(value_type(0)),
            y(value_type(0))
        {}
	
        tvec2(value_type const & s1, value_type const & s2) :
            x(s1),
            y(s2)
        {}
    };
	
    template <typename T> 
    tvec2<T> operator+ (tvec2<T> const & v1, tvec2<T> const & v2)
    {
        return tvec2<T>(
            v1.x + T(v2.x),
            v1.y + T(v2.y));
    }
		
    template <typename T> 
    tvec2<T> operator- (tvec2<T> const & v1, tvec2<T> const & v2)
    {
        return tvec2<T>(
            v1.x - T(v2.x),
            v1.y - T(v2.y));
    }
		
    template <typename T> 
    tvec2<T> operator* (tvec2<T> const & v, T const & s)
    {
        return tvec2<T>(
            v.x * T(s),
            v.y * T(s));
    }

    template <typename T>
    struct tvec3
    {	
        typedef T               value_type;
        typedef std::size_t     size_type;
        typedef tvec3<T>        type;

        value_type  x;
        value_type  y;
        value_type  z;

        size_type   length() const
        {
            return 3;
        }

        value_type & operator[](size_type i)
        {
            assert(i < this->length());
            return (&x)[i];
        }

        value_type const & operator[](size_type i) const
        {
            assert(i < this->length());
            return (&x)[i];
        }
		
        inline tvec3() :
            x(value_type(0)),
            y(value_type(0)),
            z(value_type(0))
        {}

        inline tvec3(value_type s) :
            x(s),
            y(s),
            z(s)
        {}
	
        template <typename A, typename B, typename C> 
        tvec3(A x, B y, C z) :
            x(value_type(x)),
            y(value_type(y)),
            z(value_type(z))
        {}

        template <typename U> 
        tvec3<T> & operator+=(tvec3<U> const & v)
        {
            this->x += T(v.x);
            this->y += T(v.y);
            this->z += T(v.z);
            return *this;
        }
	
        template <typename U> 
        tvec3<T> & operator-=(tvec3<U> const & v)
        {
            this->x -= T(v.x);
            this->y -= T(v.y);
            this->z -= T(v.z);
            return *this;
        }
		
        template <typename U> 
        tvec3<T> & operator*=(U const & s)
        {
            this->x *= T(s);
            this->y *= T(s);
            this->z *= T(s);
            return *this;
        }
    };

    /**
    *   射线与三角形相交
    */
    template<typename T>
    bool intersectTriangle( 
                            const tvec3<T>& orig, 
                            const tvec3<T>& dir,
                            const tvec3<T>& v0, 
                            const tvec3<T>& v1, 
                            const tvec3<T>& v2,
                            T* t, 
                            T* u,
                            T* v 
                            )
    {
        // Find vectors for two edges sharing vert0
        tvec3<T>    edge1   =   v1 - v0;
        tvec3<T>    edge2   =   v2 - v0;

        // Begin calculating determinant - also used to calculate U parameter
        tvec3<T>    pvec;
        pvec    =   cross(dir, edge2 );

        // If determinant is near zero, ray lies in plane of triangle
        T   det =   dot( edge1,pvec );

        tvec3<T>    tvec;
        if( det > 0 )
        {
            tvec    =   orig - v0;
        }
        else
        {
            tvec    =   v0 - orig;
            det     =   -det;
        }
        if( det < 0.0000000001)
            return false;
        // Calculate U parameter and test bounds
        *u  =   dot( tvec, pvec );
        if( *u < 0.0f || *u > det )
            return false;

        // Prepare to test V parameter
        tvec3<T>    qvec;
        qvec    =   cross(tvec, edge1 );

        // Calculate V parameter and test bounds
        *v  =   dot( dir, qvec );
        if( *v < T(0.0f) || *u + *v > det )
            return false;

        *t  =   dot( edge2,qvec );
        T   fInvDet = T(1.0) / det;
        *t  *=  fInvDet;
        *u  *=  fInvDet;
        *v  *=  fInvDet;

        return true;
    }
 
    template <typename T> 
    tvec3<T> operator+ (tvec3<T> const & v1, tvec3<T> const & v2)
    {
        return tvec3<T>(
            v1.x + T(v2.x),
            v1.y + T(v2.y),
            v1.z + T(v2.z));
    }	
	
    template <typename T> 
    tvec3<T> operator- (tvec3<T> const & v1, tvec3<T> const & v2)
    {
        return tvec3<T>(
            v1.x - T(v2.x),
            v1.y - T(v2.y),
            v1.z - T(v2.z));
    }
	
    template <typename T> 
    tvec3<T> operator*(tvec3<T> const & v, T const & s)
    {
        return tvec3<T>(
            v.x * T(s),
            v.y * T(s),
            v.z * T(s));
    }
	
    template <typename T> 
    tvec3<T> operator* (T const & s, tvec3<T> const & v)
    {
        return tvec3<T>(
            T(s) * v.x,
            T(s) * v.y,
            T(s) * v.z);
    }
	
	template <typename T>
    struct tvec4
    {
        typedef T           value_type;
        typedef std::size_t size_type;
        typedef tvec4<T>  type;

        value_type x, y, z, w;

        size_type length() const
        {
            return 4;
        }
		
        value_type & operator[](size_type i)
        {
            assert(i < this->length());
            return (&x)[i];
        }
		
        value_type const & operator[](size_type i) const
        {
            assert(i < this->length());
            return (&x)[i];
        }
		
        tvec4() :
            x(value_type(0)),
            y(value_type(0)),
            z(value_type(0)),
            w(value_type(0))
        {}
		
        tvec4(tvec3<T> const& v, T s) :
            x(v.x),
            y(v.y),
            z(v.z),
            w(s)
        {}
	
        tvec4
            (
            value_type s1, 
            value_type s2, 
            value_type s3, 
            value_type s4
            ) :
            x(s1),
            y(s2),
            z(s3),
            w(s4)
        {}
		
        template <typename U> 
        tvec4<T> & operator/=(U const & s)
        {
            this->x /= T(s);
            this->y /= T(s);
            this->z /= T(s);
            this->w /= T(s);
            return *this;
        }
    };
	
    template <typename T> 
    tvec4<T> operator+ (tvec4<T> const & v1, tvec4<T> const & v2)
    {
        return tvec4<T>(
            v1.x + v2.x,
            v1.y + v2.y,
            v1.z + v2.z,
            v1.w + v2.w);
    }
	
    template <typename T> 
    tvec4<T> operator* (tvec4<T> const & v, T const & s)
    {
        return tvec4<T>(
            v.x * s,
            v.y * s,
            v.z * s,
            v.w * s);
    }
	
    template <typename T> 
    tvec4<T> operator/ (tvec4<T> const & v, T const & s)
    {
        return tvec4<T>(
            v.x / s,
            v.y / s,
            v.z / s,
            v.w / s);
    }
	
    template <typename T> 
    struct tmat3x3
    {
        typedef T               value_type;
        typedef std::size_t     size_type;
        typedef tvec3<T>      col_type;
        typedef tvec3<T>      row_type;
        typedef tmat3x3<T>    type;
        typedef tmat3x3<T>    transpose_type;

    private:
        // Data
        col_type value[3];

    public:
		
        size_type length() const
        {
            return 3;
        }

        tmat3x3(value_type const & s)
        {
            value_type const Zero(0);
            this->value[0] = col_type(s, Zero, Zero);
            this->value[1] = col_type(Zero, s, Zero);
            this->value[2] = col_type(Zero, Zero, s);
        }
	
        col_type const & operator[](size_type i) const
        {
            assert(i < this->length());
            return this->value[i];
        }
		
    };
   
	template <typename T> 
    struct tmat4x4
    {
        typedef T               value_type;
        typedef std::size_t     size_type;
        typedef tvec4<T>        col_type;
        typedef tvec4<T>        row_type;
        typedef tmat4x4<T>      type;
        typedef tmat4x4<T>      transpose_type;

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
                + this->value[1][1] * subFactor00 - this->value[1][2] * subFactor01 + this->value[1][3] * subFactor02,
                - this->value[1][0] * subFactor00 + this->value[1][2] * subFactor03 - this->value[1][3] * subFactor04,
                + this->value[1][0] * subFactor01 - this->value[1][1] * subFactor03 + this->value[1][3] * subFactor05,
                - this->value[1][0] * subFactor02 + this->value[1][1] * subFactor04 - this->value[1][2] * subFactor05,

                - this->value[0][1] * subFactor00 + this->value[0][2] * subFactor01 - this->value[0][3] * subFactor02,
                + this->value[0][0] * subFactor00 - this->value[0][2] * subFactor03 + this->value[0][3] * subFactor04,
                - this->value[0][0] * subFactor01 + this->value[0][1] * subFactor03 - this->value[0][3] * subFactor05,
                + this->value[0][0] * subFactor02 - this->value[0][1] * subFactor04 + this->value[0][2] * subFactor05,

                + this->value[0][1] * subFactor06 - this->value[0][2] * subFactor07 + this->value[0][3] * subFactor08,
                - this->value[0][0] * subFactor06 + this->value[0][2] * subFactor09 - this->value[0][3] * subFactor10,
                + this->value[0][0] * subFactor11 - this->value[0][1] * subFactor09 + this->value[0][3] * SubFactor12,
                - this->value[0][0] * subFactor08 + this->value[0][1] * subFactor10 - this->value[0][2] * SubFactor12,

                - this->value[0][1] * subFactor13 + this->value[0][2] * subFactor14 - this->value[0][3] * subFactor15,
                + this->value[0][0] * subFactor13 - this->value[0][2] * subFactor16 + this->value[0][3] * subFactor17,
                - this->value[0][0] * subFactor14 + this->value[0][1] * subFactor16 - this->value[0][3] * subFactor18,
                + this->value[0][0] * subFactor15 - this->value[0][1] * subFactor17 + this->value[0][2] * subFactor18);

            value_type determinant = 
                + this->value[0][0] * res[0][0] 
                + this->value[0][1] * res[1][0] 
                + this->value[0][2] * res[2][0] 
                + this->value[0][3] * res[3][0];

            res /= determinant;
            return res;
        }

    private:
        col_type    value[4];
    public:
		
        size_type length() const
        {
            return 4;
        }
        size_type col_size()
        {
            return 4;
        }
        size_type row_size()
        {
            return 4;
        }
		
        T*  dataPtr()
        {
            return  (T*)value;
        }

        col_type & operator[](size_type i)
        {
            assert(i < this->length());
            return this->value[i];
        }
		
        col_type const & operator[](size_type i) const
        {
            assert(i < this->length());
            return this->value[i];
        }
	
        tmat4x4(tmat3x3<T> const & m)
        {
            this->value[0] = col_type(m[0], value_type(0));
            this->value[1] = col_type(m[1], value_type(0));
            this->value[2] = col_type(m[2], value_type(0));
            this->value[3] = col_type(value_type(0), value_type(0), value_type(0), value_type(1));
        }
		
        tmat4x4()
        {
        }
		
        tmat4x4
            (
            value_type const & x0, value_type const & y0, value_type const & z0, value_type const & w0,
            value_type const & x1, value_type const & y1, value_type const & z1, value_type const & w1,
            value_type const & x2, value_type const & y2, value_type const & z2, value_type const & w2,
            value_type const & x3, value_type const & y3, value_type const & z3, value_type const & w3
            )
        {
            this->value[0] = col_type(x0, y0, z0, w0);
            this->value[1] = col_type(x1, y1, z1, w1);
            this->value[2] = col_type(x2, y2, z2, w2);
            this->value[3] = col_type(x3, y3, z3, w3);
        }
	
        T const *   data() const
        {
            return  &this->value[0][0];
        }
		
        template <typename U>
        tmat4x4<T> & operator/= (U const & s)
        {
            this->value[0] /= s;
            this->value[1] /= s;
            this->value[2] /= s;
            this->value[3] /= s;
            return *this;
        }
	
        tmat4x4<T>& rotate(T angle,tvec3<T> const & v )
        {
        	T a = (T)DEG2RAD(angle);
            T c = cos(a);
            T s = sin(a);

            tvec3<T> axis = normalize(v);

            tvec3<T> temp = (T(1) - c) * axis;

            tmat4x4<T> res;
            this->value[0][0]   =   c + temp[0] * axis[0];
            this->value[0][1]   =   0 + temp[0] * axis[1] + s * axis[2];
            this->value[0][2]   =   0 + temp[0] * axis[2] - s * axis[1];
            this->value[0][3]   =   0;

            this->value[1][0]   =   0 + temp[1] * axis[0] - s * axis[2];
            this->value[1][1]   =   c + temp[1] * axis[1];
            this->value[1][2]   =   0 + temp[1] * axis[2] + s * axis[0];
            this->value[1][3]   =   0;

            this->value[2][0]   =   0 + temp[2] * axis[0] + s * axis[1];
            this->value[2][1]   =   0 + temp[2] * axis[1] - s * axis[0];
            this->value[2][2]   =   c + temp[2] * axis[2];
            this->value[2][3]   =   0;

            this->value[3][0]   =   0;
            this->value[3][1]   =   0;
            this->value[3][2]   =   0;
            this->value[3][3]   =   1;
            return  *this;
        }

        tmat4x4<T> transpose( ) const 
        {
            return  tmat4x4<T>(
                                this->value[0][0], this->value[1][0], this->value[2][0], this->value[3][0],
                                this->value[0][1], this->value[1][1], this->value[2][1], this->value[3][1],
                                this->value[0][2], this->value[1][2], this->value[2][2], this->value[3][2],
                                this->value[0][3], this->value[1][3], this->value[2][3], this->value[3][3]
                                );
        }
    };
	
    template <typename T> 
    tvec3<T> operator * (tvec3<T> const& v, tmat4x4<T> const& mat)
    {
        return  tvec3<T>
                (
                v.x*mat[0][0] + v.y*mat[1][0] + v.z*mat[2][0] + 1*mat[3][0],
                v.x*mat[0][1] + v.y*mat[1][1] + v.z*mat[2][1] + 1*mat[3][1],
                v.x*mat[0][2] + v.y*mat[1][2] + v.z*mat[2][2] + 1*mat[3][2]
                );
    }
	
    template <typename T> 
    typename tmat4x4<T>::col_type operator* (tmat4x4<T> const & m, typename tmat4x4<T>::row_type const & v)
    {
        return typename tmat4x4<T>::col_type(
            m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z + m[3][0] * v.w,
            m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z + m[3][1] * v.w,
            m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z + m[3][2] * v.w,
            m[0][3] * v.x + m[1][3] * v.y + m[2][3] * v.z + m[3][3] * v.w);
    }
	
    template <typename T> 
    typename tmat4x4<T>::row_type operator* (typename tmat4x4<T>::col_type const & v, tmat4x4<T> const & m)
    {
        return typename tmat4x4<T>::row_type(
            m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w,
            m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w,
            m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w,
            m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w);
    }

	
    template <typename T> 
    tmat4x4<T> operator* (tmat4x4<T> const & m1, tmat4x4<T> const & m2)
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
	
	template <typename T>
	typename tvec3<T>::value_type length(tvec3<T> const & v)
	{
		typename tvec3<T>::value_type sqr = v.x * v.x + v.y * v.y + v.z * v.z;
		return sqrt(sqr);
	}
	
	template <typename T>
    typename tvec3<T>::value_type dot(tvec3<T> const & x, tvec3<T> const & y)
	{
		return x.x * y.x + x.y * y.y + x.z * y.z;
	}
	
	template <typename T>
    tvec3<T> cross(tvec3<T> const & x, tvec3<T> const & y)
	{
		return  tvec3<T>
                (
			    x.y * y.z - y.y * x.z,
			    x.z * y.x - y.z * x.x,
			    x.x * y.y - y.x * x.y
                );
	}
	
    template <typename T>
    T inversesqrt(T x)
    {
        return T(1) / sqrt(x);
    }	
	
	template <typename T>
	tvec3<T> normalize(tvec3<T> const & x)
	{
		typename tvec3<T>::value_type sqr = x.x * x.x + x.y * x.y + x.z * x.z;
		return x * inversesqrt(sqr);
	}
	
    template <typename valType> 
    tmat4x4<valType>  ortho
                        (
                        valType left, 
                        valType right, 
                        valType bottom, 
                        valType top, 
                        valType zNear, 
                        valType zFar
                        )
    {
        tmat4x4<valType> res(1);
        res[0][0]   =   valType(2) / (right - left);
        res[1][1]   =   valType(2) / (top - bottom);
        res[2][2]   =   - valType(2) / (zFar - zNear);
        res[3][0]   =   - (right + left) / (right - left);
        res[3][1]   =   - (top + bottom) / (top - bottom);
        res[3][2]   =   - (zFar + zNear) / (zFar - zNear);
        return res;
    }

    template <typename valType>
    void frustum(valType *matrix, valType left, valType right, valType bottom, valType top, valType znear, valType zfar)
    {
        valType temp, temp2, temp3, temp4;
        temp = valType(2.0) * znear;
        temp2 = right - left;
        temp3 = top - bottom;
        temp4 = zfar - znear;
        matrix[0] = temp / temp2;
        matrix[1] = valType(0.0);
        matrix[2] = valType(0.0);
        matrix[3] = valType(0.0);
        matrix[4] = valType(0.0);
        matrix[5] = temp / temp3;
        matrix[6] = valType(0.0);
        matrix[7] = valType(0.0);
        matrix[8] = (right + left) / temp2;
        matrix[9] = (top + bottom) / temp3;
        matrix[10] = (-zfar - znear) / temp4;
        matrix[11] = valType(-1.0);
        matrix[12] = valType(0.0);
        matrix[13] = valType(0.0);
        matrix[14] = (-temp * zfar) / temp4;
        matrix[15] = valType(0.0);
    }

    template <typename valType> 
    tmat4x4<valType> perspective(valType fovy, valType aspect, valType znear, valType zfar)
    {
        tmat4x4<valType> res(0);
        valType ymax, xmax;
        ymax = znear * (valType)tan((valType)(fovy * PI / 360.0));
        xmax = ymax * aspect;

        frustum<valType>((valType*)res.data(), -xmax, xmax, -ymax, ymax, znear, zfar);

        return  res;
    }

    template <typename T> 
    tmat4x4<T>    lookAt
                    (
                    tvec3<T> const & eye,
                    tvec3<T> const & center,
                    tvec3<T> const & up
                    )
    {
        tvec3<T> zAxis  =   normalize(center - eye);
        tvec3<T> yAxis  =   normalize(up);
        tvec3<T> xAxis  =   normalize(cross(zAxis, yAxis));
        yAxis = normalize(cross(xAxis, zAxis));

        tmat4x4<T>    res(1);
        res[0][0]   =   xAxis.x;
        res[1][0]   =   xAxis.y;
        res[2][0]   =   xAxis.z;
        res[0][1]   =   yAxis.x;
        res[1][1]   =   yAxis.y;
        res[2][1]   =   yAxis.z;
        res[0][2]   =   -zAxis.x;
        res[1][2]   =   -zAxis.y;
        res[2][2]   =   -zAxis.z;
        res[3][0]   =   -dot(xAxis, eye);
        res[3][1]   =   -dot(yAxis, eye);
        res[3][2]   =   dot(zAxis, eye);
        return res;
    }


    template <typename T> 
    tmat4x4<T>    lookAtL
        (
        tvec3<T> const & eye,
        tvec3<T> const & center,
        tvec3<T> const & up
        )
    {
        tvec3<T> zAxis  =   normalize(center - eye);
        tvec3<T> yAxis  =   normalize(up);
        tvec3<T> xAxis  =   normalize(cross(yAxis,zAxis));
        yAxis = normalize(cross(zAxis,xAxis));

        tmat4x4<T>    res(1);
        res[0][0]   =   xAxis.x;
        res[1][0]   =   xAxis.y;
        res[2][0]   =   xAxis.z;
        res[0][1]   =   yAxis.x;
        res[1][1]   =   yAxis.y;
        res[2][1]   =   yAxis.z;
        res[0][2]   =   -zAxis.x;
        res[1][2]   =   -zAxis.y;
        res[2][2]   =   -zAxis.z;
        res[3][0]   =   -dot(xAxis, eye);
        res[3][1]   =   -dot(yAxis, eye);
        res[3][2]   =   dot(zAxis, eye);
        return res;
    }

    template<typename T>
    class   AxisAlignedBox
    {
    public:
        enum Extent
        {
            EXTENT_NULL,
            EXTENT_FINITE,
            EXTENT_INFINITE
        };
    public:
	    tvec3<T>    _minimum;
	    tvec3<T>    _maximum;
        Extent      _extent;
    public:
	    AxisAlignedBox()
	    {
		    _minimum    =   tvec3<T>( T(-0.5), T(-0.5), T(-0.5) );
		    _maximum    =   tvec3<T>( T(0.5), T(0.5), T(0.5) );
            _extent     =   EXTENT_NULL;
	    }

	    ~AxisAlignedBox()
	    {
	    }
	    void setExtents(
		    T mx, T my, T mz,
		    T Mx, T My, T Mz )
	    {
		    _minimum.x  =   mx;
		    _minimum.y  =   my;
		    _minimum.z  =   mz;

		    _maximum.x  =   Mx;
		    _maximum.y  =   My;
		    _maximum.z  =   Mz;
            _extent     =   EXTENT_FINITE;

	    }
	
	    void merge( const AxisAlignedBox<T>& right )
	    {

            if ((right._extent == EXTENT_NULL) || (_extent == EXTENT_INFINITE))
            {
                return;
            }
            else if (right._extent == EXTENT_INFINITE)
            {
                _extent =   EXTENT_INFINITE;
            }
            else if (_extent == EXTENT_NULL)
            {
                setExtents(right._minimum, right._maximum);
            }
            else
            {
                //! merge
                tvec3<T> min =   _minimum;
                tvec3<T> max =   _maximum;
                max.makeCeil(right._maximum);
                min.makeFloor(right._minimum);
                setExtents(min, max);
            }
	    }

	    tvec3<T>    getCenter(void) const
	    {
		    return tvec3<T>(
			                (_maximum.x + _minimum.x) * T(0.5f),
			                (_maximum.y + _minimum.y) * T(0.5f),
			                (_maximum.z + _minimum.z) * T(0.5f)
                            );
	    }
	    /**
	    *   Gets the size of the box
	    */ 
	    tvec3<T> getSize(void) const
	    {
		    return _maximum - _minimum;
	    }
        
	    tvec3<T> getHalfSize(void) const
	    {
		    return (_maximum - _minimum) * T(0.5);
	    }	
	   
};
    
    template<typename T>
    class  tray
    {
        typedef T           value_type;
        typedef tray<T>     type;
    protected:
        tvec3<T>    _origin;
        tvec3<T>    _direction;
    public:
        tray():
            _origin(value_type(0),value_type(0),value_type(0)),
            _direction(value_type(0),value_type(0),value_type(1))
        {}
				

        /**
        *   设置射线的起点
        */
        void            setOrigin(const tvec3<T>& origin)   
        {   
            _origin = origin;   
        } 
        /**
        *   返回射线的起点
        */
        const tvec3<T>&  getOrigin(void) const               
        {   
            return _origin;     
        } 

        /**
        *   设置射线的方向
        */
        void            setDirection(const tvec3<T>& dir)    
        {   
            _direction = dir;   
        } 
        
        /**
        *   返回射线的方向
        */
        const tvec3<T>&  getDirection(void) const
        {   
            return _direction;  
        } 

	    /** 
        *   Gets the position of a point t units along the ray. 
        */
	    tvec3<T>        getPoint(T time) const 
        {   
            return tvec3<T>(_origin + (_direction * time));
        }

    };

    template<class T>
    class  Plane
    {
    public:
        tvec3<T>    _normal;
        T           _distance;
    public:
		
        Plane ()
        {
            _normal     =   tvec3<T>(0,0,0);
            _distance   =   0.0f;
        }
	
	    /** Construct a plane using the 4 constants directly **/
		
        Plane (T x, T y, T z, T o)
        {
            _normal     =   tvec3<T>(x, y, z);
            T invLen    = 1.0f / (_normal).length();
            _normal     *=  invLen;
            _distance   =   o * invLen;
        }
		
			
        /**
        *   到点的距离
        */
        T   distance(const tvec3<T> &pos) const
        {
            return  dot(_normal,pos) + _distance;
        }
 
    };
 
    typedef char                    PATH[256];
    typedef double                  real;
    typedef tvec2<short>            short2;
    typedef tvec2<unsigned short>   ushort2;
    typedef tvec2<unsigned int>     uint2;
    typedef tvec2<int>              int2;
    typedef tvec2<float>            float2;
    typedef tvec2<double>           double2;

    typedef tvec2<real>             real2;

    typedef tvec3<unsigned char>    uchar3;
    typedef tvec3<byte>             byte3;
    typedef tvec3<unsigned short>   ushort3;
    
    typedef tvec3<unsigned int>     uint3;
    typedef tvec3<int>              int3;
    typedef tvec3<int>              int3;
    typedef tvec3<unsigned>         uint3;
    typedef tvec3<float>            float3;
    typedef tvec3<double>           double3;

    typedef tvec3<real>             real3;

    typedef tvec4<unsigned short>   ushort4;

    typedef tvec2<unsigned short>   half2;
    typedef tvec3<unsigned short>   half3;
    typedef tvec4<unsigned short>   half4;

    typedef tvec4<int>              int4;
    typedef tvec4<float>            float4;
    typedef tvec4<double>           double4;
    typedef tvec4<real>             real4;

    typedef AxisAlignedBox<float>   aabb3df;
    typedef AxisAlignedBox<real>    aabb3dr;

    typedef tmat3x3<float>      matrix3;
    typedef tmat4x4<float>      matrix4;

    typedef tmat3x3<double>     matrix3d;
    typedef tmat4x4<double>     matrix4d;

    typedef tmat3x3<real>       matrix3r;
    typedef tmat4x4<real>       matrix4r;
    
    typedef tray<real>          Ray;
    typedef tray<float>         RayF;  

}
