#pragma once
#include "lifeiMathUtil.h"

namespace CELL
{
   template<class T>   inline T    tmin(T a,T b)
    {
        return  a < b ? a:b;
    }

    template<class T>   inline  T    tmax(T a,T b)
    {
        return  a > b ? a:b;
    }

    union   TileId
    {
        struct
        {
            int64  _row : 28;
            int64  _col : 28;
            int64  _lev : 8;
        };
        int64  _index;
    };

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
        tvec2(tvec2<T> const & v) :
            x(v.x),
            y(v.y)
        {}
        tvec2(value_type const & s) :
            x(s),
            y(s)
        {}

        tvec2(value_type const & s1, value_type const & s2) :
            x(s1),
            y(s2)
        {}

        template <typename U> 
        tvec2(U const & x) :
            x(value_type(x)),
            y(value_type(x))
        {}

        template <typename U, typename V> 
        tvec2(U const & a, V b) :
            x(value_type(a)),
            y(value_type(b))
        {}


        template <typename U> 
        tvec2(tvec2<U> const & v) :
            x(value_type(v.x)),
            y(value_type(v.y))
        {}

        tvec2<T> & operator= (tvec2<T> const & v)
        {
            this->x = v.x;
            this->y = v.y;
            return *this;
        }

        template <typename U> 
        tvec2<T> & operator= (tvec2<U> const & v)
        {
            this->x = T(v.x);
            this->y = T(v.y);
            return *this;
        }

        template <typename U> 
        tvec2<T> & operator+=(U const & s)
        {
            this->x += T(s);
            this->y += T(s);
            return *this;
        }

        template <typename U> 
        tvec2<T> & operator+=(tvec2<U> const & v)
        {
            this->x += T(v.x);
            this->y += T(v.y);
            return *this;
        }


        template <typename U> 
        tvec2<T> & operator-=(U const & s)
        {
            this->x -= T(s);
            this->y -= T(s);
            return *this;
        }

        template <typename U> 
        tvec2<T> & operator-=(tvec2<U> const & v)
        {
            this->x -= T(v.x);
            this->y -= T(v.y);
            return *this;
        }

        template <typename U> 
        tvec2<T> & operator*=(U s)
        {
            this->x *= T(s);
            this->y *= T(s);
            return *this;
        }

        template <typename U> 
        tvec2<T> & operator*=(tvec2<U> const & v)
        {
            this->x *= T(v.x);
            this->y *= T(v.y);
            return *this;
        }

        template <typename U> 
        tvec2<T> & operator/=(U s)
        {
            this->x /= T(s);
            this->y /= T(s);
            return *this;
        }

        template <typename U> 
        tvec2<T> & operator/=(tvec2<U> const & v)
        {
            this->x /= T(v.x);
            this->y /= T(v.y);
            return *this;
        }

        tvec2<T> & operator++()
        {
            ++  this->x;
            ++  this->y;
            return *this;
        }
        tvec2<T> & operator--()
        {
            --this->x;
            --this->y;
            return *this;
        }
        void makeCeil( tvec2<T> cmp )
        {
            if( cmp.x > x ) x = cmp.x;
            if( cmp.y > y ) y = cmp.y;
        }
        void makeFloor( tvec2<T> cmp )
        {
            if( cmp.x < x ) x = cmp.x;
            if( cmp.y < y ) y = cmp.y;
        }
    };

	
    template <typename T> 
    tvec2<T> operator+ (tvec2<T> const & v, T const & s)
    {
        return tvec2<T>(
            v.x + T(s),
            v.y + T(s));
    }

    template <typename T> 
    tvec2<T> operator+ (T const & s, tvec2<T> const & v)
    {
        return tvec2<T>(
            T(s) + v.x,
            T(s) + v.y);
    }

    template <typename T> 
    tvec2<T> operator+ (tvec2<T> const & v1, tvec2<T> const & v2)
    {
        return tvec2<T>(
            v1.x + T(v2.x),
            v1.y + T(v2.y));
    }

    template <typename T> 
    tvec2<T> operator-(tvec2<T> const & v, T const & s)
    {
        return tvec2<T>(
            v.x - T(s),
            v.y - T(s));
    }

    template <typename T> 
    tvec2<T> operator- (T const & s, tvec2<T> const & v)
    {
        return tvec2<T>(
            T(s) - v.x,
            T(s) - v.y);
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
    tvec2<T> operator* (T const & s, tvec2<T> const & v)
    {
        return tvec2<T>(
            T(s) * v.x,
            T(s) * v.y);
    }

    template <typename T> 
    tvec2<T> operator*(tvec2<T> const & v1, tvec2<T> const & v2)
    {
        return tvec2<T>(
            v1.x * T(v2.x),
            v1.y * T(v2.y));
    }
	
    template <typename T> 
    tvec2<T> operator- (tvec2<T> const & v)
    {
        return  tvec2<T>  (
                            -v.x, 
                            -v.y
                            );
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

        inline tvec3(tvec3<T> const & v) :
            x(v.x),
            y(v.y),
            z(v.z)
        {}

        inline tvec3(value_type s) :
            x(s),
            y(s),
            z(s)
        {}

        inline tvec3(value_type s0, value_type s1, value_type s2) :
            x(s0),
            y(s1),
            z(s2)
        {}


        template <typename U> 
        tvec3(U s) :
            x(value_type(s)),
            y(value_type(s)),
            z(value_type(s))
        {}

        template <typename A, typename B, typename C> 
        tvec3(A x, B y, C z) :
            x(value_type(x)),
            y(value_type(y)),
            z(value_type(z))
        {}

        template <typename A, typename B> 
        tvec3(tvec2<A> const& v, B s) :
            x(value_type(v.x)),
            y(value_type(v.y)),
            z(value_type(s))
        {}
        template <typename A, typename B> 
        tvec3(A s,tvec2<B> const& v) :
            x(value_type(s)),
            y(value_type(v.x)),
            z(value_type(v.y))
        {}

        template <typename U> 
        tvec3(tvec3<U> const & v) :
            x(value_type(v.x)),
            y(value_type(v.y)),
            z(value_type(v.z))
        {}


        tvec3<T>& operator= (tvec3<T> const & v)
        {
            this->x = v.x;
            this->y = v.y;
            this->z = v.z;
            return *this;
        }

        template <typename U> 
        tvec3<T>& operator= (tvec3<U> const & v)
        {
            this->x = T(v.x);
            this->y = T(v.y);
            this->z = T(v.z);
            return *this;
        }

        template <typename U> 
        tvec3<T> & operator+=(U const & s)
        {
            this->x += T(s);
            this->y += T(s);
            this->z += T(s);
            return *this;
        }

        template <typename U> 
        tvec3<T> & operator+=(tvec3<U> const & v)
        {
            this->x += T(v.x);
            this->y += T(v.y);
            this->z += T(v.z);
            return *this;
        }

        template <typename U> 
        tvec3<T> & operator-=(U const & s)
        {
            this->x -= T(s);
            this->y -= T(s);
            this->z -= T(s);
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

        template <typename U> 
        tvec3<T> & operator*=(tvec3<U> const & v)
        {
            this->x *= T(v.x);
            this->y *= T(v.y);
            this->z *= T(v.z);
            return *this;
        }

        template <typename U> 
        tvec3<T> & operator/=(U const & s)
        {
            this->x /= T(s);
            this->y /= T(s);
            this->z /= T(s);
            return *this;
        }

        template <typename U> 
        tvec3<T> & operator/=(tvec3<U> const & v)
        {
            this->x /= T(v.x);
            this->y /= T(v.y);
            this->z /= T(v.z);
            return *this;
        }

        tvec3<T> & operator++()
        {
            ++this->x;
            ++this->y;
            ++this->z;
            return *this;
        }
        tvec3<T> & operator--()
        {
            --this->x;
            --this->y;
            --this->z;
            return *this;
        }

        void    makeFloor( const tvec3<T>& cmp )
        {
            if( cmp.x < x ) x = cmp.x;
            if( cmp.y < y ) y = cmp.y;
            if( cmp.z < z ) z = cmp.z;
        }
        void    makeCeil( const tvec3<T>& cmp )
        {
            if( cmp.x > x ) x = cmp.x;
            if( cmp.y > y ) y = cmp.y;
            if( cmp.z > z ) z = cmp.z;
        }
        T       lengthf() const
        {
            return (T)sqrtf( x * x + y * y + z * z );
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
    tvec3<T> operator+(tvec3<T> const & v, T const & s)
    {
        return tvec3<T>(
            v.x + T(s),
            v.y + T(s),
            v.z + T(s));
    }

    template <typename T> 
    tvec3<T> operator+ ( T const & s, tvec3<T> const & v)
    {
        return tvec3<T>(
            T(s) + v.x,
            T(s) + v.y,
            T(s) + v.z);
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
    tvec3<T> operator- (tvec3<T> const & v, T const & s)
    {
        return tvec3<T>(
            v.x - T(s),
            v.y - T(s),
            v.z - T(s));
    }

    template <typename T> 
    tvec3<T> operator- (T const & s, tvec3<T> const & v)
    {
        return tvec3<T>(
            T(s) - v.x,
            T(s) - v.y,
            T(s) - v.z);
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
    tvec3<T> operator* (tvec3<T> const & v1, tvec3<T> const & v2)
    {
        return tvec3<T>(
            v1.x * T(v2.x),
            v1.y * T(v2.y),
            v1.z * T(v2.z));
    }

    template <typename T> 
    tvec3<T> operator/ (tvec3<T> const & v, T const & s)
    {
        return tvec3<T>(
            v.x / T(s),
            v.y / T(s),
            v.z / T(s));
    }

    template <typename T> 
    tvec3<T> operator/ (T const & s, tvec3<T> const & v)
    {
        return tvec3<T>(
            T(s) / v.x,
            T(s) / v.y,
            T(s) / v.z);
    }

    template <typename T> 
    tvec3<T> operator/ (tvec3<T> const & v1, tvec3<T> const & v2)
    {
        return tvec3<T>(
            v1.x / T(v2.x),
            v1.y / T(v2.y),
            v1.z / T(v2.z));
    }

    template <typename T> 
    tvec3<T> operator- (tvec3<T> const & v)
    {
        return tvec3<T>(
            -v.x, 
            -v.y, 
            -v.z);
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
        tvec4(T s) :
            x(s),
            y(s),
            z(s),
            w(s)
        {}
        tvec4(tvec4<T> const & v) :
            x(v.x),
            y(v.y),
            z(v.z),
            w(v.w)
        {}

        template <typename A, typename B> 
        tvec4(tvec3<A> const & v, B s):
            x(value_type(v.x)),
            y(value_type(v.y)),
            z(value_type(v.z)),
            w(value_type(s))
        {}

        template <typename A, typename B> 
        tvec4(A s,tvec3<B> const & v):
            x(value_type(s)),
            y(value_type(v.x)),
            z(value_type(v.y)),
            w(value_type(v.z))
        {}

        template<typename U>
        tvec4(tvec4<U> const & v) :
            x(value_type(v.x)),
            y(value_type(v.y)),
            z(value_type(v.z)),
            w(value_type(v.w))
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

        tvec4<T> & operator=(tvec4<T> const & v)
        {
            this->x = v.x;
            this->y = v.y;
            this->z = v.z;
            this->w = v.w;
            return *this;
        }

        template <typename U> 
        tvec4<T> & operator= (tvec4<U> const & v)
        {
            this->x = T(v.x);
            this->y = T(v.y);
            this->z = T(v.z);
            this->w = T(v.w);
            return *this;
        }

        template <typename U> 
        tvec4<T> & operator+=(U const & s)
        {
            this->x += T(s);
            this->y += T(s);
            this->z += T(s);
            this->w += T(s);
            return *this;
        }
        template <typename U> 
        tvec4<T> & operator+=(tvec4<U> const & v)
        {
            this->x += T(v.x);
            this->y += T(v.y);
            this->z += T(v.z);
            this->w += T(v.w);
            return *this;
        }

        template <typename U> 
        tvec4<T> & operator-=(U const & s)
        {
            this->x -= T(s);
            this->y -= T(s);
            this->z -= T(s);
            this->w -= T(s);
            return *this;
        }

        template <typename U> 
        tvec4<T> & operator-=(tvec4<U> const & v)
        {
            this->x -= T(v.x);
            this->y -= T(v.y);
            this->z -= T(v.z);
            this->w -= T(v.w);
            return *this;
        }
        template <typename U> 
        tvec4<T> & operator*= (U const & s)
        {
            this->x *= T(s);
            this->y *= T(s);
            this->z *= T(s);
            this->w *= T(s);
            return *this;
        }

        template <typename U> 
        tvec4<T> & operator*=( tvec4<U> const & v)
        {
            this->x *= T(v.x);
            this->y *= T(v.y);
            this->z *= T(v.z);
            this->w *= T(v.w);
            return *this;
        }
        template <typename U> 
        tvec4<T> & operator/=(U const & s)
        {
            this->x /= T(s);
            this->y /= T(s);
            this->z /= T(s);
            this->w /= T(s);
            return *this;
        }

        template <typename U> 
        tvec4<T> & operator/=(tvec4<U> const & v)
        {
            this->x /= T(v.x);
            this->y /= T(v.y);
            this->z /= T(v.z);
            this->w /= T(v.w);
            return *this;
        }

        tvec4<T> & operator++()
        {
            ++this->x;
            ++this->y;
            ++this->z;
            ++this->w;
            return *this;
        }

        tvec4<T> & operator--()
        {
            --this->x;
            --this->y;
            --this->z;
            --this->w;
            return *this;
        }
    };
	
    template <typename T> 
    tvec4<T> operator+ (tvec4<T> const & v, T const & s)
    {
        return tvec4<T>(
            v.x + s,
            v.y + s,
            v.z + s,
            v.w + s);
    }

    template <typename T> 
    tvec4<T> operator+ (T const & s, tvec4<T> const & v)
    {
        return tvec4<T>(
            s + v.x,
            s + v.y,
            s + v.z,
            s + v.w);
    }

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
    tvec4<T> operator* (T const & s, tvec4<T> const & v)
    {
        return tvec4<T>(
            s * v.x,
            s * v.y,
            s * v.z,
            s * v.w);
    }

    template <typename T> 
    tvec4<T> operator*(tvec4<T> const & v1, tvec4<T> const & v2)
    {
        return tvec4<T>(
            v1.x * v2.x,
            v1.y * v2.y,
            v1.z * v2.z,
            v1.w * v2.w);
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
    tvec4<T> operator/ (T const & s, tvec4<T> const & v)
    {
        return tvec4<T>(
            s / v.x,
            s / v.y,
            s / v.z,
            s / v.w);
    }

    template <typename T> 
    tvec4<T> operator/ ( tvec4<T> const & v1, tvec4<T> const & v2)
    {
        return tvec4<T>(
            v1.x / v2.x,
            v1.y / v2.y,
            v1.z / v2.z,
            v1.w / v2.w);
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
        size_type col_size()
        {
            return 3;
        }

        size_type row_size()
        {
            return 3;
        }
        T*      dataPtr()
        {
            return  (T*)value;
        }
        tmat3x3()
        {
            value_type const Zero(0);
            value_type const One(1);
            this->value[0] = col_type(One, Zero, Zero);
            this->value[1] = col_type(Zero, One, Zero);
            this->value[2] = col_type(Zero, Zero, One);
        }

        tmat3x3
            (
            tmat3x3<T> const & m
            )
        {
            this->value[0] = m.value[0];
            this->value[1] = m.value[1];
            this->value[2] = m.value[2];
        }


        tmat3x3(value_type const & s)
        {
            value_type const Zero(0);
            this->value[0] = col_type(s, Zero, Zero);
            this->value[1] = col_type(Zero, s, Zero);
            this->value[2] = col_type(Zero, Zero, s);
        }


        tmat3x3
            (
            value_type const & x0, value_type const & y0, value_type const & z0, 
            value_type const & x1, value_type const & y1, value_type const & z1,
            value_type const & x2, value_type const & y2, value_type const & z2
            )
        {
            this->value[0] = col_type(x0, y0, z0);
            this->value[1] = col_type(x1, y1, z1);
            this->value[2] = col_type(x2, y2, z2);
        }

        tmat3x3
            (
            col_type const & v0, 
            col_type const & v1, 
            col_type const & v2
            )
        {
            this->value[0] = v0;
            this->value[1] = v1;
            this->value[2] = v2;
        }

        template <typename U> 
        tmat3x3(U const & s)
        {
            value_type const Zero(0);
            this->value[0] = tvec3<T>(value_type(s), Zero, Zero);
            this->value[1] = tvec3<T>(Zero, value_type(s), Zero);
            this->value[2] = tvec3<T>(Zero, Zero, value_type(s));
        }

        template <
            typename X1, typename Y1, typename Z1, 
            typename X2, typename Y2, typename Z2, 
            typename X3, typename Y3, typename Z3>  
            tmat3x3
            (
            X1 const & x1, Y1 const & y1, Z1 const & z1, 
            X2 const & x2, Y2 const & y2, Z2 const & z2, 
            X3 const & x3, Y3 const & y3, Z3 const & z3 
            )
        {
            this->value[0] = col_type(value_type(x1), value_type(y1), value_type(z1));
            this->value[1] = col_type(value_type(x2), value_type(y2), value_type(z2));
            this->value[2] = col_type(value_type(x3), value_type(y3), value_type(z3));
        }

        template <typename V1, typename V2, typename V3> 
        tmat3x3
            (
            tvec3<V1> const & v1, 
            tvec3<V2> const & v2, 
            tvec3<V3> const & v3
            )
        {
            this->value[0] = col_type(v1);
            this->value[1] = col_type(v2);
            this->value[2] = col_type(v3);
        }

        template <typename U> 
        tmat3x3(tmat3x3<U> const & m)
        {
            this->value[0] = col_type(m[0]);
            this->value[1] = col_type(m[1]);
            this->value[2] = col_type(m[2]);
        }

        T const *   data() const
        {
            return  &this->value[0][0];
        }

        tmat3x3<T> _inverse() const
        {
            T S00 = value[0][0];
            T S01 = value[0][1];
            T S02 = value[0][2];

            T S10 = value[1][0];
            T S11 = value[1][1];
            T S12 = value[1][2];

            T S20 = value[2][0];
            T S21 = value[2][1];
            T S22 = value[2][2];

            tmat3x3<T> Inverse(
                S11 * S22 - S21 * S12,
                S12 * S20 - S22 * S10,
                S10 * S21 - S20 * S11,
                S02 * S21 - S01 * S22,
                S00 * S22 - S02 * S20,
                S01 * S20 - S00 * S21,
                S12 * S01 - S11 * S02,
                S10 * S02 - S12 * S00,
                S11 * S00 - S10 * S01);

            T Determinant = S00 * (S11 * S22 - S21 * S12)
                - S10 * (S01 * S22 - S21 * S02)
                + S20 * (S01 * S12 - S11 * S02);

            Inverse /= Determinant;
            return Inverse;
        }

        col_type &  operator[](size_type i)
        {
            assert(i < this->length());
            return this->value[i];
        }

        col_type const & operator[](size_type i) const
        {
            assert(i < this->length());
            return this->value[i];
        }

        tmat3x3<T> & operator=(tmat3x3<T> const & m)
        {
            this->value[0] = m[0];
            this->value[1] = m[1];
            this->value[2] = m[2];
            return *this;
        }
        template <typename U> 
        tmat3x3<T> & operator=(tmat3x3<U> const & m)
        {
            this->value[0] = m[0];
            this->value[1] = m[1];
            this->value[2] = m[2];
            return *this;
        }

        template <typename U> 
        tmat3x3<T> & operator+= (U const & s)
        {
            this->value[0] += s;
            this->value[1] += s;
            this->value[2] += s;
            return *this;
        }

        template <typename U> 
        tmat3x3<T> & operator+=(tmat3x3<U> const & m)
        {
            this->value[0] += m[0];
            this->value[1] += m[1];
            this->value[2] += m[2];
            return *this;
        }

        template <typename U> 
        tmat3x3<T> & operator-= (U const & s)
        {
            this->value[0] -= s;
            this->value[1] -= s;
            this->value[2] -= s;
            return *this;
        }

        template <typename U> 
        tmat3x3<T> & operator-= (tmat3x3<U> const & m)
        {
            this->value[0] -= m[0];
            this->value[1] -= m[1];
            this->value[2] -= m[2];
            return *this;
        }

        template <typename U> 
        tmat3x3<T> & operator*= (U const & s)
        {
            this->value[0] *= s;
            this->value[1] *= s;
            this->value[2] *= s;
            return *this;
        }
        template <typename U> 
        tmat3x3<T> & operator*= (tmat3x3<U> const & m)
        {
            return (*this = *this * m);
        }

        template <typename U> 
        tmat3x3<T> & operator/= (U const & s)
        {
            this->value[0] /= s;
            this->value[1] /= s;
            this->value[2] /= s;
            return *this;
        }

        template <typename U> 
        tmat3x3<T> & operator/= (tmat3x3<U> const & m)
        {
            return (*this = *this / m);
        }

        tmat3x3<T> & operator++ ()
        {
            ++this->value[0];
            ++this->value[1];
            ++this->value[2];
            return *this;
        }
        tmat3x3<T> & operator-- ()
        {
            --this->value[0];
            --this->value[1];
            --this->value[2];
            return *this;
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
        void identify()
        {
            this->value[0] = col_type(1, 0, 0, 0);
            this->value[1] = col_type(0, 1, 0, 0);
            this->value[2] = col_type(0, 0, 1, 0);
            this->value[3] = col_type(0, 0, 0, 1);
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

        tmat4x4(tmat4x4<T> const & m)
        {
            this->value[0] = m.value[0];
            this->value[1] = m.value[1];
            this->value[2] = m.value[2];
            this->value[3] = m.value[3];
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

        tmat4x4(value_type s)
        {
            value_type const Zero(0);
            this->value[0] = col_type(s, Zero, Zero, Zero);
            this->value[1] = col_type(Zero, s, Zero, Zero);
            this->value[2] = col_type(Zero, Zero, s, Zero);
            this->value[3] = col_type(Zero, Zero, Zero, s);
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

        tmat4x4
            (
            col_type const & v0, 
            col_type const & v1, 
            col_type const & v2,
            col_type const & v3
            )
        {
            this->value[0] = v0;
            this->value[1] = v1;
            this->value[2] = v2;
            this->value[3] = v3;
        }

        template <typename U> 
        tmat4x4(tmat4x4<U> const & m)
        {
            this->value[0] = col_type(m[0]);
            this->value[1] = col_type(m[1]);
            this->value[2] = col_type(m[2]);
            this->value[3] = col_type(m[3]);
        }

        template <typename U> 
        tmat4x4(U const & s)
        {
            value_type const Zero(0);
            this->value[0] = tvec4<T>(value_type(s), Zero, Zero, Zero);
            this->value[1] = tvec4<T>(Zero, value_type(s), Zero, Zero);
            this->value[2] = tvec4<T>(Zero, Zero, value_type(s), Zero);
            this->value[3] = tvec4<T>(Zero, Zero, Zero, value_type(s));
        }
        template <
            typename X1, typename Y1, typename Z1, typename W1, 
            typename X2, typename Y2, typename Z2, typename W2, 
            typename X3, typename Y3, typename Z3, typename W3, 
            typename X4, typename Y4, typename Z4, typename W4>  
            tmat4x4
            (
            X1 const & x1, Y1 const & y1, Z1 const & z1, W1 const & w1, 
            X2 const & x2, Y2 const & y2, Z2 const & z2, W2 const & w2, 
            X3 const & x3, Y3 const & y3, Z3 const & z3, W3 const & w3, 
            X4 const & x4, Y4 const & y4, Z4 const & z4, W4 const & w4
            )
        {
            this->value[0] = col_type(value_type(x1), value_type(y1), value_type(z1), value_type(w1));
            this->value[1] = col_type(value_type(x2), value_type(y2), value_type(z2), value_type(w2));
            this->value[2] = col_type(value_type(x3), value_type(y3), value_type(z3), value_type(w3));
            this->value[3] = col_type(value_type(x4), value_type(y4), value_type(z4), value_type(w4));
        }
        template <typename V1, typename V2, typename V3, typename V4> 
        tmat4x4
            (
            tvec4<V1> const & v1, 
            tvec4<V2> const & v2, 
            tvec4<V3> const & v3,
            tvec4<V4> const & v4
            )		
        {
            this->value[0] = col_type(v1);
            this->value[1] = col_type(v2);
            this->value[2] = col_type(v3);
            this->value[3] = col_type(v4);
        }

        tmat4x4<T>  _inverse() const
        {
#define VERTTYPEMUL(a,b)			( (T)((a)*(b)) )
#define VERTTYPEDIV(a,b)			( (T)((a)/(b)) )
#define VERTTYPEABS(a)				( (T)(fabs(a)) )

#define f2vt(x)						(x)
#define vt2f(x)						(x)

            tmat4x4<T>  res;
            T   outf[16]  =   {0};
            T	det_1;
            T	pos, neg, temp;
            T*  f   =   (T*)data();

            pos = neg = f2vt(0.0);
            temp =  VERTTYPEMUL(VERTTYPEMUL(f[ 0], f[ 5]), f[10]);
            if (temp >= 0) pos += temp; else neg += temp;
            temp =  VERTTYPEMUL(VERTTYPEMUL(f[ 4], f[ 9]), f[ 2]);
            if (temp >= 0) pos += temp; else neg += temp;
            temp =  VERTTYPEMUL(VERTTYPEMUL(f[ 8], f[ 1]), f[ 6]);
            if (temp >= 0) pos += temp; else neg += temp;
            temp =  VERTTYPEMUL(VERTTYPEMUL(-f[ 8], f[ 5]), f[ 2]);
            if (temp >= 0) pos += temp; else neg += temp;
            temp =  VERTTYPEMUL(VERTTYPEMUL(-f[ 4], f[ 1]), f[10]);
            if (temp >= 0) pos += temp; else neg += temp;
            temp =  VERTTYPEMUL(VERTTYPEMUL(-f[ 0], f[ 9]), f[ 6]);
            if (temp >= 0) pos += temp; else neg += temp;
            det_1 = pos + neg;

            /* Is the submatrix A singular? */
            if (det_1 == f2vt(0.0)) //|| (VERTTYPEABS(det_1 / (pos - neg)) < 1.0e-15)
            {
                /* Matrix M has no inverse */
                _RPT0(_CRT_WARN, "Matrix has no inverse : singular matrix\n");
            }
            else
            {
                /* Calculate inverse(A) = adj(A) / det(A) */
                //det_1 = 1.0 / det_1;
                det_1 = VERTTYPEDIV(f2vt(1.0f), det_1);
                outf[ 0] =   VERTTYPEMUL(( VERTTYPEMUL(f[ 5], f[10]) - VERTTYPEMUL(f[ 9], f[ 6]) ), det_1);
                outf[ 1] = - VERTTYPEMUL(( VERTTYPEMUL(f[ 1], f[10]) - VERTTYPEMUL(f[ 9], f[ 2]) ), det_1);
                outf[ 2] =   VERTTYPEMUL(( VERTTYPEMUL(f[ 1], f[ 6]) - VERTTYPEMUL(f[ 5], f[ 2]) ), det_1);
                outf[ 4] = - VERTTYPEMUL(( VERTTYPEMUL(f[ 4], f[10]) - VERTTYPEMUL(f[ 8], f[ 6]) ), det_1);
                outf[ 5] =   VERTTYPEMUL(( VERTTYPEMUL(f[ 0], f[10]) - VERTTYPEMUL(f[ 8], f[ 2]) ), det_1);
                outf[ 6] = - VERTTYPEMUL(( VERTTYPEMUL(f[ 0], f[ 6]) - VERTTYPEMUL(f[ 4], f[ 2]) ), det_1);
                outf[ 8] =   VERTTYPEMUL(( VERTTYPEMUL(f[ 4], f[ 9]) - VERTTYPEMUL(f[ 8], f[ 5]) ), det_1);
                outf[ 9] = - VERTTYPEMUL(( VERTTYPEMUL(f[ 0], f[ 9]) - VERTTYPEMUL(f[ 8], f[ 1]) ), det_1);
                outf[10] =   VERTTYPEMUL(( VERTTYPEMUL(f[ 0], f[ 5]) - VERTTYPEMUL(f[ 4], f[ 1]) ), det_1);

                /* Calculate -C * inverse(A) */
                outf[12] = - ( VERTTYPEMUL(f[12], outf[ 0]) + VERTTYPEMUL(f[13], outf[ 4]) + VERTTYPEMUL(f[14], outf[ 8]) );
                outf[13] = - ( VERTTYPEMUL(f[12], outf[ 1]) + VERTTYPEMUL(f[13], outf[ 5]) + VERTTYPEMUL(f[14], outf[ 9]) );
                outf[14] = - ( VERTTYPEMUL(f[12], outf[ 2]) + VERTTYPEMUL(f[13], outf[ 6]) + VERTTYPEMUL(f[14], outf[10]) );

                /* Fill in last row */
                outf[ 3] = f2vt(0.0f);
                outf[ 7] = f2vt(0.0f);
                outf[11] = f2vt(0.0f);
                outf[15] = f2vt(1.0f);
            }
            memcpy((void*)res.data(),outf,sizeof(outf));

            return res;
        }

        T const *   data() const
        {
            return  &this->value[0][0];
        }

        tmat4x4<T>& operator= (tmat4x4<T> const & m)
        {
            this->value[0] = m[0];
            this->value[1] = m[1];
            this->value[2] = m[2];
            this->value[3] = m[3];
            return *this;
        }

        template <typename U> 
        tmat4x4<T>& operator= (tmat4x4<U> const & m)
        {
            this->value[0] = m[0];
            this->value[1] = m[1];
            this->value[2] = m[2];
            this->value[3] = m[3];
            return *this;
        }

        template <typename U> 
        tmat4x4<T>& operator+= (U const & s)
        {
            this->value[0] += s;
            this->value[1] += s;
            this->value[2] += s;
            this->value[3] += s;
            return *this;
        }

        template <typename U> 
        tmat4x4<T>& operator+= (tmat4x4<U> const & m)
        {
            this->value[0] += m[0];
            this->value[1] += m[1];
            this->value[2] += m[2];
            this->value[3] += m[3];
            return *this;
        }

        template <typename U> 
        tmat4x4<T> & operator-= (U const & s)
        {
            this->value[0] -= s;
            this->value[1] -= s;
            this->value[2] -= s;
            this->value[3] -= s;
            return *this;
        }

        template <typename U>
        tmat4x4<T> & operator-= (tmat4x4<U> const & m)
        {
            this->value[0] -= m[0];
            this->value[1] -= m[1];
            this->value[2] -= m[2];
            this->value[3] -= m[3];
            return *this;
        }

        template <typename U>
        tmat4x4<T> & operator*= (U const & s)
        {
            this->value[0] *= s;
            this->value[1] *= s;
            this->value[2] *= s;
            this->value[3] *= s;
            return *this;
        }

        template <typename U>
        tmat4x4<T> & operator*= (tmat4x4<U> const & m)
        {
            return (*this = *this * m);
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
        template <typename U>
        tmat4x4<T> & operator/= (tmat4x4<U> const & m)
        {
            return (*this = *this / m);
        }

        tmat4x4<T> & operator++ ()
        {
            ++this->value[0];
            ++this->value[1];
            ++this->value[2];
            ++this->value[3];
            return *this;
        }

        tmat4x4<T> & operator-- ()
        {
            --this->value[0];
            --this->value[1];
            --this->value[2];
            --this->value[3];
            return *this;
        }
        tmat4x4<T>&    translate( value_type x,value_type y,value_type z)
        {
            this->value[0] = col_type(1, 0, 0, 0);
            this->value[1] = col_type(0, 1, 0, 0);
            this->value[2] = col_type(0, 0, 1, 0);
            this->value[3] = col_type(x, y, z, 1);
            return  *this;
        }
        template<typename U>
        tmat4x4<T>& translate( U x,U y,U z)
        {
            this->value[0] = col_type(1, 0, 0, 0);
            this->value[1] = col_type(0, 1, 0, 0);
            this->value[2] = col_type(0, 0, 1, 0);
            this->value[3] = col_type(T(x), T(y), T(z), 1);
            return  *this;
        }

        tmat4x4<T>& translate(tvec3<T> const& pos)
        {
            this->value[0] = col_type(1,    0,      0,      0);
            this->value[1] = col_type(0,    1,      0,      0);
            this->value[2] = col_type(0,    0,      1,      0);
            this->value[3] = col_type(pos.x,pos.y, pos.z,   1);
            return  *this;
        }
        template<typename U>
        tmat4x4<T>& translate(tvec3<U> const& pos)
        {
            this->value[0] = col_type(1,    0,      0,      0);
            this->value[1] = col_type(0,    1,      0,      0);
            this->value[2] = col_type(0,    0,      1,      0);
            this->value[3] = col_type(T(pos.x),T(pos.y), T(pos.z),   1);
            return  *this;
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

        tmat4x4<T>& rotateX(value_type angle)
        {
        	T a = DEG2RAD(angle);
            T c = cos(a);
            T s = sin(a);

            this->value[0] = col_type(1, 0, 0, 0);
            this->value[1] = col_type(0, c, s, 0);
            this->value[2] = col_type(0,-s, c, 0);
            this->value[3] = col_type(0, 0, 0, 1);

            return  *this;
        }
        template<typename U>
        tmat4x4<T>& rotateX(U angle)
        {
            T a = DEG2RAD(angle);
            T c = cos(a);
            T s = sin(a);

            this->value[0] = col_type(1, 0, 0, 0);
            this->value[1] = col_type(0, c, s, 0);
            this->value[2] = col_type(0,-s, c, 0);
            this->value[3] = col_type(0, 0, 0, 1);

            return  *this;
        }

        tmat4x4<T>& rotateY(value_type angle)
        {
        	T a = DEG2RAD(angle);
            T c = cos(a);
            T s = sin(a);

            this->value[0] = col_type(c, 0,-s, 0);
            this->value[1] = col_type(0, 1, 0, 0);
            this->value[2] = col_type(s, 0, c, 0);
            this->value[3] = col_type(0, 0, 0, 1);
            return  *this;

        }
        template<typename U>
        tmat4x4<T>& rotateY(U angle)
        {
        	T a = DEG2RAD(angle);
            T c = cos(a);
            T s = sin(a);

            this->value[0] = col_type(c, 0,-s, 0);
            this->value[1] = col_type(0, 1, 0, 0);
            this->value[2] = col_type(s, 0, c, 0);
            this->value[3] = col_type(0, 0, 0, 1);
            return  *this;

        }
        tmat4x4<T>& rotateZ(value_type angle)
        {
            T a = T(DEG2RAD(angle));		
            T c = cos(a);
            T s = sin(a);

            this->value[0] = col_type( c, s, 0, 0);
            this->value[1] = col_type(-s, c, 0, 0);
            this->value[2] = col_type( 0, 0, 1, 0);
            this->value[3] = col_type( 0, 0, 0, 1);
            return  *this;
        }
        template<typename U>
        tmat4x4<T>& rotateZ(U angle)
        {
            T a = DEG2RAD(angle);

            T c = cos(a);
            T s = sin(a);

            this->value[0] = col_type( c, s, 0, 0);
            this->value[1] = col_type(-s, c, 0, 0);
            this->value[2] = col_type( 0, 0, 1, 0);
            this->value[3] = col_type( 0, 0, 0, 1);
            return  *this;
        }

        
        tmat4x4<T> rotateXY(T angleX, T angleY)
        {
            T cosX = cos(DEG2RAD(angleX));
            T sinX = sin(DEG2RAD(angleX));
            T cosY = cos(DEG2RAD(angleY));
            T sinY = sin(DEG2RAD(angleY));


            this->value[0] = col_type( cosY,        -sinX * sinY,	cosX * sinY,0);
            this->value[1] = col_type( 0,           cosX,			sinX,       0);
            this->value[2] = col_type( -sinY ,      -sinX * cosY,	cosX * cosY,0);
            this->value[3] = col_type( 0,           0,              0,          1);
            return  *this;
        }

        tmat4x4<T> rotateYX(T angleX, T angleY)
        {
            T cosX = cos(DEG2RAD(angleX));
            T sinX = sin(DEG2RAD(angleX));
            T cosY = cos(DEG2RAD(angleY));
            T sinY = sin(DEG2RAD(angleY));


            this->value[0] = col_type( cosY,        0,		        sinY,       0);
            this->value[1] = col_type( -sinX * sinY,cosX,			sinX * cosY,0);
            this->value[2] = col_type( -cosX * sinY,-sinX,          cosX * cosY,0);
            this->value[3] = col_type( 0,           0,              0,          1);

            return  *this;
        }

        tmat4x4<T> rotateYXZ( T yaw, T pitch, T roll)
        {
            T tmp_ch = (T)cos(DEG2RAD(yaw));
            T tmp_sh = (T)sin(DEG2RAD(yaw));
            T tmp_cp = (T)cos(DEG2RAD(pitch));
            T tmp_sp = (T)sin(DEG2RAD(pitch));
            T tmp_cb = (T)cos(DEG2RAD(roll));
            T tmp_sb = (T)sin(DEG2RAD(roll));

            tmat4x4<T> Result;
            this->value[0][0] = tmp_ch * tmp_cb + tmp_sh * tmp_sp * tmp_sb;
            this->value[0][1] = tmp_sb * tmp_cp;
            this->value[0][2] = -tmp_sh * tmp_cb + tmp_ch * tmp_sp * tmp_sb;
            this->value[0][3] = T(0);
            this->value[1][0] = -tmp_ch * tmp_sb + tmp_sh * tmp_sp * tmp_cb;
            this->value[1][1] = tmp_cb * tmp_cp;
            this->value[1][2] = tmp_sb * tmp_sh + tmp_ch * tmp_sp * tmp_cb;
            this->value[1][3] = T(0);
            this->value[2][0] = tmp_sh * tmp_cp;
            this->value[2][1] = -tmp_sp;
            this->value[2][2] = tmp_ch * tmp_cp;
            this->value[2][3] = T(0);
            this->value[3][0] = T(0);
            this->value[3][1] = T(0);
            this->value[3][2] = T(0);
            this->value[3][3] = T(1);

            return  *this;
        }

        tmat4x4<T> yawPitchRoll( T yaw, T pitch, T roll)
        {
            T tmp_ch = cos(DEG2RAD(yaw));
            T tmp_sh = sin(DEG2RAD(yaw));
            T tmp_cp = cos(DEG2RAD(pitch));
            T tmp_sp = sin(DEG2RAD(pitch));
            T tmp_cb = cos(DEG2RAD(roll));
            T tmp_sb = sin(DEG2RAD(roll));

            this->value[0][0] = tmp_ch * tmp_cb + tmp_sh * tmp_sp * tmp_sb;
            this->value[0][1] = tmp_sb * tmp_cp;
            this->value[0][2] = -tmp_sh * tmp_cb + tmp_ch * tmp_sp * tmp_sb;
            this->value[0][3] = T(0);
            this->value[1][0] = -tmp_ch * tmp_sb + tmp_sh * tmp_sp * tmp_cb;
            this->value[1][1] = tmp_cb * tmp_cp;
            this->value[1][2] = tmp_sb * tmp_sh + tmp_ch * tmp_sp * tmp_cb;
            this->value[1][3] = T(0);
            this->value[2][0] = tmp_sh * tmp_cp;
            this->value[2][1] = -tmp_sp;
            this->value[2][2] = tmp_ch * tmp_cp;
            this->value[2][3] = T(0);
            this->value[3][0] = T(0);
            this->value[3][1] = T(0);
            this->value[3][2] = T(0);
            this->value[3][3] = T(1);

            return  *this;
        }

        tmat4x4<T>& scale(tvec3<T> const& s)
        {
            this->value[0] = col_type(s[0], 0,      0,      0);
            this->value[1] = col_type(0,    s[1],   0,      0);
            this->value[2] = col_type(0,    0,      s[2],   0);
            this->value[3] = col_type(0,    0,      0,      1);

            return  *this;
        }

        tmat4x4<T>& scale(value_type x,value_type y,value_type z)
        {
            this->value[0] = col_type(x, 0, 0, 0);
            this->value[1] = col_type(0, y, 0, 0);
            this->value[2] = col_type(0, 0, z, 0);
            this->value[3] = col_type(0, 0, 0, 1);

            return  *this;
        }

        template<typename U>
        tmat4x4<T>& scale(U x,U y,U z)
        {
            this->value[0] = col_type(value_type(x), 0, 0, 0);
            this->value[1] = col_type(0, value_type(y), 0, 0);
            this->value[2] = col_type(0, 0, value_type(z), 0);
            this->value[3] = col_type(0, 0, 0, 1);

            return  *this;
        }

        template<typename U,typename V,typename W>
        tmat4x4<T>& scale(U x,V y,W z)
        {
            this->value[0] = col_type(value_type(x), 0, 0, 0);
            this->value[1] = col_type(0, value_type(y), 0, 0);
            this->value[2] = col_type(0, 0, value_type(z), 0);
            this->value[3] = col_type(0, 0, 0, 1);
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

        tmat4x4<T> extractMatrixRotation() const
        {
            return  tmat4x4<T>(
                                this->value[0][0], this->value[0][1], this->value[0][2], 0.0,
                                this->value[1][0], this->value[1][1], this->value[1][2], 0.0,
                                this->value[2][0], this->value[2][1], this->value[2][2], 0.0,
                                0.0,       0.0,       0.0,       1.0
                                );
        }
        /**
         *	制作整数矩阵
         */
        void    makeInt()
        {
            T*  pData   =   (T*)data();
            for (int i = 0 ;i < 16 ; ++ i)
            {
                pData[i]    =   floor(pData[i]);
            }
        }
        /**
         *	制作整数矩阵
         */
        void    makeDec(T scales)
        {
            T*  pData   =   (T*)data();
            for (int i = 0 ;i < 16 ; ++ i)
            {
                pData[i]    =   pData[i] - floor(pData[i]);
                pData[i]    *=  scales;
            }
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
    tmat4x4<T> operator* (tmat4x4<T> const & m, typename tmat4x4<T>::value_type s)
    {
        return tmat4x4<T>(
            m[0] * s,
            m[1] * s,
            m[2] * s,
            m[3] * s);
    }

    template <typename T> 
    tmat4x4<T> operator* (typename tmat4x4<T>::value_type s, tmat4x4<T> const & m)
    {
        return tmat4x4<T>(
            m[0] * s,
            m[1] * s,
            m[2] * s,
            m[3] * s);
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
    typename tmat4x4<T>::col_type operator/ (tmat4x4<T> const & m, typename tmat4x4<T>::row_type const & v)
    {
        return m.inverse() * v;
    }

    template <typename T> 
    typename tmat4x4<T>::row_type operator/ (typename tmat4x4<T>::col_type const & v, tmat4x4<T> const & m)
    {
        return v * m.inverse();
    }

    
    //////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////
    //! 射线类
    //////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <typename T>
	typename tvec2<T>::value_type length(tvec2<T> const & v)
	{
		typename tvec2<T>::value_type sqr = v.x * v.x + v.y * v.y;
		return sqrt(sqr);
	}

	template <typename T>
	typename tvec3<T>::value_type length(tvec3<T> const & v)
	{
		typename tvec3<T>::value_type sqr = v.x * v.x + v.y * v.y + v.z * v.z;
		return sqrt(sqr);
	}

	template <typename T>
	typename tvec4<T>::value_type length(tvec4<T> const & v)
	{
		typename tvec4<T>::value_type sqr = v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w;
		return sqrt(sqr);
	}
	template <typename T>
	typename tvec2<T>::value_type distance(tvec2<T> const & p0,tvec2<T> const & p1)
	{
		return length(p1 - p0);
	}

	template <typename T>
	typename tvec3<T>::value_type distance(tvec3<T> const & p0,tvec3<T> const & p1)
	{
		return length(p1 - p0);
	}

	template <typename T>
	typename tvec4<T>::value_type distance(tvec4<T> const & p0,tvec4<T> const & p1)
	{
		return length(p1 - p0);
	}

	template <typename T>
	typename tvec2<T>::value_type dot(tvec2<T> const & x, tvec2<T> const & y)
	{
		return x.x * y.x + x.y * y.y;
	}

	template <typename T>
    typename tvec3<T>::value_type dot(tvec3<T> const & x, tvec3<T> const & y)
	{
		return x.x * y.x + x.y * y.y + x.z * y.z;
	}
	template <typename T>
	typename tvec4<T>::value_type dot(tvec4<T> const & x, tvec4<T> const & y)
	{
		return x.x * y.x + x.y * y.y + x.z * y.z + x.w * y.w;
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
	tvec2<T> normalize(tvec2<T> const & x)
	{	
		typename tvec2<T>::value_type sqr = x.x * x.x + x.y * x.y;
		return x * inversesqrt(sqr);
	}

	template <typename T>
	tvec3<T> normalize(tvec3<T> const & x)
	{
		typename tvec3<T>::value_type sqr = x.x * x.x + x.y * x.y + x.z * x.z;
		return x * inversesqrt(sqr);
	}

	template <typename T>
	tvec4<T> normalize(tvec4<T> const & x)
	{
		typename tvec4<T>::value_type sqr = x.x * x.x + x.y * x.y + x.z * x.z + x.w * x.w;
		return x * inversesqrt(sqr);
	}

    template <typename T> 
    tmat4x4<T> translate(tmat4x4<T> const & m,tvec3<T> const & v)
    {
        tmat4x4<T> res(m);
        res[3]  = m[0] * v[0] + m[1] * v[1] + m[2] * v[2] + m[3];
        return  res;
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
	    /*
	    1-----2
	    /|    /|
	    / |   / |
	    5-----4  |
	    |  0--|--3
	    | /   | /
	    |/    |/
	    6-----7
	    */
	    typedef enum 
        {
		    FAR_LEFT_BOTTOM     =   0,
		    FAR_LEFT_TOP        =   1,
		    FAR_RIGHT_TOP       =   2,
		    FAR_RIGHT_BOTTOM    =   3,
		    NEAR_RIGHT_BOTTOM   =   7,
		    NEAR_LEFT_BOTTOM    =   6,
		    NEAR_LEFT_TOP       =   5,
		    NEAR_RIGHT_TOP      =   4
	    } CornerEnum;

	    AxisAlignedBox()
	    {
		    _minimum    =   tvec3<T>( T(-0.5), T(-0.5), T(-0.5) );
		    _maximum    =   tvec3<T>( T(0.5), T(0.5), T(0.5) );
            _extent     =   EXTENT_NULL;
	    }
	    AxisAlignedBox(const AxisAlignedBox & rkBox)
	    {
            setExtents( rkBox._minimum, rkBox._maximum );
            _extent =   rkBox._extent;
	    }

	    AxisAlignedBox( const tvec3<T>& min, const tvec3<T>& max )
	    {
		    setExtents( min, max );
	    }

	    AxisAlignedBox(
		    T mx, T my, T mz,
		    T Mx, T My, T Mz
            )
	    {
		    setExtents( mx, my, mz, Mx, My, Mz );
	    }

	    AxisAlignedBox<T>& operator=(const AxisAlignedBox<T>& right)
	    {
            setExtents(right._minimum, right._maximum);
		    return *this;
	    }

	    ~AxisAlignedBox()
	    {
	    }
	    /** 
        *   Gets the minimum corner of the box.
	    */
	    const tvec3<T>& getMinimum(void) const
	    { 
		    return _minimum; 
	    }

	    /** 
        *   Gets a modifiable version of the minimum
	    *   corner of the box.
	    */
	    tvec3<T>& getMinimum(void)
	    { 
		    return _minimum; 
	    }

        void    setMinimum(const tvec3<T>& mins)
        { 
            _minimum    =   mins;
        }
        void    setMinimum(T x,T y, T z)
        { 
            _minimum    =   tvec3<T>(x,y,z);
        }
	    /** 
        *   Gets the maximum corner of the box.
	    */
	    const tvec3<T>& getMaximum(void) const
	    { 
		    return _maximum;
	    }
	    /** 
        *   Gets a modifiable version of the maximum
	    *   corner of the box.
	    */
	    tvec3<T>& getMaximum(void)
	    { 
		    return _maximum;
	    }
	    /** 
        *   Sets the maximum corner of the box.
	    */
	    void setMaximum( const tvec3<T>& vec )
	    {
		    _maximum = vec;
	    }

	    void setMaximum( T x, T y, T z )
	    {
		    _maximum.x = x;
		    _maximum.y = y;
		    _maximum.z = z;
	    }

	    /** 
        *   Changes one of the components of the maximum corner of the box
	    *   used to resize only one dimension of the box
	    */
	    void setMaximumX( T x )
	    {
		    _maximum.x = x;
	    }

	    void setMaximumY( T y )
	    {
		    _maximum.y = y;
	    }

	    void setMaximumZ( T z )
	    {
		    _maximum.z = z;
	    }

	    /** 
        *   Sets both minimum and maximum extents at once.
	    */
	    void setExtents( const tvec3<T>& min, const tvec3<T>& max )
	    {
		    _minimum    =   min;
		    _maximum    =   max;
            _extent     =   EXTENT_FINITE;
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

	    /** Returns a pointer to an array of 8 corner points, useful for
	    collision vs. non-aligned objects.
	    @remarks
	    If the order of these corners is important, they are as
	    follows: The 4 points of the minimum Z face (note that
	    because Ogre uses right-handed coordinates, the minimum Z is
	    at the 'back' of the box) starting with the minimum point of
	    all, then anticlockwise around this face (if you are looking
	    onto the face from outside the box). Then the 4 points of the
	    maximum Z face, starting with maximum point of all, then
	    anticlockwise around this face (looking onto the face from
	    outside the box). Like this:
	    <pre>
	    1-----2
	    /|    /|
	    / |   / |
	    5-----4  |
	    |  0--|--3
	    | /   | /
	    |/    |/
	    6-----7
	    </pre>
	    @remarks as this implementation uses a static member, make sure to use your own copy !
	    */
        template<typename U>
        void    getAllCorners(tvec3<U> outCorners[8] ) const
        {
            outCorners[0].x     =   (U)_minimum.x; outCorners[0].y     =   (U)_minimum.y; outCorners[0].z =   (U)_minimum.z;
            outCorners[1].x     =   (U)_minimum.x; outCorners[1].y     =   (U)_maximum.y; outCorners[1].z =   (U)_minimum.z;
            outCorners[2].x     =   (U)_maximum.x; outCorners[2].y     =   (U)_maximum.y; outCorners[2].z =   (U)_minimum.z;
            outCorners[3].x     =   (U)_maximum.x; outCorners[3].y     =   (U)_minimum.y; outCorners[3].z =   (U)_minimum.z;            

            outCorners[4].x     =   (U)_maximum.x; outCorners[4].y     =   (U)_maximum.y; outCorners[4].z =   (U)_maximum.z;
            outCorners[5].x     =   (U)_minimum.x; outCorners[5].y     =   (U)_maximum.y; outCorners[5].z =   (U)_maximum.z;
            outCorners[6].x     =   (U)_minimum.x; outCorners[6].y     =   (U)_minimum.y; outCorners[6].z =   (U)_maximum.z;
            outCorners[7].x     =   (U)_maximum.x; outCorners[7].y     =   (U)_minimum.y; outCorners[7].z =   (U)_maximum.z;
        }

	    /** 
        *   gets the position of one of the corners
	    */
	    tvec3<T> getCorner(CornerEnum cornerToGet) const
	    {
		    switch(cornerToGet)
		    {
		    case FAR_LEFT_BOTTOM:
			    return _minimum;
		    case FAR_LEFT_TOP:
			    return tvec3<T>(_minimum.x, _maximum.y, _minimum.z);
		    case FAR_RIGHT_TOP:
			    return tvec3<T>(_maximum.x, _maximum.y, _minimum.z);
		    case FAR_RIGHT_BOTTOM:
			    return tvec3<T>(_maximum.x, _minimum.y, _minimum.z);
		    case NEAR_RIGHT_BOTTOM:
			    return tvec3<T>(_maximum.x, _minimum.y, _maximum.z);
		    case NEAR_LEFT_BOTTOM:
			    return tvec3<T>(_minimum.x, _minimum.y, _maximum.z);
		    case NEAR_LEFT_TOP:
			    return tvec3<T>(_minimum.x, _maximum.y, _maximum.z);
		    case NEAR_RIGHT_TOP:
			    return _maximum;
		    default:
			    return tvec3<T>();
		    }
	    }

	    /** 
        *   Merges the passed in box into the current box. The result is the
	    *   box which encompasses both.
	    */
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

	    /** 
        *   Extends the box to encompass the specified point (if needed).
	    */
	    void merge( const tvec3<T>& point )
	    {
            switch (_extent)
            {
            case EXTENT_NULL: // if null, use this point
                setExtents(point, point);
                return;

            case EXTENT_FINITE:
                _maximum.makeCeil(point);
                _minimum.makeFloor(point);
                return;

            case EXTENT_INFINITE:
                return;
            }
	    }
	    void transform( const tmat4x4<T>& matrix )
	    {
            tvec3<T>    oldMin;
            tvec3<T>    oldMax;
            tvec3<T>    currentCorner;

            oldMin  = _minimum;
            oldMax  = _maximum;


            // We sequentially compute the corners in the following order :
            // 0, 6, 5, 1, 2, 4 ,7 , 3
            // This sequence allows us to only change one member at a time to get at all corners.

            // For each one, we transform it using the matrix
            // Which gives the resulting point and merge the resulting point.

            currentCorner   =   oldMin;
            tvec3<T> vVert  =   currentCorner * matrix;
            setExtents(vVert,vVert);

            // First corner 
            // min min min
            currentCorner = oldMin;
            merge( currentCorner * matrix );

            // min,min,max
            currentCorner.z = oldMax.z;
            merge( currentCorner * matrix );

            // min max max
            currentCorner.y = oldMax.y;
            merge( currentCorner * matrix );

            // min max min
            currentCorner.z = oldMin.z;
            merge( currentCorner * matrix );

            // max max min
            currentCorner.x = oldMax.x;
            merge( currentCorner * matrix );

            // max max max
            currentCorner.z = oldMax.z;
            merge( currentCorner * matrix );

            // max min max
            currentCorner.y = oldMin.y;
            merge( currentCorner * matrix);

            // max min min
            currentCorner.z = oldMin.z;
            merge( currentCorner * matrix); 
	    }

	    /** 
        *   Returns whether or not this box intersects another. 
        */
	    bool intersects(const AxisAlignedBox& b2) const
	    {
		    if (_maximum.x < b2._minimum.x)
			    return false;
		    if (_maximum.y < b2._minimum.y)
			    return false;
		    if (_maximum.z < b2._minimum.z)
			    return false;

		    if (_minimum.x > b2._maximum.x)
			    return false;
		    if (_minimum.y > b2._maximum.y)
			    return false;
		    if (_minimum.z > b2._maximum.z)
			    return false;
		    return true;

	    }

        /** 
        *   Returns whether or not this box intersects another. 
        */
	    bool intersectsNoZ(const AxisAlignedBox& b2) const
	    {
		    if (_maximum.x < b2._minimum.x)
			    return false;
		    if (_maximum.y < b2._minimum.y)
			    return false;

		    if (_minimum.x > b2._maximum.x)
			    return false;
		    if (_minimum.y > b2._maximum.y)
			    return false;
		    return true;

	    }

        
	    AxisAlignedBox<T> intersection(const AxisAlignedBox<T>& b2) const
	    {
		    tvec3<T> intMin = _minimum;
            tvec3<T> intMax = _maximum;

            intMin.makeCeil(b2.getMinimum());
            intMax.makeFloor(b2.getMaximum());

            if (intMin.x < intMax.x &&
                intMin.y < intMax.y &&
                intMin.z < intMax.z)
            {
                return AxisAlignedBox<T>(intMin, intMax);
            }

            return AxisAlignedBox<T>();
	    }
        void    setNull()
        {
	        _extent = EXTENT_NULL;
        }

        bool    isNull(void) const
        {
	        return (_extent == EXTENT_NULL);
        }

        bool    isFinite(void) const
        {
	        return (_extent == EXTENT_FINITE);
        }

        void    setInfinite()
        {
	        _extent = EXTENT_INFINITE;
        }
        bool    isInfinite(void) const
        {
	        return (_extent == EXTENT_INFINITE);
        }

	    void    scale(const tvec3<T>& s)
	    {
		    tvec3<T> min = _minimum * s;
		    tvec3<T> max = _maximum * s;
		    setExtents(min, max);
	    }
	    
	    bool    intersects(const tvec3<T>& v) const
	    {
            return( v.x >= _minimum.x  &&  v.x <= _maximum.x  && 
                    v.y >= _minimum.y  &&  v.y <= _maximum.y  && 
                    v.z >= _minimum.z  &&  v.z <= _maximum.z);
	    }

        bool    intersects(const tvec2<T>& v) const
        {
            return( v.x >= _minimum.x  &&  v.x <= _maximum.x  && 
                    v.y >= _minimum.y  &&  v.y <= _maximum.y );
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

        bool contains(const tvec3<T>& v) const
        {
            return _minimum.x <= v.x && v.x <= _maximum.x &&
                   _minimum.y <= v.y && v.y <= _maximum.y &&
                   _minimum.z <= v.z && v.z <= _maximum.z;
        }

        bool contains(const AxisAlignedBox& other) const
        {
            return this->_minimum.x <= other._minimum.x &&
                   this->_minimum.y <= other._minimum.y &&
                   this->_minimum.z <= other._minimum.z &&
                   other._maximum.x <= this->_maximum.x &&
                   other._maximum.y <= this->_maximum.y &&
                   other._maximum.z <= this->_maximum.z;
        }
        bool operator== (const AxisAlignedBox& right) const
        {
            return this->_minimum == right._minimum &&
                   this->_maximum == right._maximum;
        }
        bool operator!= (const AxisAlignedBox& right) const
        {
            return !(*this == right);
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
        tray(const tvec3<T>& origin, const tvec3<T>& direction):
            _origin(origin), 
            _direction(direction)
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

        /**
        *   测试射线box相交
        *   如果相交,返回值中的first == true.否则false
        *   second为射线到点的距离
        *   调用getPoint方法，则返回交点
        */
	    std::pair<bool, T> intersects(const AxisAlignedBox<T>& box) const
        {
            T           lowt    = 0.0f;
            T           t;
            bool        hit     = false;
            tvec3<T>    hitpoint;
            tvec3<T>    min      =   box.getMinimum();
            tvec3<T>    max      =   box.getMaximum();

            /**
            *   点在包围盒里面
            */
            if ( _origin > min && _origin < max )
            {
                return std::pair<bool, T>(true, 0.0f);
            }

            // Check each face in turn, only check closest 3
            // Min x
            if (_origin.x <= min.x && _direction.x > 0)
            {
                t   =   (min.x - _origin.x) / _direction.x;
                if (t >= 0)
                {
                    // Substitute t back into ray and check bounds and dist
                    hitpoint = _origin + _direction * t;
                    if (hitpoint.y >= min.y && 
                        hitpoint.y <= max.y &&
                        hitpoint.z >= min.z && 
                        hitpoint.z <= max.z &&
                        (!hit || t < lowt))
                    {
                        hit     =   true;
                        lowt    =   t;
                    }
                }
            }
            // Max x
            if (_origin.x >= max.x && _direction.x < 0)
            {
                t   =   (max.x - _origin.x) / _direction.x;
                if (t >= 0)
                {
                    // Substitute t back into ray and check bounds and dist
                    hitpoint = _origin + _direction * t;
                    if (hitpoint.y >= min.y && 
                        hitpoint.y <= max.y &&
                        hitpoint.z >= min.z &&
                        hitpoint.z <= max.z &&
                        (!hit || t < lowt))
                    {
                        hit     =   true;
                        lowt    =   t;
                    }
                }
            }
            // Min y
            if (_origin.y <= min.y && _direction.y > 0)
            {
                t   =   (min.y - _origin.y) / _direction.y;
                if (t >= 0)
                {
                    // Substitute t back into ray and check bounds and dist
                    hitpoint = _origin + _direction * t;
                    if (hitpoint.x >= min.x && 
                        hitpoint.x <= max.x &&
                        hitpoint.z >= min.z && 
                        hitpoint.z <= max.z &&
                        (!hit || t < lowt))
                    {
                        hit     =   true;
                        lowt    =   t;
                    }
                }
            }
            // Max y
            if (_origin.y >= max.y && _direction.y < 0)
            {
                t   =   (max.y - _origin.y) / _direction.y;
                if (t >= 0)
                {
                    // Substitute t back into ray and check bounds and dist
                    hitpoint = _origin + _direction * t;
                    if (hitpoint.x >= min.x &&
                        hitpoint.x <= max.x &&
                        hitpoint.z >= min.z &&
                        hitpoint.z <= max.z &&
                        (!hit || t < lowt))
                    {
                        hit     =   true;
                        lowt    =   t;
                    }
                }
            }
            // Min z
            if (_origin.z <= min.z && _direction.z > 0)
            {
                t   =   (min.z - _origin.z) / _direction.z;
                if (t >= 0)
                {
                    // Substitute t back into ray and check bounds and dist
                    hitpoint = _origin + _direction * t;
                    if (hitpoint.x >= min.x && 
                        hitpoint.x <= max.x &&
                        hitpoint.y >= min.y &&
                        hitpoint.y <= max.y &&
                        (!hit || t < lowt))
                    {
                        hit     =   true;
                        lowt    =   t;
                    }
                }
            }
            // Max z
            if (_origin.z >= max.z && _direction.z < 0)
            {
                t   =   (max.z - _origin.z) / _direction.z;
                if (t >= 0)
                {
                    // Substitute t back into ray and check bounds and dist
                    hitpoint = _origin + _direction * t;
                    if (hitpoint.x >= min.x && 
                        hitpoint.x <= max.x &&
                        hitpoint.y >= min.y && 
                        hitpoint.y <= max.y &&
                        (!hit || t < lowt))
                    {
                        hit     =   true;
                        lowt    =   t;
                    }
                }
            }
            return std::pair<bool, T>(hit, lowt);
        }

        std::pair<bool, T> intersectSphere(const tvec3<T>& center,T radius)  const
        {
            tvec3<T> raydir = _direction;
            // Adjust ray origin relative to sphere center
            tvec3<T> rayorig = _origin - center;
           
            T       len =   CELL::length(rayorig) *  CELL::length(rayorig);
            // Check origin inside first
            if (len <= radius * radius )
            {
                return std::pair<bool, T>(true, 0);
            }

            // Mmm, quadratics
            // Build coeffs which can be used with std quadratic solver
            // ie t = (-b +/- sqrt(b*b + 4ac)) / 2a
            T a     =   CELL::dot(raydir,raydir);
            T b     =   2 * CELL::dot(rayorig,raydir);
            T c     =   CELL::dot(rayorig,rayorig)- radius * radius;

            T d     = (b*b) - (4 * a * c);
            if (d < 0)
            {
                // No intersection
                return std::pair<bool, T>(false, (T)0);
            }
            else
            {
                // BTW, if d=0 there is one intersection, if d > 0 there are 2
                // But we only want the closest one, so that's ok, just use the 
                // '-' version of the solver
                T t = (-b - sqrt(d)) / (2 * a);
                if (t < 0)
                    t = (-b + sqrt(d)) / (2 * a);
                return std::pair<bool, T>(true, (T)t);
            }
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
        Plane (const Plane& right)
        {
            _normal     =   right._normal;
            _distance   =   right._distance;
        }
        /** Construct a plane through a normal, and a distance to move the plane along the normal.*/
        Plane (const tvec3<T>& rkNormal, T fConstant)
        {
            _normal     =   rkNormal;
            _distance   =   -fConstant;
        }
	    /** Construct a plane using the 4 constants directly **/
        Plane (T x, T y, T z, T o)
        {
            _normal     =   tvec3<T>(x, y, z);
            T invLen    = 1.0f / (_normal).length();
            _normal     *=  invLen;
            _distance   =   o * invLen;
        }
        Plane (const tvec3<T>& rkNormal, const tvec3<T>& rkPoint)
        {
            redefine(rkNormal, rkPoint);
        }
        Plane (const tvec3<T>& rkPoint0, const tvec3<T>& rkPoint1,const tvec3<T>& rkPoint2)
        {
            redefine(rkPoint0, rkPoint1, rkPoint2);
        }
        /**
        *   到点的距离
        */
        T   distance(const tvec3<T> &pos) const
        {
            return  dot(_normal,pos) + _distance;
        }

        /** The "positive side" of the plane is the half space to which the
            plane normal points. The "negative side" is the other half
            space. The flag "no side" indicates the plane itself.
        */
        enum Side
        {
            NO_SIDE,
            POSITIVE_SIDE,
            NEGATIVE_SIDE,
            BOTH_SIDE
        };

        Side getSide (const tvec3<T>& rkPoint) const
        {
            float fDistance = getDistance(rkPoint);

            if ( fDistance < 0.0 )
                return Plane::NEGATIVE_SIDE;

            if ( fDistance > 0.0 )
                return Plane::POSITIVE_SIDE;

            return Plane::NO_SIDE;
        }

        
        Side getSide (const tvec3<T>& centre, const tvec3<T>& halfSize) const
        {
            // Calculate the distance between box centre and the plane
            float dist = getDistance(centre);

            // Calculate the maximise allows absolute distance for
            // the distance between box centre and plane
            float maxAbsDist = _normal.absDot(halfSize);

            if (dist < -maxAbsDist)
                return Plane::NEGATIVE_SIDE;

            if (dist > +maxAbsDist)
                return Plane::POSITIVE_SIDE;

            return Plane::BOTH_SIDE;
        }

        float getDistance (const tvec3<T>& rkPoint) const
        {
            return _normal.dot(rkPoint) + _distance;
        }

        void redefine(const tvec3<T>& rkPoint0, const tvec3<T>& rkPoint1,
            const tvec3<T>& rkPoint2)
        {
            tvec3<T> kEdge1 = rkPoint1 - rkPoint0;
            tvec3<T> kEdge2 = rkPoint2 - rkPoint0;
            _normal = cross(kEdge1,kEdge2);
            _normal.normalise();
            _distance = -dot(_normal,rkPoint0);
        }

	    /** Redefine this plane based on a normal and a point. */
	    void redefine(const tvec3<T>& rkNormal, const tvec3<T>& rkPoint)
        {
            _normal = rkNormal;
            _distance = -dot(rkNormal,rkPoint);
        }

    	
// 	    tvec3<T> projectVector(const tvec3<T>& p) const
//         {
//             matrix3 xform;
//             xform[0][0] = 1.0f - _normal.x * _normal.x;
//             xform[0][1] = -_normal.x * _normal.y;
//             xform[0][2] = -_normal.x * _normal.z;
//             xform[1][0] = -_normal.y * _normal.x;
//             xform[1][1] = 1.0f - _normal.y * _normal.y;
//             xform[1][2] = -_normal.y * _normal.z;
//             xform[2][0] = -_normal.z * _normal.x;
//             xform[2][1] = -_normal.z * _normal.y;
//             xform[2][2] = 1.0f - _normal.z * _normal.z;
//             return xform * p;
//         }

        /** Normalises the plane.
            @remarks
                This method normalises the plane's normal and the length scale of d
                is as well.
            @note
                This function will not crash for zero-sized vectors, but there
                will be no changes made to their components.
            @returns The previous length of the plane's normal.
        */
        float normalise(void)
        {
            float fLength = _normal.length();

            // Will also work for zero-sized vectors, but will change nothing
            if (fLength > 1e-08f)
            {
                float fInvLength = 1.0f / fLength;
                _normal *= fInvLength;
                _distance *= fInvLength;
            }

            return fLength;
        }

        /// Comparison operator
        bool operator==(const Plane& right) const
        {
            return (right._distance == _distance && right._normal == _normal);
        }
        bool operator!=(const Plane& right) const
        {
            return (right._distance != _distance && right._normal != _normal);
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
