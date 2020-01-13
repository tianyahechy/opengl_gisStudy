#pragma once
#include <cstdio>
#include <cassert>
#include <cmath>
#include <vector>
#include <map>
#include <limits>
#include <xutility>
#include "CELLMath.hpp"


namespace CELL
{

#define	TWO_PI						( PI * 2)
#define HALF_PI						(3.14159265358979323846264338327 * 0.5)

#define LOG2						0.69314718055994529
#define WGS_84_RADIUS_EQUATOR_		6378137.0
#define WGS_84_RADIUS_POLAR_		6356752.3142

#define MIN(a,b)					((a) < (b) ? (a) : (b))
#define MAX(a,b)					((a) > (b) ? (a) : (b))
#define MAX_USHORT					65536
#define MIN_USHORT					0

#define MAKE_INT(a, b)          ((int)(((short)(((int)(a)) & 0xffff)) | ((int)((short)(((int)(b)) & 0xffff))) << 16))
#define MAKE_UINT(a, b)         ((uint)(((ushort)(((uint)(a)) & 0xffff)) | ((uint)((ushort)(((uint)(b)) & 0xffff))) << 16))
#define GET_LWORD(l)            ((ushort)(((uint)(l)) & 0xffff))
#define GET_HIWORD(l)           ((ushort)((((uint)(l)) >> 16) & 0xffff))

	inline  ushort  rgb_24_2_565(int r, int g, int b)
	{
		return (ushort)(((unsigned(r) << 8) & 0xF800) |
			((unsigned(g) << 3) & 0x7E0) |
			((unsigned(b) >> 3)));
	}

	inline  void rgb565_2_rgb24(byte *rgb24, ushort rgb565)
	{
#define RGB565_MASK_RED         0xF800   
#define RGB565_MASK_GREEN       0x07E0   
#define RGB565_MASK_BLUE        0x001F 

		//extract RGB   
		rgb24[2] = (byte)((rgb565 & RGB565_MASK_RED) >> 11);
		rgb24[1] = (byte)((rgb565 & RGB565_MASK_GREEN) >> 5);
		rgb24[0] = (byte)((rgb565 & RGB565_MASK_BLUE));

		//amplify the image   
		rgb24[2] <<= 3;
		rgb24[1] <<= 2;
		rgb24[0] <<= 3;
	}

	/**
	*   点在多边形里
	*   如果点在多边形中，则，点与边的夹角之和 == 360
	*/
	template<typename T>
	bool    insidePolyon(const tvec3<T>& point, const tvec3<T> polygon[], size_t count)
	{
		T           MATCH_FACTOR = T(0.99);
		T           angle = T(0.0);
		tvec3<T>    vA, vB;
		for (size_t i = 0; i < count; ++i)
		{
			vA = polygon[i] - point;
			vB = polygon[(i + 1) % count] - point;
			angle += angleBetweenVector(vA, vB);
		}
		if (angle >= (MATCH_FACTOR * TWO_PI))
		{
			return true;
		}
		return false;
	}

	template<typename T>
	bool    insidePolyon(const tvec2<T>& point, const tvec2<T> polygon[], size_t count)
	{
		T           MATCH_FACTOR = T(0.99);
		T           angle = T(0.0);
		tvec2<T>    vA, vB;
		for (size_t i = 0; i < count; ++i)
		{
			vA = polygon[i] - point;
			vB = polygon[(i + 1) % count] - point;
			tvec3<T>    a(vA.x, vA.y, 0);
			tvec3<T>    b(vB.x, vB.y, 0);
			angle += angleBetweenVector<T>(a, b);
		}
		if (angle >= (MATCH_FACTOR * TWO_PI))
		{
			return true;
		}
		return false;
	}

	template<typename T>
	bool pointinTriangle(tvec3<T> A, tvec3<T> B, tvec3<T> C, tvec3<T> P)
	{
		tvec3<T> v0 = C - A;
		tvec3<T> v1 = B - A;
		tvec3<T> v2 = P - A;

		float dot00 = dot(v0, v0);
		float dot01 = dot(v0, v1);
		float dot02 = dot(v0, v2);
		float dot11 = dot(v1, v1);
		float dot12 = dot(v1, v2);

		float inverDeno = 1 / (dot00 * dot11 - dot01 * dot01);

		float u = (dot11 * dot02 - dot01 * dot12) * inverDeno;
		if (u < 0 || u > 1) // if u out of range, return directly
		{
			return false;
		}

		float v = (dot00 * dot12 - dot01 * dot02) * inverDeno;
		if (v < 0 || v > 1) // if v out of range, return directly
		{
			return false;
		}

		return u + v <= 1;
	}

	template<typename T>
	bool pointinTriangle(tvec2<T> A, tvec2<T> B, tvec2<T> C, tvec2<T> P)
	{
		return   pointinTriangle(
			tvec3<T>(A.x, A.y, 0),
			tvec3<T>(B.x, B.y, 0),
			tvec3<T>(C.x, C.y, 0),
			tvec3<T>(P.x, P.y, 0));
	}

	template<typename T>
	inline  T angleBetween(const tvec3<T>& a, const tvec3<T>& b)
	{
		T lenProduct = a.lengthf() * b.lengthf();

		// Divide by zero check
		if (lenProduct < 1e-6f)
			lenProduct = 1e-6f;

		float f = dot(a, b) / lenProduct;

		f = clamp(f, T(-1.0), T(1.0));
		return acosEx(f);

	}
	/// <summary>
	/// 计算包围球数据
	/// </summary>
	template<class T>
	tvec4<T>        calcSphere(const tvec3<T>* pPos, uint nCount, uint stride)
	{
		AxisAlignedBox<T>   aabb = calcAabb<T>(pPos, nCount, stride);
		tvec3<T>            center = aabb.getCenter();
		T                   radius = CELL::length(aabb.getHalfSize());
		return  tvec4<T>(center.x, center.y, center.z, radius);
	}
	/// <summary>
	/// 计算包围盒数据
	/// </summary>
	template<class T>
	AxisAlignedBox<T> calcAabb(const tvec3<T>* pPos, uint nCount, uint stride)
	{
		char*       pData = (char*)pPos;
		tvec3<T>*   pCur = (tvec3<T>*)pPos;

		AxisAlignedBox<T> aabb;
		aabb._minimum.x = FLT_MAX;
		aabb._minimum.y = FLT_MAX;
		aabb._minimum.z = FLT_MAX;

		aabb._maximum.x = -FLT_MAX;
		aabb._maximum.y = -FLT_MAX;
		aabb._maximum.z = -FLT_MAX;
		aabb._extent = AxisAlignedBox<T>::EXTENT_FINITE;

		for (uint i = 0;i < nCount; ++i)
		{
			pData += stride;
			pCur = (tvec3<T>*)pCur;
			aabb._minimum.x = CELL::tmin<T>(pCur[i].x, aabb._minimum.x);
			aabb._minimum.y = CELL::tmin<T>(pCur[i].y, aabb._minimum.y);
			aabb._minimum.z = CELL::tmin<T>(pCur[i].z, aabb._minimum.z);

			aabb._maximum.x = CELL::tmax<T>(pCur[i].x, aabb._maximum.x);
			aabb._maximum.y = CELL::tmax<T>(pCur[i].y, aabb._maximum.y);
			aabb._maximum.z = CELL::tmax<T>(pCur[i].z, aabb._maximum.z);
		}
		return  aabb;
	}

	/// <summary>
	/// 获取文件名称
	/// </summary>
	/// <param name="fileName">文件全路径名称</param>
	static  inline  char*    getFileName(char* fileName)
	{
		size_t  len = strlen(fileName);
		for (size_t i = len - 1; fileName[i]; --i)
		{
			if (fileName[i] == '/' || fileName[i] == '\\')
			{
				return  fileName + i;
			}
		}
		return  0;
	}
	/// <summary>
	/// 获取文件路径
	/// </summary>
	/// <param name="fileName">文件名称,全路径名称</param>
	/// <param name="path">径名</param>
	static  inline  bool    getFilePath(const char* fileName, char path[256])
	{
		size_t  len = strlen(fileName);
		for (size_t i = len - 1; fileName[i]; --i)
		{
			if (fileName[i] == '/' || fileName[i] == '\\')
			{
				strncpy(path, fileName, i);
				return  true;
			}
		}
		return  false;
	}

	/// <summary>
	/// 获取文件扩展名
	/// </summary>
	/// <param name="fileName">文件名称</param>
	static  inline  char*   getFileExt(char* fileName)
	{
		size_t  len = strlen(fileName);
		char*   pEnd = fileName + len;
		while (pEnd > fileName)
		{
			if (*pEnd == '.')
				return  pEnd;
			else
				--pEnd;
		}
		if (pEnd == fileName)
			return  0;
		else
			return  pEnd;
	}

	/// 根据字符串生成hashcode
	inline  int     stringHashCode(const char* pStr)
	{
		int h = 0;
		for (int i = 0; pStr[i]; i++)
		{
			h = 31 * h + pStr[i];
		}
		return h;
	}
	class   Rgba4Byte
	{
	public:
		Rgba4Byte(
			unsigned char r = 255,
			unsigned char g = 255,
			unsigned char b = 255,
			unsigned char a = 255
		)
		{
			_r = r;
			_g = g;
			_b = b;
			_a = a;
		}
		friend  bool    operator == (const Rgba4Byte& left, const Rgba4Byte& right)
		{
			return  left._r == right._r &&
				left._g == right._g &&
				left._b == right._b &&
				left._a == right._a;
		}
		friend  bool    operator != (const Rgba4Byte& left, const Rgba4Byte& right)
		{
			return  left._r != right._r ||
				left._g != right._g ||
				left._b != right._b ||
				left._a != right._a;
		}
		operator unsigned()
		{
			unsigned    color;
			char*       pColor = (char*)&color;
			pColor[0] = _r;
			pColor[1] = _g;
			pColor[2] = _b;
			pColor[3] = _a;
			return  color;
		}
		operator int()
		{
			int         color;
			char*       pColor = (char*)&color;
			pColor[0] = _r;
			pColor[1] = _g;
			pColor[2] = _b;
			pColor[3] = _a;
			return  color;
		}
		operator long()
		{
			long        color;
			char*       pColor = (char*)&color;
			pColor[0] = _r;
			pColor[1] = _g;
			pColor[2] = _b;
			pColor[3] = _a;
			return  color;
		}
	public:
		unsigned char   _r;
		unsigned char   _g;
		unsigned char   _b;
		unsigned char   _a;
	};

	typedef Rgba4Byte   Rgba;

	inline  Rgba4Byte   colorLerp(const Rgba4Byte& c1, const Rgba4Byte& c2, float s)
	{
		Rgba4Byte   color;

		color._r = (unsigned char)(c1._r + s * (c2._r - c1._r));
		color._g = (unsigned char)(c1._g + s * (c2._g - c1._g));
		color._b = (unsigned char)(c1._b + s * (c2._b - c1._b));
		color._a = (unsigned char)(c1._a + s * (c2._a - c1._a));
		return color;
	}
	inline  Rgba4Byte   quantiseNormal(const tvec3<float>& input)
	{
		// -1.0 - 1.f -> 0.f - 255.f
		return  Rgba((unsigned char)((input.x * 127.f)),
			(unsigned char)((input.y * 127.f)),
			(unsigned char)((input.z * 127.f)),
			255
		);
	}

	inline  uint    compressFloat3To101010Rev(float x, float y, float z)
	{
		return  ((((uint)(x *511.0f)) & 0x000003ff) << 0L) |
			((((uint)(y *511.0f)) & 0x000003ff) << 10L) |
			((((uint)(z *511.0f)) & 0x000003ff) << 20L);
	}

	inline int roundToInt(float x)
	{
		if (x > 0)
		{
			return int(x + 0.5f);
		}
		else
		{
			return int(x - 0.5f);
		}
	}

	inline uint getLowerPowerOfTwo(const uint x)
	{
		unsigned int i = 1;
		while (i <= x) i += i;

		return i >> 1;
	}

	inline uint getUpperPowerOfTwo(const uint x)
	{
		uint i = 1;
		while (i < x) i += i;

		return i;
	}

	inline uint getClosestPowerOfTwo(const uint x)
	{
		uint i = 1;
		while (i < x) i += i;

		if (4 * x < 3 * i) i >>= 1;
		return i;
	}

	template <typename T>
	class   tAxisAlignedBox2
	{
	public:
		enum Extent
		{
			EXTENT_NULL,
			EXTENT_FINITE,
			EXTENT_INFINITE
		};
	public:
		tvec2<T>    _vMin;
		tvec2<T>    _vMax;
		Extent      mExtent;
	public:
		tvec2<T>    center() const
		{
			return  (_vMin + _vMax) * T(0.5);
		}

		tvec2<T>    size() const
		{
			return  _vMax - _vMin;
		}

		tvec2<T>    halfSize() const
		{
			return  (_vMax - _vMin) * T(0.5);
		}

		bool    intersects(tvec2<T> v) const
		{
			return(v.x >= _vMin.x  &&  v.x <= _vMax.x  &&
				v.y >= _vMin.y  &&  v.y <= _vMax.y);
		}

		void    merge(tvec2<T> point)
		{
			if (_vMin.x > point.x)
			{
				_vMin.x = point.x;
			}

			if (_vMin.y > point.y)
			{
				_vMin.y = point.y;
			}
			if (_vMax.x < point.x)
			{
				_vMax.x = point.x;
			}
			if (_vMax.y < point.y)
			{
				_vMax.y = point.y;
			}
		}

		void    merge(tAxisAlignedBox2<T> other)
		{
			_vMax.makeCeil(other._vMax);
			_vMin.makeFloor(other._vMin);
		}

		bool    contains(tvec2<T> point) const
		{
			return  _vMin.x <= point.x && point.x <= _vMax.x &&
				_vMin.y <= point.y && point.y <= _vMax.y;
		}

		bool    contains(tAxisAlignedBox2<T> other) const
		{
			return  this->_vMin.x <= other._vMin.x &&
				this->_vMin.y <= other._vMin.y &&
				other._vMax.x <= this->_vMax.x &&
				other._vMax.y <= this->_vMax.y;
		}
	};

	template < typename T >
	class tellipsoidModel
	{
	public:
		tellipsoidModel(T radiusEquator = T(WGS_84_RADIUS_EQUATOR), T radiusPolar = T(WGS_84_RADIUS_POLAR))
		{
			_radiusEquator = radiusEquator;
			_radiusPolar = radiusPolar;
			T   flattening = (_radiusEquator - _radiusPolar) / _radiusEquator;
			_eccentricitySquared = T(2)*flattening - flattening*flattening;
		}

		~tellipsoidModel(void)
		{
		}


		void    convertLatLongHeightToXYZ(
			T latitude,
			T longitude,
			T height,
			T& X,
			T& Y,
			T& Z
		) const
		{
			// for details on maths see http://www.colorado.edu/geography/gcraft/notes/datum/gif/llhxyz.gif
			T  sin_latitude = sin(latitude);
			T  cos_latitude = cos(latitude);
			T  N = _radiusEquator / sqrt(1.0 - _eccentricitySquared*sin_latitude*sin_latitude);
			X = (N + height) * cos_latitude*cos(longitude);
			Y = (N + height) * cos_latitude*sin(longitude);
			Z = (N*(1 - _eccentricitySquared) + height)*sin_latitude;
		}


		void    convertXYZToLatLongHeight(
			T X,
			T Y,
			T Z,
			T& latitude,
			T& longitude,
			T& height
		) const
		{
			// http://www.colorado.edu/geography/gcraft/notes/datum/gif/xyzllh.gif
			T  p = (T)sqrt(X*X + Y*Y);
			T  theta = (T)atan2(Z*_radiusEquator, (p*_radiusPolar));
			T  eDashSquared = (_radiusEquator*_radiusEquator - _radiusPolar*_radiusPolar) / (_radiusPolar*_radiusPolar);

			T  sin_theta = (T)sin(theta);
			T  cos_theta = (T)cos(theta);

			latitude = (T)atan((Z + eDashSquared*_radiusPolar*sin_theta*sin_theta*sin_theta) /
				(p - _eccentricitySquared*_radiusEquator*cos_theta*cos_theta*cos_theta));
			longitude = (T)atan2(Y, X);

			T  sin_latitude = (T)sin(latitude);
			T  N = _radiusEquator / (T)sqrt(1.0 - _eccentricitySquared*sin_latitude*sin_latitude);

			height = p / (T)cos(latitude) - N;
		}

	protected:
		T  _radiusEquator;
		T  _radiusPolar;
		T  _eccentricitySquared;
	};


	template<typename T>
	class   tspline
	{
	public:
		tspline()
		{
			mCoeffs[0][0] = 2;
			mCoeffs[0][1] = -2;
			mCoeffs[0][2] = 1;
			mCoeffs[0][3] = 1;
			mCoeffs[1][0] = -3;
			mCoeffs[1][1] = 3;
			mCoeffs[1][2] = -2;
			mCoeffs[1][3] = -1;
			mCoeffs[2][0] = 0;
			mCoeffs[2][1] = 0;
			mCoeffs[2][2] = 1;
			mCoeffs[2][3] = 0;
			mCoeffs[3][0] = 1;
			mCoeffs[3][1] = 0;
			mCoeffs[3][2] = 0;
			mCoeffs[3][3] = 0;

			mCoeffs = mCoeffs.transpose();
			mAutoCalc = true;
		}
		~tspline() {};

		void addPoint(const tvec3<T>& p)
		{
			mPoints.push_back(p);
			if (mAutoCalc)
			{
				recalcTangents();
			}
		}

		const tvec3<T>& getPoint(size_t index) const
		{
			assert(index < mPoints.size() && "Point index is out of bounds!!");

			return mPoints[index];
		}
		tvec3<T>& getPoint(size_t index)
		{
			assert(index < mPoints.size() && "Point index is out of bounds!!");

			return mPoints[index];
		}

		/**
		*   获取点的数量
		*/
		size_t getNumPoints(void) const
		{
			return  mPoints.size();
		}
		/**
		*   清除所有的点数据
		*/
		void clear(void)
		{
			mPoints.clear();
			mTangents.clear();
		}
		/**
		*   更新点数据
		*/
		void updatePoint(size_t index, const tvec3<T>& value)
		{
			assert(index < mPoints.size() && "Point index is out of bounds!!");

			mPoints[index] = value;
			if (mAutoCalc)
			{
				recalcTangents();
			}
		}
		/**
		*   差值获取点数据
		*/
		tvec3<T>    interpolate(T time) const
		{
			T           fSeg = time * (mPoints.size() - 1);
			unsigned    segIdx = (unsigned)fSeg;
			// Apportion t 
			time = fSeg - segIdx;

			return interpolate(segIdx, time);
		}
		/**
		*   根据索引差值
		*/
		tvec3<T>    interpolate(size_t fromIndex, T t) const
		{
			// Bounds check
			assert(fromIndex < mPoints.size() && "fromIndex out of bounds");

			if ((fromIndex + 1) == mPoints.size())
			{
				// Duff request, cannot blend to nothing
				// Just return source
				return mPoints[fromIndex];
			}
			// Fast special cases
			if (t == 0.0f)
			{
				return mPoints[fromIndex];
			}
			else if (t == 1.0f)
			{
				return mPoints[fromIndex + 1];
			}

			// float interpolation
			// Form a vector of powers of t
			T   t2, t3;
			t2 = t * t;
			t3 = t2 * t;
			tvec4<T>    powers(t3, t2, t, 1);

			const tvec3<T>& point1 = mPoints[fromIndex];
			const tvec3<T>& point2 = mPoints[fromIndex + 1];
			const tvec3<T>& tan1 = mTangents[fromIndex];
			const tvec3<T>& tan2 = mTangents[fromIndex + 1];
			tmat4x4<T> pt;

			pt[0][0] = point1.x;
			pt[0][1] = point1.y;
			pt[0][2] = point1.z;
			pt[0][3] = 1.0f;
			pt[1][0] = point2.x;
			pt[1][1] = point2.y;
			pt[1][2] = point2.z;
			pt[1][3] = 1.0f;
			pt[2][0] = tan1.x;
			pt[2][1] = tan1.y;
			pt[2][2] = tan1.z;
			pt[2][3] = 1.0f;
			pt[3][0] = tan2.x;
			pt[3][1] = tan2.y;
			pt[3][2] = tan2.z;
			pt[3][3] = 1.0f;

			pt = pt.transpose();

			tvec4<T> ret = powers * mCoeffs * pt;

			return tvec3<T>(ret.x, ret.y, ret.z);
		}
		/**
		*   自动计算标记
		*/
		void    setAutoCalculate(bool autoCalc)
		{
			mAutoCalc = autoCalc;
		}
		/**
		*   计算切线
		*/
		void    recalcTangents(void)
		{
			size_t i, numPoints;
			bool isClosed;

			numPoints = mPoints.size();
			if (numPoints < 2)
			{
				return;
			}
			if (mPoints[0] == mPoints[numPoints - 1])
			{
				isClosed = true;
			}
			else
			{
				isClosed = false;
			}

			mTangents.resize(numPoints);


			for (i = 0; i < numPoints; ++i)
			{
				if (i == 0)
				{
					// Special case start
					if (isClosed)
					{
						// Use numPoints-2 since numPoints-1 is the last point and == [0]
						mTangents[i] = 0.5f * (mPoints[1] - mPoints[numPoints - 2]);
					}
					else
					{
						mTangents[i] = 0.5f * (mPoints[1] - mPoints[0]);
					}
				}
				else if (i == numPoints - 1)
				{
					if (isClosed)
					{
						mTangents[i] = mTangents[0];
					}
					else
					{
						mTangents[i] = 0.5f * (mPoints[i] - mPoints[i - 1]);
					}
				}
				else
				{
					mTangents[i] = 0.5f * (mPoints[i + 1] - mPoints[i - 1]);
				}
			}
		}

	public:
		bool                    mAutoCalc;
		std::vector< tvec3<T> > mPoints;
		std::vector< tvec3<T> > mTangents;
		tmat4x4<T>              mCoeffs;
	};

	template<typename T>
	class   AxisAlignedBox2D
	{
	public:
		tvec2<T>    _minimum;
		tvec2<T>    _maximum;
	public:
		AxisAlignedBox2D()
		{
			_minimum = tvec2<T>(T(-0.5), T(-0.5));
			_maximum = tvec2<T>(T(0.5), T(0.5));
		}
		AxisAlignedBox2D(const AxisAlignedBox2D & rkBox)
		{
			setExtents(rkBox._minimum, rkBox._maximum);
		}

		AxisAlignedBox2D(const tvec2<T>& min, const tvec2<T>& max)
		{
			setExtents(min, max);
		}

		AxisAlignedBox2D(
			T mx, T my,
			T Mx, T My
		)
		{
			setExtents(tvec2<T>(mx, my), tvec2<T>(Mx, My));
		}

		AxisAlignedBox2D<T>& operator=(const AxisAlignedBox2D<T>& right)
		{
			setExtents(right._minimum, right._maximum);
			return *this;
		}

		~AxisAlignedBox2D()
		{
		}
		/**
		*   Gets the minimum corner of the box.
		*/
		const tvec2<T>& getMinimum(void) const
		{
			return _minimum;
		}

		/**
		*   Gets a modifiable version of the minimum
		*   corner of the box.
		*/
		tvec2<T>& getMinimum(void)
		{
			return _minimum;
		}

		void setMinimum(const tvec2<T>& vec)
		{
			_minimum = vec;
		}
		void setMinimum(T x, T y)
		{
			_minimum = tvec2<T>(x, y);
		}

		void    offset(T x, T y)
		{
			_minimum.x += x;
			_minimum.y += y;

			_maximum.x += x;
			_maximum.y += y;
		}
		void    offset(const tvec2<T>& of)
		{
			_minimum += of;
			_maximum += of;
		}
		/**
		*   Gets the maximum corner of the box.
		*/
		const tvec2<T>& getMaximum(void) const
		{
			return _maximum;
		}
		/**
		*   Gets a modifiable version of the maximum
		*   corner of the box.
		*/
		tvec2<T>& getMaximum(void)
		{
			return _maximum;
		}


		/**
		*   Sets the maximum corner of the box.
		*/
		void setMaximum(const tvec2<T>& vec)
		{
			_maximum = vec;
		}

		void setMaximum(T x, T y)
		{
			_maximum.x = x;
			_maximum.y = y;
		}

		/**
		*   Sets both minimum and maximum extents at once.
		*/
		void setExtents(const tvec2<T>& min, const tvec2<T>& max)
		{
			_minimum = min;
			_maximum = max;
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
		inline  bool intersects(const AxisAlignedBox2D& b2) const
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


		inline  AxisAlignedBox2D<T> intersection(const AxisAlignedBox2D<T>& b2) const
		{
			tvec2<T> intMin = _minimum;
			tvec2<T> intMax = _maximum;

			intMin.makeCeil(b2.getMinimum());
			intMax.makeFloor(b2.getMaximum());

			if (intMin.x < intMax.x &&
				intMin.y < intMax.y)
			{
				return AxisAlignedBox2D<T>(intMin, intMax);
			}

			return AxisAlignedBox2D<T>(0, 0, 0, 0);
		}

		inline  bool    intersects(const tvec2<T>& v) const
		{
			return(v.x >= _minimum.x  &&  v.x <= _maximum.x  &&
				v.y >= _minimum.y  &&  v.y <= _maximum.y);
		}


		inline  tvec2<T>    getCenter(void) const
		{
			return tvec2<T>(
				(_maximum.x + _minimum.x) * T(0.5f),
				(_maximum.y + _minimum.y) * T(0.5f)
				);
		}
		/**
		*   Gets the size of the box
		*/
		inline  tvec2<T> getSize(void) const
		{
			return _maximum - _minimum;
		}
		inline  bool    isNull()
		{
			return  _maximum.x == _minimum.x && _maximum.y == _minimum.y;
		}

		inline  tvec2<T> getHalfSize(void) const
		{
			return (_maximum - _minimum) * T(0.5);
		}

		inline  bool contains(const tvec2<T>& v) const
		{
			return _minimum.x <= v.x && v.x <= _maximum.x &&
				_minimum.y <= v.y && v.y <= _maximum.y;
		}

		inline  bool contains(const AxisAlignedBox2D& other) const
		{
			return this->_minimum.x <= other._minimum.x &&
				this->_minimum.y <= other._minimum.y &&
				other._maximum.x <= this->_maximum.x &&
				other._maximum.y <= this->_maximum.y;
		}
		inline  bool operator== (const AxisAlignedBox2D& right) const
		{
			return this->_minimum == right._minimum &&
				this->_maximum == right._maximum;
		}
		inline  bool operator!= (const AxisAlignedBox2D& right) const
		{
			return !(*this == right);
		}

		inline  void    inflate(const tvec2<T>& sz)
		{
			_minimum -= sz;
			_maximum += sz;
		}
		inline  void    inflate(T x, T y)
		{
			_minimum.x -= x;
			_minimum.y -= y;

			_maximum.x += x;
			_maximum.y += y;
		}

		inline  void    merge(tvec2<T> point)
		{
			if (_minimum.x > point.x)
			{
				_minimum.x = point.x;
			}

			if (_minimum.y > point.y)
			{
				_minimum.y = point.y;
			}
			if (_maximum.x < point.x)
			{
				_maximum.x = point.x;
			}
			if (_maximum.y < point.y)
			{
				_maximum.y = point.y;
			}
		}

		inline  void    merge(AxisAlignedBox2D<T> other)
		{
			_maximum.makeCeil(other._maximum);
			_minimum.makeFloor(other._minimum);
		}

	};

	inline  float   randRange(float fMin, float fMax)
	{
		return  float(rand()) / float(RAND_MAX) * (fMax - fMin) + fMin;
	}

	union LargeInt
	{
		struct  __LARGE_INT
		{
			unsigned    int LowPart;
			unsigned    int HighPart;
		}_largeInt;
		int64       int64Data;
	};
	/**
	*   产生64位数字
	*/
	inline  int64   makeInt64(unsigned low, unsigned hi)
	{
		LargeInt    intdata;
		intdata._largeInt.HighPart = low;
		intdata._largeInt.LowPart = hi;
		return  intdata.int64Data;
	}

	inline  uint    makeUint(short a, short b)
	{
		return  ((uint)(((ushort)(((uint)(a)) & 0xffff)) | ((uint)((ushort)(((uint)(b)) & 0xffff))) << 16));

	}
	inline  ushort   loWord(uint data)
	{
		return  ((ushort)(((uint)(data)) & 0xffff));
	}

	inline  ushort   hiWord(uint data)
	{
		return  ((ushort)((((uint)(data)) >> 16) & 0xffff));
	}

	inline  bool isNan(float dat)
	{
		int & ref = *(int *)&dat;
		return (ref & 0x7F800000) == 0x7F800000 && (ref & 0x7FFFFF) != 0;
	}
	inline bool isNan(double dat)
	{
		__int64 & ref = *(__int64 *)&dat;
		return (ref & 0x7FF0000000000000) == 0x7FF0000000000000 && (ref & 0xfffffffffffff) != 0;
	}

	/**
	*   两个向量的夹角
	*   定义两个向量 A,B
	*   A·B = |A|*|B|*cos(@)
	*   cos(@) = A·B/|A|*|B|
	*   @ = acos(@)
	*/
	template <typename T>
	T   angleBetweenVector(const tvec3<T>& a, const tvec3<T>& b)
	{
#define Mag(V) (sqrtf(V.x*V.x + V.y*V.y + V.z*V.z))
		T   dotProduct = dot(a, b);
		T   vectorsMagnitude = Mag(a) * Mag(b);
		T   angle = acos(dotProduct / vectorsMagnitude);
		T   result = angle * T(RAD2DEG);
		if (_isnan(result))
		{
			return	T(0);
		}
		else
		{
			return	result;
		}
	}

	template <typename T>
	T   angleBetweenVector(const tvec2<T>& a, const tvec2<T>& b)
	{
#define Mag2D(V)    (sqrtf(V.x*V.x + V.y*V.y))

		T   dotProduct = dot(a, b);
		T   vectorsMagnitude = Mag2D(a) * Mag2D(b);
		T   angle = acos(dotProduct / vectorsMagnitude);
		T   result = angle * T(RAD2DEG);
		if (_isnan(result))
		{
			return	T(0);
		}
		else
		{
			return	result;
		}
	}

	/**
	*   计算三角形面积
	*/
	template<typename T> T calcTriangleArea(const tvec3<T>& pt1, const tvec3<T>& pt2, const tvec3<T>& pt3)
	{
		tvec3<T> e1 = pt2 - pt1;
		tvec3<T> e2 = pt3 - pt1;
		tvec3<T> e3 = cross(e1, e2);
		return  length(e3) * T(0.5);
	}

	template<typename T>
	class   trect
	{
	public:
		trect(T left = 0, T top = 0, T right = 0, T bottom = 0)
		{
			_left = left;
			_top = top;
			_right = right;
			_bottom = bottom;
		}
		void    fromCenter(T x, T y, T size)
		{
			_left = x - size * T(0.5f);
			_top = y - size * T(0.5f);
			_right = x + size * T(0.5f);
			_bottom = y + size * T(0.5f);
		}

		void    fromCenter(T x, T y, T sizeX, T sizeY)
		{
			_left = x - sizeX * T(0.5f);
			_top = y - sizeY * T(0.5f);
			_right = x + sizeX * T(0.5f);
			_bottom = y + sizeY * T(0.5f);
		}

		bool    ptInRect(T x, T y)
		{
			return  x >= _left && x <= _right && y >= _top && y <= _bottom;
		}
	public:
		T    _left;
		T    _top;
		T    _right;
		T    _bottom;
	};

	template <typename T>
	struct tmat2x2
	{
		typedef T               value_type;
		typedef std::size_t     size_type;
		typedef tvec2<T>      col_type;
		typedef tvec2<T>      row_type;
		typedef tmat2x2<T>    type;
		typedef tmat2x2<T>    transpose_type;


	public:
		tmat2x2<T> _inverse() const
		{
			value_type Determinant = this->value[0][0] * this->value[1][1] - this->value[1][0] * this->value[0][1];

			tmat2x2<T> Inverse(
				+this->value[1][1] / Determinant,
				-this->value[0][1] / Determinant,
				-this->value[1][0] / Determinant,
				+this->value[0][0] / Determinant);
			return Inverse;
		}

	private:
		col_type value[2];

	public:

		size_type length() const
		{
			return 2;
		}

		static  size_type col_size()
		{
			return 2;
		}

		static  size_type row_size()
		{
			return 2;
		}

		col_type &operator[](size_type i)
		{
			assert(i < this->length());
			return this->value[i];
		}
		col_type const &operator[](size_type i) const
		{
			assert(i < this->length());
			return this->value[i];
		}

		tmat2x2()
		{
			this->value[0] = col_type(1, 0);
			this->value[1] = col_type(0, 1);
		}

		tmat2x2(tmat2x2<T> const & m)
		{
			this->value[0] = m.value[0];
			this->value[1] = m.value[1];
		}
		tmat2x2(value_type s)
		{
			value_type const Zero(0);
			this->value[0] = col_type(s, Zero);
			this->value[1] = col_type(Zero, s);
		}

		tmat2x2(value_type x0, value_type y0, value_type x1, value_type y1)
		{
			this->value[0] = col_type(x0, y0);
			this->value[1] = col_type(x1, y1);
		}

		tmat2x2(col_type const & v0, col_type const & v1)
		{
			this->value[0] = v0;
			this->value[1] = v1;
		}

		template <typename U>
		tmat2x2(U s)
		{
			value_type const Zero(0);
			this->value[0] = tvec2<T>(value_type(s), Zero);
			this->value[1] = tvec2<T>(Zero, value_type(s));
		}

		template <typename X1, typename Y1, typename X2, typename Y2>
		tmat2x2(X1 x1, Y1 y1, X2 x2, Y2 y2)
		{
			this->value[0] = col_type(value_type(x1), value_type(y1));
			this->value[1] = col_type(value_type(x2), value_type(y2));
		}
		template <typename V1, typename V2>
		tmat2x2
		(
			tvec2<V1> const & v1,
			tvec2<V2> const & v2
		)
		{
			this->value[0] = col_type(v1);
			this->value[1] = col_type(v2);
		}

		T*  dataPtr()
		{
			return  (T*)value;
		}
		template <typename U>
		tmat2x2(tmat2x2<U> const & m)
		{
			this->value[0] = col_type(m[0]);
			this->value[1] = col_type(m[1]);
		}
		tmat2x2<T>& operator=(tmat2x2<T> const & m)
		{
			this->value[0] = m[0];
			this->value[1] = m[1];
			return *this;
		}

		template <typename U>
		tmat2x2<T>& operator=
			(
				tmat2x2<U> const & m
				)
		{
			this->value[0] = m[0];
			this->value[1] = m[1];
			return *this;
		}

		template <typename U>
		tmat2x2<T>& operator+=(U const & s)
		{
			this->value[0] += s;
			this->value[1] += s;
			return *this;
		}

		template <typename U>
		tmat2x2<T>& operator+=
			(
				tmat2x2<U> const & m
				)
		{
			this->value[0] += m[0];
			this->value[1] += m[1];
			return *this;
		}

		template <typename U>
		tmat2x2<T>& operator-=(U const & s)
		{
			this->value[0] -= s;
			this->value[1] -= s;
			return *this;
		}

		template <typename U>
		tmat2x2<T>& operator-=(tmat2x2<U> const & m)
		{
			this->value[0] -= m[0];
			this->value[1] -= m[1];
			return *this;
		}

		template <typename U>
		tmat2x2<T>& operator*= (U const & s)
		{
			this->value[0] *= s;
			this->value[1] *= s;
			return *this;
		}

		template <typename U>
		tmat2x2<T>& operator*= (tmat2x2<U> const & m)
		{
			return (*this = *this * m);
		}

		template <typename U>
		tmat2x2<T>& operator/= (U const & s)
		{
			this->value[0] /= s;
			this->value[1] /= s;
			return *this;
		}

		template <typename U>
		tmat2x2<T>& operator/= (tmat2x2<U> const & m)
		{
			return (*this = *this / m);
		}

		tmat2x2<T>& operator++ ()
		{
			++this->value[0];
			++this->value[1];
			return *this;
		}

		tmat2x2<T>& operator-- ()
		{
			--this->value[0];
			--this->value[1];
			return *this;
		};
	};

	template <typename T>
	tmat2x2<T> rotate(T angle)
	{
		T c = cos(DEG2RAD(angle));
		T s = sin(DEG2RAD(angle));
		return  tmat2x2<T>(c, s, -s, c);
	}

	template <typename T>
	tmat2x2<T> operator+ (tmat2x2<T> const & m, T const & s)
	{
		return tmat2x2<T>(m[0] + s, m[1] + s);
	}

	template <typename T>
	tmat2x2<T> operator+ (T const & s, tmat2x2<T> const & m)
	{
		return tmat2x2<T>(m[0] + s, m[1] + s);
	}

	template <typename T>
	tmat2x2<T> operator+ (tmat2x2<T> const & m1, tmat2x2<T> const & m2)
	{
		return tmat2x2<T>(m1[0] + m2[0], m1[1] + m2[1]);
	}

	template <typename T>
	tmat2x2<T> operator- (tmat2x2<T> const & m, T const & s)
	{
		return tmat2x2<T>(m[0] - s, m[1] - s);
	}

	template <typename T>
	tmat2x2<T> operator- (T const & s, tmat2x2<T> const & m)
	{
		return tmat2x2<T>(s - m[0], s - m[1]);
	}

	template <typename T>
	tmat2x2<T> operator- (tmat2x2<T> const & m1, tmat2x2<T> const & m2)
	{
		return tmat2x2<T>(m1[0] - m2[0], m1[1] - m2[1]);
	}

	template <typename T>
	tmat2x2<T> operator* (tmat2x2<T> const & m, T  const & s)
	{
		return tmat2x2<T>(m[0] * s, m[1] * s);
	}

	template <typename T>
	tmat2x2<T> operator* (T const & s, tmat2x2<T> const & m)
	{
		return tmat2x2<T>(m[0] * s, m[1] * s);
	}

	template <typename T>
	tvec2<T> operator*(tmat2x2<T> const & m, tvec2<T> const & v)
	{
		return tvec2<T>(
			m[0][0] * v.x + m[1][0] * v.y,
			m[0][1] * v.x + m[1][1] * v.y);
	}

	template <typename T>
	tvec2<T> operator*(tvec2<T> const & v, tmat2x2<T> const & m)
	{
		return  tvec2<T>(
			v.x * m[0][0] + v.y * m[0][1],
			v.x * m[1][0] + v.y * m[1][1]);
	}

	template <typename T>
	tmat2x2<T> operator*(tmat2x2<T> const & m1, tmat2x2<T> const & m2)
	{
		return tmat2x2<T>(
			m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1],
			m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1],
			m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1],
			m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1]);
	}



	template <typename T>
	tmat4x4<T> rotateX(T angleX)
	{
		T cosX = cos(DEG2RAD(angleX));
		T sinX = sin(DEG2RAD(angleX));

		return tmat4x4<T>(
			T(1), T(0), T(0), T(0),
			T(0), cosX, sinX, T(0),
			T(0), -sinX, cosX, T(0),
			T(0), T(0), T(0), T(1));
	}

	template <typename T>
	tmat4x4<T> rotateY(T angleY)
	{
		T cosY = cos(DEG2RAD(angleY));
		T sinY = sin(DEG2RAD(angleY));

		return tmat4x4<T>(
			cosY, T(0), sinY, T(0),
			T(0), T(1), T(0), T(0),
			-sinY, T(0), cosY, T(0),
			T(0), T(0), T(0), T(1));
	}

	template <typename T>
	tmat4x4<T> rotateZ(T angleZ)
	{
		T cosZ = cos(DEG2RAD(angleZ));
		T sinZ = sin(DEG2RAD(angleZ));

		return  tmat4x4<T>(
			cosZ, sinZ, T(0), T(0),
			-sinZ, cosZ, T(0), T(0),
			T(0), T(0), T(1), T(0),
			T(0), T(0), T(0), T(1));
	}

	template <typename T>
	tmat4x4<T> rotateXY(T angleX, T angleY)
	{
		T cosX = cos(DEG2RAD(angleX));
		T sinX = sin(DEG2RAD(angleX));
		T cosY = cos(DEG2RAD(angleY));
		T sinY = sin(DEG2RAD(angleY));

		return  tmat4x4<T>(
			cosY, -sinX * sinY, cosX * sinY, T(0),
			T(0), cosX, sinX, T(0),
			-sinY, -sinX * cosY, cosX * cosY, T(0),
			T(0), T(0), T(0), T(1));
	}

	template <typename T>
	tmat4x4<T> rotateYX(T angleY, T angleX)
	{

		T cosX = cos(DEG2RAD(angleX));
		T sinX = sin(DEG2RAD(angleX));
		T cosY = cos(DEG2RAD(angleY));
		T sinY = sin(DEG2RAD(angleY));

		return  tmat4x4<T>(
			cosY, T(0), sinY, T(0),
			-sinX * sinY, cosX, sinX * cosY, T(0),
			-cosX * sinY, -sinX, cosX * cosY, T(0),
			T(0), T(0), T(0), T(1));
	}

	template <typename T>
	tmat4x4<T> rotateXZ(T angleX, T angleZ)
	{
		return rotateX(angleX) * rotateZ(angleZ);
	}

	template <typename T>
	tmat4x4<T> rotateZX(T angleX, T angleZ)
	{
		return rotateZ(angleZ) * rotateX(angleX);
	}

	template <typename T>
	tmat4x4<T> rotateYXZ(T yaw, T pitch, T roll)
	{
		T tmp_ch = cos(DEG2RAD(yaw));
		T tmp_sh = sin(DEG2RAD(yaw));
		T tmp_cp = cos(DEG2RAD(pitch));
		T tmp_sp = sin(DEG2RAD(pitch));
		T tmp_cb = cos(DEG2RAD(roll));
		T tmp_sb = sin(DEG2RAD(roll));

		tmat4x4<T> res;
		res[0][0] = tmp_ch * tmp_cb + tmp_sh * tmp_sp * tmp_sb;
		res[0][1] = tmp_sb * tmp_cp;
		res[0][2] = -tmp_sh * tmp_cb + tmp_ch * tmp_sp * tmp_sb;
		res[0][3] = T(0);
		res[1][0] = -tmp_ch * tmp_sb + tmp_sh * tmp_sp * tmp_cb;
		res[1][1] = tmp_cb * tmp_cp;
		res[1][2] = tmp_sb * tmp_sh + tmp_ch * tmp_sp * tmp_cb;
		res[1][3] = T(0);
		res[2][0] = tmp_sh * tmp_cp;
		res[2][1] = -tmp_sp;
		res[2][2] = tmp_ch * tmp_cp;
		res[2][3] = T(0);
		res[3][0] = T(0);
		res[3][1] = T(0);
		res[3][2] = T(0);
		res[3][3] = T(1);
		return res;
	}

	template <typename T>
	tmat4x4<T> yawPitchRoll(T yaw, T pitch, T roll)
	{
		T tmp_ch = cos(DEG2RAD(yaw));
		T tmp_sh = sin(DEG2RAD(yaw));
		T tmp_cp = cos(DEG2RAD(pitch));
		T tmp_sp = sin(DEG2RAD(pitch));
		T tmp_cb = cos(DEG2RAD(roll));
		T tmp_sb = sin(DEG2RAD(roll));


		tmat4x4<T> res;
		res[0][0] = tmp_ch * tmp_cb + tmp_sh * tmp_sp * tmp_sb;
		res[0][1] = tmp_sb * tmp_cp;
		res[0][2] = -tmp_sh * tmp_cb + tmp_ch * tmp_sp * tmp_sb;
		res[0][3] = T(0);
		res[1][0] = -tmp_ch * tmp_sb + tmp_sh * tmp_sp * tmp_cb;
		res[1][1] = tmp_cb * tmp_cp;
		res[1][2] = tmp_sb * tmp_sh + tmp_ch * tmp_sp * tmp_cb;
		res[1][3] = T(0);
		res[2][0] = tmp_sh * tmp_cp;
		res[2][1] = -tmp_sp;
		res[2][2] = tmp_ch * tmp_cp;
		res[2][3] = T(0);
		res[3][0] = T(0);
		res[3][1] = T(0);
		res[3][2] = T(0);
		res[3][3] = T(1);
		return res;
	}

	template <typename T>
	void axisAngle
	(
		tmat4x4<T> const & mat,
		tvec3<T> & axis,
		T & angle
	)
	{
		T epsilon = (T)0.01;
		T epsilon2 = (T)0.1;

		if ((fabs(mat[1][0] - mat[0][1]) < epsilon) &&
			(fabs(mat[2][0] - mat[0][2]) < epsilon) &&
			(fabs(mat[2][1] - mat[1][2]) < epsilon))
		{
			if ((fabs(mat[1][0] + mat[0][1]) < epsilon2) &&
				(fabs(mat[2][0] + mat[0][2]) < epsilon2) &&
				(fabs(mat[2][1] + mat[1][2]) < epsilon2) &&
				(fabs(mat[0][0] + mat[1][1] + mat[2][2] - (T)3.0) < epsilon2))
			{
				angle = (T)0.0;
				axis.x = (T)1.0;
				axis.y = (T)0.0;
				axis.z = (T)0.0;
				return;
			}
			angle = T(PI);
			T xx = (mat[0][0] + (T)1.0) / (T)2.0;
			T yy = (mat[1][1] + (T)1.0) / (T)2.0;
			T zz = (mat[2][2] + (T)1.0) / (T)2.0;
			T xy = (mat[1][0] + mat[0][1]) / (T)4.0;
			T xz = (mat[2][0] + mat[0][2]) / (T)4.0;
			T yz = (mat[2][1] + mat[1][2]) / (T)4.0;
			if ((xx > yy) && (xx > zz))
			{
				if (xx < epsilon)
				{
					axis.x = (T)0.0;
					axis.y = (T)0.7071;
					axis.z = (T)0.7071;
				}
				else
				{
					axis.x = sqrt(xx);
					axis.y = xy / axis.x;
					axis.z = xz / axis.x;
				}
			}
			else if (yy > zz)
			{
				if (yy < epsilon)
				{
					axis.x = (T)0.7071;
					axis.y = (T)0.0;
					axis.z = (T)0.7071;
				}
				else
				{
					axis.y = sqrt(yy);
					axis.x = xy / axis.y;
					axis.z = yz / axis.y;
				}
			}
			else
			{
				if (zz < epsilon)
				{
					axis.x = (T)0.7071;
					axis.y = (T)0.7071;
					axis.z = (T)0.0;
				}
				else
				{
					axis.z = sqrt(zz);
					axis.x = xz / axis.z;
					axis.y = yz / axis.z;
				}
			}
			return;
		}
		T s = sqrt((mat[2][1] - mat[1][2]) * (mat[2][1] - mat[1][2]) + (mat[2][0] - mat[0][2]) * (mat[2][0] - mat[0][2]) + (mat[1][0] - mat[0][1]) * (mat[1][0] - mat[0][1]));
		if (abs(s) < T(0.001))
			s = (T)1.0;
		angle = acos((mat[0][0] + mat[1][1] + mat[2][2] - (T)1.0) / (T)2.0);
		axis.x = (mat[1][2] - mat[2][1]) / s;
		axis.y = (mat[2][0] - mat[0][2]) / s;
		axis.z = (mat[0][1] - mat[1][0]) / s;
	}

	template <typename T>
	tmat4x4<T> axisAngleMatrix(tvec3<T> const & axis, T const angle)
	{
		T c = cos(angle);
		T s = sin(angle);
		T t = T(1) - c;
		tvec3<T> n = normalize(axis);

		return tmat4x4<T>(
			t * n.x * n.x + c, t * n.x * n.y + n.z * s, t * n.x * n.z - n.y * s, T(0),
			t * n.x * n.y - n.z * s, t * n.y * n.y + c, t * n.y * n.z + n.x * s, T(0),
			t * n.x * n.z + n.y * s, t * n.y * n.z - n.x * s, t * n.z * n.z + c, T(0),
			T(0), T(0), T(0), T(1)
			);
	}

	template <typename T>
	tmat4x4<T> interpolate
	(
		tmat4x4<T> const & m1,
		tmat4x4<T> const & m2,
		T const delta
	)
	{
		tmat4x4<T> m1rot = m1.extractMatrixRotation();
		tmat4x4<T> dltRotation = m2 * m1rot.transpose();
		tvec3<T> dltAxis;
		T dltAngle;
		axisAngle(dltRotation, dltAxis, dltAngle);
		tmat4x4<T> out = axisAngleMatrix(dltAxis, dltAngle * delta) * m1rot;
		out[3][0] = m1[3][0] + delta * (m2[3][0] - m1[3][0]);
		out[3][1] = m1[3][1] + delta * (m2[3][1] - m1[3][1]);
		out[3][2] = m1[3][2] + delta * (m2[3][2] - m1[3][2]);
		return out;
	}


	template <typename T>
	struct tquat
	{
		typedef T value_type;
		typedef std::size_t size_type;

	public:
		value_type  x;
		value_type  y;
		value_type  z;
		value_type  w;

		size_type length() const
		{
			return	4;
		}

		tquat() :
			x(0),
			y(0),
			z(0),
			w(1)
		{}
		explicit tquat(value_type s, tvec3<T> const & v) :
			x(v.x),
			y(v.y),
			z(v.z),
			w(s)
		{
		}
		explicit tquat(tvec3<T> const & v, value_type s) :
			x(v.x),
			y(v.y),
			z(v.z),
			w(s)
		{
		}
		explicit tquat(value_type w, value_type x, value_type y, value_type z) :
			x(x),
			y(y),
			z(z),
			w(w)
		{}

		explicit tquat(const T& eulerAngle)
		{
			tvec3<T> c = cos(eulerAngle * value_type(0.5));
			tvec3<T> s = sin(eulerAngle * value_type(0.5));

			this->w = c.x * c.y * c.z + s.x * s.y * s.z;
			this->x = s.x * c.y * c.z - c.x * s.y * s.z;
			this->y = c.x * s.y * c.z + s.x * c.y * s.z;
			this->z = c.x * c.y * s.z - s.x * s.y * c.z;
		}

		explicit tquat(tmat3x3<T> const & m)
		{
			*this = quat_cast(m);
		}

		explicit tquat(tmat4x4<T> const & m)
		{
			*this = quat_cast(m);
		}

		value_type & operator[](int i)
		{
			return (&x)[i];
		}

		value_type const & operator[](int i) const
		{
			return (&x)[i];
		}

		tquat<T> & operator*=(value_type s)
		{
			this->w *= s;
			this->x *= s;
			this->y *= s;
			this->z *= s;
			return *this;
		}

		tquat<T> & operator = (const tquat<T>& right)
		{
			this->w = right.w;
			this->x = right.x;
			this->y = right.y;
			this->z = right.z;
			return *this;
		}

		tquat<T> & operator/=(value_type s)
		{
			this->w /= s;
			this->x /= s;
			this->y /= s;
			this->z /= s;
			return *this;
		}
	};


	template< typename T>
	tmat4x4<T>  makeTransform(tvec3<T> const & position, tvec3<T> const& scale, const tquat<T>& orientation)
	{
		tmat3x3<T> rot3x3 = mat3_cast(orientation);

		return  tmat4x4<T>
			(
				scale.x * rot3x3[0][0], scale.x * rot3x3[0][1], scale.x * rot3x3[0][2], 0,
				scale.y * rot3x3[1][0], scale.y * rot3x3[1][1], scale.y * rot3x3[1][2], 0,
				scale.z * rot3x3[2][0], scale.z * rot3x3[2][1], scale.z * rot3x3[2][2], 0,
				position.x, position.y, position.z, 1
				);
	}

	template <typename T>
	T   dot(tquat<T> const & q1, tquat<T> const & q2)
	{
		return q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w;
	}

	template <typename T>
	T   length(tquat<T> const & q)
	{
		return sqrt(dot(q, q));
	}

	template <typename genType>
	genType mix(genType x, genType y, genType a)
	{
		return x + a * (y - x);
	}


	template <typename T>
	tmat4x4<T>    pickMatrix
	(
		tvec2<T> const & center,
		tvec2<T> const & delta,
		tvec4<T> const & viewport
	)
	{
		assert(delta.x > T(0) && delta.y > T(0));
		tmat4x4<T> res(1.0f);

		if (!(delta.x > T(0) && delta.y > T(0)))
		{
			return res;
		}

		tvec3<T>  Temp
		(
			(T(viewport[2]) - T(2) * (center.x - T(viewport[0]))) / delta.x,
			(T(viewport[3]) - T(2) * (center.y - T(viewport[1]))) / delta.y,
			T(0)
		);
		res = translate(res, Temp);
		return  scale(res, tvec3<T>(T(viewport[2]) / delta.x, T(viewport[3]) / delta.y, T(1)));
	}
	template <typename T>
	tvec3<T>    unProject
	(
		tvec3<T> const & win,
		tmat4x4<T> const & model,
		tmat4x4<T> const & proj,
		tvec4<T> const & viewport
	)
	{
		tmat4x4<T> inverses = (proj * model).inverse();

		tvec4<T> tmp = tvec4<T>(win.x, win.y, win.z, T(1));
		tmp.x = (tmp.x - T(viewport[0])) / T(viewport[2]);
		tmp.y = (tmp.y - T(viewport[1])) / T(viewport[3]);
		tmp = tmp * T(2) - T(1);

		tvec4<T> obj = inverses * tmp;
		obj /= obj.w;

		return tvec3<T>(obj.x, obj.y, obj.z);
	}

	template <typename T>
	tvec3<T>    project
	(
		tvec3<T> const & obj,
		tmat4x4<T> const & model,
		tmat4x4<T> const & proj,
		tvec4<T> const & viewport
	)
	{
		tvec4<T> tmp = tvec4<T>(obj.x, obj.y, obj.z, T(1));
		tmp = model * tmp;
		tmp = proj * tmp;

		tmp /= tmp.w;
		tmp = tmp * T(0.5) + T(0.5);
		tmp[0] = tmp[0] * T(viewport[2]) + T(viewport[0]);
		tmp[1] = tmp[1] * T(viewport[3]) + T(viewport[1]);

		return tvec3<T>(tmp.x, tmp.y, tmp.z);
	}


	template <typename valType>
	tmat4x4<valType>    frustum
	(
		valType left,
		valType right,
		valType bottom,
		valType top,
		valType nearVal,
		valType farVal
	)
	{
		tmat4x4<valType> res(0);
		res[0][0] = (valType(2) * nearVal) / (right - left);
		res[1][1] = (valType(2) * nearVal) / (top - bottom);
		res[2][0] = (right + left) / (right - left);
		res[2][1] = (top + bottom) / (top - bottom);
		res[2][2] = -(farVal + nearVal) / (farVal - nearVal);
		res[2][3] = valType(-1);
		res[3][2] = -(valType(2) * farVal * nearVal) / (farVal - nearVal);
		return res;
	}

	template <typename T>
	tmat4x4<T> scale_slow(tmat4x4<T> const & m, tvec3<T> const & v)
	{
		tmat4x4<T> res(T(1));
		res[0][0] = v.x;
		res[1][1] = v.y;
		res[2][2] = v.z;

		return  m * res;
	}

	template <typename T>
	tmat4x4<T> rotate_slow
	(
		tmat4x4<T> const & m,
		T const & angle,
		tvec3<T> const & v
	)
	{

		T const a = DEG2RAD(angle);
		T c = cos(a);
		T s = sin(a);
		tmat4x4<T> res;

		tvec3<T> axis = normalize(v);

		res[0][0] = c + (1 - c)      * axis.x     * axis.x;
		res[0][1] = (1 - c) * axis.x * axis.y + s * axis.z;
		res[0][2] = (1 - c) * axis.x * axis.z - s * axis.y;
		res[0][3] = 0;

		res[1][0] = (1 - c) * axis.y * axis.x - s * axis.z;
		res[1][1] = c + (1 - c) * axis.y * axis.y;
		res[1][2] = (1 - c) * axis.y * axis.z + s * axis.x;
		res[1][3] = 0;

		res[2][0] = (1 - c) * axis.z * axis.x + s * axis.y;
		res[2][1] = (1 - c) * axis.z * axis.y - s * axis.x;
		res[2][2] = c + (1 - c) * axis.z * axis.z;
		res[2][3] = 0;

		res[3] = tvec4<T>(0, 0, 0, 1);
		return m * res;
	}
	template <typename T>
	tmat4x4<T> scale(tmat4x4<T> const & m, tvec3<T> const & v)
	{
		tmat4x4<T> res;
		res[0] = m[0] * v[0];
		res[1] = m[1] * v[1];
		res[2] = m[2] * v[2];
		res[3] = m[3];
		return  res;
	}

	template <typename T>
	tmat4x4<T>    rotate
	(
		tmat4x4<T> const & m,
		T const & angle,
		tvec3<T> const & v
	)
	{

		T a = DEG2RAD(angle);
		T c = cos(a);
		T s = sin(a);

		tvec3<T> axis = normalize(v);

		tvec3<T> temp = (T(1) - c) * axis;

		tmat4x4<T> res;
		res[0][0] = c + temp[0] * axis[0];
		res[0][1] = 0 + temp[0] * axis[1] + s * axis[2];
		res[0][2] = 0 + temp[0] * axis[2] - s * axis[1];

		res[1][0] = 0 + temp[1] * axis[0] - s * axis[2];
		res[1][1] = c + temp[1] * axis[1];
		res[1][2] = 0 + temp[1] * axis[2] + s * axis[0];

		res[2][0] = 0 + temp[2] * axis[0] + s * axis[1];
		res[2][1] = 0 + temp[2] * axis[1] - s * axis[0];
		res[2][2] = c + temp[2] * axis[2];

		tmat4x4<T> rot;

		rot[0] = m[0] * res[0][0] + m[1] * res[0][1] + m[2] * res[0][2];
		rot[1] = m[0] * res[1][0] + m[1] * res[1][1] + m[2] * res[1][2];
		rot[2] = m[0] * res[2][0] + m[1] * res[2][1] + m[2] * res[2][2];
		rot[3] = m[3];
		return rot;
	}

	template <typename valType>
	tquat<valType> angleAxis(valType angle, tvec3<valType> const & axis)
	{
		tquat<valType> result;

		valType a = (valType)(valType(DEG2RAD(angle)));
		valType s = sin(a * valType(0.5));

		result.w = cos(a * valType(0.5));
		result.x = axis.x * s;
		result.y = axis.y * s;
		result.z = axis.z * s;
		return result;
	}

	template <typename T>
	tvec3<T> axis(tquat<T> const & x)
	{
		T   tmp1 = T(1) - x.w * x.w;
		if (tmp1 <= T(0))
		{
			return tvec3<T>(0, 0, 1);
		}
		T   tmp2 = T(1) / sqrt(tmp1);

		return tvec3<T>(x.x * tmp2, x.y * tmp2, x.z * tmp2);
	}



	template <typename T>
	tmat4x4<T>  mat4_cast(tquat<T> const & q)
	{
		return tmat4x4<T>(mat3_cast(q));
	}
	template <typename T>
	tquat<T>    quat_cast(tmat3x3<T> const & m)
	{
		typename tquat<T>::value_type fourXSquaredMinus1 = m[0][0] - m[1][1] - m[2][2];
		typename tquat<T>::value_type fourYSquaredMinus1 = m[1][1] - m[0][0] - m[2][2];
		typename tquat<T>::value_type fourZSquaredMinus1 = m[2][2] - m[0][0] - m[1][1];
		typename tquat<T>::value_type fourWSquaredMinus1 = m[0][0] + m[1][1] + m[2][2];

		int biggestIndex = 0;
		typename tquat<T>::value_type fourBiggestSquaredMinus1 = fourWSquaredMinus1;
		if (fourXSquaredMinus1 > fourBiggestSquaredMinus1)
		{
			fourBiggestSquaredMinus1 = fourXSquaredMinus1;
			biggestIndex = 1;
		}
		if (fourYSquaredMinus1 > fourBiggestSquaredMinus1)
		{
			fourBiggestSquaredMinus1 = fourYSquaredMinus1;
			biggestIndex = 2;
		}
		if (fourZSquaredMinus1 > fourBiggestSquaredMinus1)
		{
			fourBiggestSquaredMinus1 = fourZSquaredMinus1;
			biggestIndex = 3;
		}

		typename tquat<T>::value_type biggestVal = sqrt(fourBiggestSquaredMinus1 + T(1)) * T(0.5);
		typename tquat<T>::value_type mult = T(0.25) / biggestVal;

		tquat<T> res;
		switch (biggestIndex)
		{
		case 0:
			res.w = biggestVal;
			res.x = (m[1][2] - m[2][1]) * mult;
			res.y = (m[2][0] - m[0][2]) * mult;
			res.z = (m[0][1] - m[1][0]) * mult;
			break;
		case 1:
			res.w = (m[1][2] - m[2][1]) * mult;
			res.x = biggestVal;
			res.y = (m[0][1] + m[1][0]) * mult;
			res.z = (m[2][0] + m[0][2]) * mult;
			break;
		case 2:
			res.w = (m[2][0] - m[0][2]) * mult;
			res.x = (m[0][1] + m[1][0]) * mult;
			res.y = biggestVal;
			res.z = (m[1][2] + m[2][1]) * mult;
			break;
		case 3:
			res.w = (m[0][1] - m[1][0]) * mult;
			res.x = (m[2][0] + m[0][2]) * mult;
			res.y = (m[1][2] + m[2][1]) * mult;
			res.z = biggestVal;
			break;

		default:
			assert(false);
			break;
		}
		return res;
	}
	template <typename T>
	tquat<T> quat_cast(tmat4x4<T> const & m4)
	{
		return quat_cast(tmat3x3<T>(m4[0][0], m4[0][1], m4[0][2],
			m4[1][0], m4[1][1], m4[1][2],
			m4[2][0], m4[2][1], m4[2][2]));
	}

	template <typename T>
	T angle(tquat<T> const & x)
	{
		return acos(x.w) * T(2) * T(RAD2DEG);
	}

	template <typename T>
	tvec3<T>    eulerAngles(tquat<T> const & x)
	{
		return tvec3<T>(pitch(x), yaw(x), roll(x));
	}


	template <typename T>
	tmat3x3<T>  mat3_cast(const tquat<T>& q)
	{

		return  tmat3x3<T>
			(
				1 - 2 * q.y * q.y - 2 * q.z * q.z, 2 * q.x * q.y + 2 * q.w * q.z, 2 * q.x * q.z - 2 * q.w * q.y,
				2 * q.x * q.y - 2 * q.w * q.z, 1 - 2 * q.x * q.x - 2 * q.z * q.z, 2 * q.y * q.z + 2 * q.w * q.x,
				2 * q.x * q.z + 2 * q.w * q.y, 2 * q.y * q.z - 2 * q.w * q.x, 1 - 2 * q.x * q.x - 2 * q.y * q.y
				);
	}
	template <typename T>
	tmat3x3<T>  mat3_cast(const tmat4x4<T>& m4)
	{

		return  tmat3x3<T>(
			m4[0][0], m4[0][1], m4[0][2],
			m4[1][0], m4[1][1], m4[1][2],
			m4[2][0], m4[2][1], m4[2][2]
			);
	}
	template <typename valType>
	valType     roll(tquat<valType> const & q)
	{
		return  atan2(valType(2) * (q.x * q.y + q.w * q.z), q.w * q.w + q.x * q.x - q.y * q.y - q.z * q.z) * valType(RAD2DEG);
	}

	template <typename valType>
	valType     pitch(tquat<valType> const & q)
	{
		return  ::atan2(valType(2) * (q.y * q.z + q.w * q.x), q.w * q.w - q.x * q.x - q.y * q.y + q.z * q.z)* valType(RAD2DEG);
	}
	template <typename valType>
	valType     yaw(tquat<valType> const & q)
	{
		return  ::asin(valType(-2) * (q.x * q.z - q.w * q.y)) * valType(RAD2DEG);
	}

	template <typename T>
	tquat<T>    mix(tquat<T> const & x, tquat<T> const & y, T const & a)
	{
		T cosTheta = dot(x, y);
		if (cosTheta > T(1) - epsilon<T>())
		{
			return tquat<T>(
				mix(x.w, y.w, a),
				mix(x.x, y.x, a),
				mix(x.y, y.y, a),
				mix(x.z, y.z, a)
				);
		}
		else
		{
			// Essential Mathematics, page 467
			T   angle = acos(cosTheta);
			return  (sin((T(1) - a) * angle) * x + sin(a * angle) * y) / sin(angle);
		}
	}

	template <typename T>
	tquat<T>    lerp(tquat<T> const & x, tquat<T> const & y, T a)
	{
		assert(a >= T(0));
		assert(a <= T(1));
		return x * (T(1) - a) + (y * a);
	}

	template <typename T>
	tquat<T>    slerp(tquat<T> const & x, tquat<T> const & y, T a)
	{
		tquat<T> z = y;

		T cosTheta = dot(x, y);

		if (cosTheta < T(0))
		{
			z = -y;
			cosTheta = -cosTheta;
		}
		if (cosTheta > T(1) - epsilon<T>())
		{
			return  tquat<T>
				(
					mix(x.w, z.w, a),
					mix(x.x, z.x, a),
					mix(x.y, z.y, a),
					mix(x.z, z.z, a)
					);
		}
		else
		{
			// Essential Mathematics, page 467
			T angle = acos(cosTheta);
			return (sin((T(1) - a) * angle) * x + sin(a * angle) * z) / sin(angle);
		}
	}

	template <typename T>
	tquat<T>    rotate
	(
		typename tquat<T>::value_type angle,
		tvec3<T> const & axis
	)
	{
		tvec3<T> Tmp = axis;

		typename tquat<T>::value_type len = length(Tmp);
		if (abs(len - T(1)) > T(0.001f))
		{
			T oneOverLen = T(1) / len;
			Tmp.x *= oneOverLen;
			Tmp.y *= oneOverLen;
			Tmp.z *= oneOverLen;
		}
		typename tquat<T>::value_type const AngleRad = (T)DEG2RAD(angle);
		typename tquat<T>::value_type const Sin = (T)sin(AngleRad * T(0.5));
		return tquat<T>((T)cos(AngleRad * T(0.5)), Tmp.x * Sin, Tmp.y * Sin, Tmp.z * Sin);
	}

	template <typename T>
	tquat<T> operator+ (tquat<T> const & q, tquat<T> const & p)
	{
		return tquat<T>(
			q.w + p.w,
			q.x + p.x,
			q.y + p.y,
			q.z + p.z
			);
	}

	template <typename T>
	tquat<T> operator* (tquat<T> const & q, tquat<T> const & p)
	{
		return tquat<T>(
			q.w * p.w - q.x * p.x - q.y * p.y - q.z * p.z,
			q.w * p.x + q.x * p.w + q.y * p.z - q.z * p.y,
			q.w * p.y + q.y * p.w + q.z * p.x - q.x * p.z,
			q.w * p.z + q.z * p.w + q.x * p.y - q.y * p.x
			);
	}

	template <typename T>
	tvec3<T> operator* (tquat<T> const & q, tvec3<T> const & v)
	{
		typename tquat<T>::value_type two(2);

		tvec3<T>    uv;
		tvec3<T>    uuv;
		tvec3<T>    quatVector(q.x, q.y, q.z);
		uv = cross(quatVector, v);
		uuv = cross(quatVector, uv);
		uv *= two * q.w;
		uuv *= two;
		return v + uv + uuv;
	}

	template <typename T>
	tvec3<T> operator* (tvec3<T> const & v, tquat<T> const & q)
	{
		return  inverse(q) * v;
	}


	template <typename T>
	tquat<T> operator* (tquat<T> const & q, typename tquat<T>::value_type s)
	{
		return tquat<T>(q.w * s, q.x * s, q.y * s, q.z * s);
	}

	template <typename T>
	tquat<T> operator* (typename tquat<T>::value_type s, tquat<T> const & q)
	{
		return q * s;
	}

	template <typename T>
	tquat<T> operator/ (tquat<T> const & q, typename tquat<T>::value_type s)
	{
		return tquat<T>(q.w / s, q.x / s, q.y / s, q.z / s);
	}


	template <typename T>
	tquat<T> cross(tquat<T> const & q1, tquat<T> const & q2)
	{
		return tquat<T>(
			q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z,
			q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y,
			q1.w * q2.y + q1.y * q2.w + q1.z * q2.x - q1.x * q2.z,
			q1.w * q2.z + q1.z * q2.w + q1.x * q2.y - q1.y * q2.x);
	}


	template <typename T>
	T epsilon()
	{
		return std::numeric_limits<T>::epsilon();
	}



	template <typename T>
	tquat<T>    conjugate(tquat<T> const & q)
	{
		return tquat<T>(q.w, -q.x, -q.y, -q.z);
	}

	template <typename T>
	tquat<T>    inverse(tquat<T> const & q)
	{
		return  conjugate(q) / dot(q, q);
	}

	template <typename T>
	bool operator==(tquat<T> const & q1, tquat<T> const & q2)
	{
		return (q1.x == q2.x) && (q1.y == q2.y) && (q1.z == q2.z) && (q1.w == q2.w);
	}

	template <typename T>
	bool operator!=(tquat<T> const & q1, tquat<T> const & q2)
	{
		return (q1.x != q2.x) || (q1.y != q2.y) || (q1.z != q2.z) || (q1.w != q2.w);
	}

	template <typename T>
	tquat<T> operator- (tquat<T> const & q)
	{
		return tquat<T>(-q.w, -q.x, -q.y, -q.z);
	}

	template <typename T>
	tvec3<T> rotateX(const tvec3<T>& v, T angle)
	{
		tvec3<T> res(v);
		T c = cos(T(DEG2RAD(angle)));
		T s = sin(T(DEG2RAD(angle)));

		res.y = v.y * c - v.z * s;
		res.z = v.y * s + v.z * c;
		return res;
	}

	template <typename T>
	tvec3<T> rotateY(tvec3<T> const & v, T angle)
	{
		tvec3<T> res = v;

		T c = cos(T(DEG2RAD(angle)));
		T s = sin(T(DEG2RAD(angle)));

		res.x = v.x * c + v.z * s;
		res.z = -v.x * s + v.z * c;
		return res;
	}

	template <typename T>
	tvec3<T> rotateZ(tvec3<T> const & v, T angle)
	{

		tvec3<T> res = v;

		T c = cos(DEG2RAD(angle));

		T s = sin(DEG2RAD(angle));

		res.x = v.x * c - v.y * s;
		res.y = v.x * s + v.y * c;
		return res;
	}

	template <typename T>
	static T clamp(T val, T minval, T maxval)
	{
		assert(minval < maxval && "Invalid clamp range");
		return MAX(MIN(val, maxval), minval);
	}

	template <typename T>
	inline   T  acosEx(T val)
	{
		if (T(-1.0f) < val)
		{
			if (val < 1.0f)
				return T(acos(val));
			else
				return T(0);
		}
		else
		{
			return T(PI);
		}
	}

	template<typename T>
	bool operator >(const tvec3<T>& left, const tvec3<T>& right)
	{
		return  left.x > right.x && left.y > right.y && left.z > right.z;
	}

	template<typename T>
	bool operator <(const tvec3<T>& left, const tvec3<T>& right)
	{
		return  left.x < right.x && left.y < right.y && left.z < right.z;
	}

	template <typename T>
	tmat4x4<T> const operator++ (tmat4x4<T> const & m, int)
	{
		return tmat4x4<T>(
			m[0] + T(1),
			m[1] + T(1),
			m[2] + T(1),
			m[3] + T(1));
	}

	template <typename T>
	tmat4x4<T> const operator-- (tmat4x4<T> const & m, int)
	{
		return tmat4x4<T>(
			m[0] - T(1),
			m[1] - T(1),
			m[2] - T(1),
			m[3] - T(1));
	}

	template <typename T>
	bool operator==(tmat4x4<T> const & m1, tmat4x4<T> const & m2)
	{
		return (m1[0] == m2[0]) && (m1[1] == m2[1]) && (m1[2] == m2[2]) && (m1[3] == m2[3]);
	}

	template <typename T>
	bool operator!=(tmat4x4<T> const & m1, tmat4x4<T> const & m2)
	{
		return (m1[0] != m2[0]) || (m1[1] != m2[1]) || (m1[2] != m2[2]) || (m1[3] != m2[3]);
	}

	template <typename T>
	tmat4x4<T> operator/ (tmat4x4<T> const & m1, tmat4x4<T> const & m2)
	{
		return m1 * m2.inverse();
	}

	template <typename T>
	tmat4x4<T> const operator- (tmat4x4<T> const & m)
	{
		return tmat4x4<T>(
			-m[0],
			-m[1],
			-m[2],
			-m[3]);
	}

	template <typename T>
	tmat4x4<T> operator/ (tmat4x4<T> const & m, typename tmat4x4<T>::value_type s)
	{
		return tmat4x4<T>(
			m[0] / s,
			m[1] / s,
			m[2] / s,
			m[3] / s);
	}

	template <typename T>
	tmat4x4<T> operator/ (typename tmat4x4<T>::value_type s, tmat4x4<T> const & m)
	{
		return tmat4x4<T>(
			s / m[0],
			s / m[1],
			s / m[2],
			s / m[3]);
	}

	template <typename T>
	tmat4x4<T> operator+ (tmat4x4<T> const & m, typename tmat4x4<T>::value_type s)
	{
	return tmat4x4<T>(
	m[0] + s,
	m[1] + s,
	m[2] + s,
	m[3] + s);
	}

	template <typename T>
	tmat4x4<T> operator+ (typename tmat4x4<T>::value_type s, tmat4x4<T> const & m)
	{
	return tmat4x4<T>(
	m[0] + s,
	m[1] + s,
	m[2] + s,
	m[3] + s);
	}

	template <typename T>
	tmat4x4<T> operator+ (tmat4x4<T> const & m1, tmat4x4<T> const & m2)
	{
	return tmat4x4<T>(
	m1[0] + m2[0],
	m1[1] + m2[1],
	m1[2] + m2[2],
	m1[3] + m2[3]);
	}

	template <typename T>
	tmat4x4<T> operator- (tmat4x4<T> const & m, typename tmat4x4<T>::value_type s)
	{
	return tmat4x4<T>(
	m[0] - s,
	m[1] - s,
	m[2] - s,
	m[3] - s);
	}

	template <typename T>
	tmat4x4<T> operator- (typename tmat4x4<T>::value_type s, tmat4x4<T> const & m)
	{
	return tmat4x4<T>(
	s - m[0],
	s - m[1],
	s - m[2],
	s - m[3]);
	}

	template <typename T>
	tmat4x4<T> operator- (tmat4x4<T> const & m1, tmat4x4<T> const & m2)
	{
	return tmat4x4<T>(
	m1[0] - m2[0],
	m1[1] - m2[1],
	m1[2] - m2[2],
	m1[3] - m2[3]);
	}
	
	template <typename T>
	tmat3x3<T> operator+ (tmat3x3<T> const & m, T const & s)
	{
	return tmat3x3<T>(
	m[0] + s,
	m[1] + s,
	m[2] + s);
	}

	template <typename T>
	tmat3x3<T> operator+ (T const & s, tmat3x3<T> const & m)
	{
	return tmat3x3<T>(
	m[0] + s,
	m[1] + s,
	m[2] + s);
	}

	template <typename T>
	tmat3x3<T> operator+ (tmat3x3<T> const & m1, tmat3x3<T> const & m2)
	{
	return tmat3x3<T>(
	m1[0] + m2[0],
	m1[1] + m2[1],
	m1[2] + m2[2]);
	}

	template <typename T>
	tmat3x3<T> operator- (tmat3x3<T> const & m, T const & s)
	{
	return tmat3x3<T>(
	m[0] - s,
	m[1] - s,
	m[2] - s);
	}

	template <typename T>
	tmat3x3<T> operator- (T const & s, tmat3x3<T> const & m)
	{
	return tmat3x3<T>(
	s - m[0],
	s - m[1],
	s - m[2]);
	}

	template <typename T>
	tmat3x3<T> operator- (tmat3x3<T> const & m1, tmat3x3<T> const & m2)
	{
	return tmat3x3<T>(
	m1[0] - m2[0],
	m1[1] - m2[1],
	m1[2] - m2[2]);
	}

	template <typename T>
	tmat3x3<T> operator* (tmat3x3<T> const & m, T const & s)
	{
	return tmat3x3<T>(
	m[0] * s,
	m[1] * s,
	m[2] * s);
	}

	template <typename T>
	tmat3x3<T> operator* (T const & s, tmat3x3<T> const & m)
	{
	return tmat3x3<T>(
	m[0] * s,
	m[1] * s,
	m[2] * s);
	}

	template <typename T>
	tvec3<T> operator* (tmat3x3<T> const & m, tvec3<T> const & v)
	{
	return  tvec3<T>(
	m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z,
	m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z,
	m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z);
	}

	template <typename T>
	tvec3<T> operator* (tvec3<T> const & v, tmat3x3<T> const & m)
	{
	return tvec3<T>(
	m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z,
	m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z,
	m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z);
	}

	template <typename T>
	tmat3x3<T> operator* (tmat3x3<T> const & m1, tmat3x3<T> const & m2)
	{
	T const srcA00 = m1[0][0];
	T const srcA01 = m1[0][1];
	T const srcA02 = m1[0][2];
	T const srcA10 = m1[1][0];
	T const srcA11 = m1[1][1];
	T const srcA12 = m1[1][2];
	T const srcA20 = m1[2][0];
	T const srcA21 = m1[2][1];
	T const srcA22 = m1[2][2];

	T const srcB00 = m2[0][0];
	T const srcB01 = m2[0][1];
	T const srcB02 = m2[0][2];
	T const srcB10 = m2[1][0];
	T const srcB11 = m2[1][1];
	T const srcB12 = m2[1][2];
	T const srcB20 = m2[2][0];
	T const srcB21 = m2[2][1];
	T const srcB22 = m2[2][2];

	tmat3x3<T> res;
	res[0][0] = srcA00 * srcB00 + srcA10 * srcB01 + srcA20 * srcB02;
	res[0][1] = srcA01 * srcB00 + srcA11 * srcB01 + srcA21 * srcB02;
	res[0][2] = srcA02 * srcB00 + srcA12 * srcB01 + srcA22 * srcB02;
	res[1][0] = srcA00 * srcB10 + srcA10 * srcB11 + srcA20 * srcB12;
	res[1][1] = srcA01 * srcB10 + srcA11 * srcB11 + srcA21 * srcB12;
	res[1][2] = srcA02 * srcB10 + srcA12 * srcB11 + srcA22 * srcB12;
	res[2][0] = srcA00 * srcB20 + srcA10 * srcB21 + srcA20 * srcB22;
	res[2][1] = srcA01 * srcB20 + srcA11 * srcB21 + srcA21 * srcB22;
	res[2][2] = srcA02 * srcB20 + srcA12 * srcB21 + srcA22 * srcB22;
	return res;
	}

	template <typename T>
	tmat3x3<T> operator/ (tmat3x3<T> const & m, T const & s)
	{
	return tmat3x3<T>(
	m[0] / s,
	m[1] / s,
	m[2] / s);
	}

	template <typename T>
	tmat3x3<T> operator/ (T const & s, tmat3x3<T> const & m)
	{
	return tmat3x3<T>(
	s / m[0],
	s / m[1],
	s / m[2]
	);
	}

	template <typename T>
	tvec3<T> operator/ (tmat3x3<T> const & m, tvec3<T> const & v)
	{
	return m._inverse() * v;
	}

	template <typename T>
	tvec3<T> operator/ (tvec3<T> const & v, tmat3x3<T> const & m)
	{
	return v * m._inverse();
	}

	template <typename T>
	tmat3x3<T> operator/ (tmat3x3<T> const & m1, tmat3x3<T> const & m2)
	{
	return m1 * m2._inverse();
	}

	template <typename T>
	tmat3x3<T> const operator- (tmat3x3<T> const & m)
	{
	return tmat3x3<T>(
	-m[0],
	-m[1],
	-m[2]);
	}

	template <typename T>
	tmat3x3<T> const operator++ (tmat3x3<T> const & m, int)
	{
	return tmat3x3<T>(
	m[0] + T(1),
	m[1] + T(1),
	m[2] + T(1));
	}

	template <typename T>
	tmat3x3<T> const operator-- (tmat3x3<T> const & m, int)
	{
	return tmat3x3<T>(
	m[0] - T(1),
	m[1] - T(1),
	m[2] - T(1));
	}
	template <typename T>
	bool operator==(tmat3x3<T> const & m1, tmat3x3<T> const & m2)
	{
	return (m1[0] == m2[0]) && (m1[1] == m2[1]) && (m1[2] == m2[2]);
	}

	template <typename T>
	bool operator!=(tmat3x3<T> const & m1, tmat3x3<T> const & m2)
	{
	return (m1[0] != m2[0]) || (m1[1] != m2[1]) || (m1[2] != m2[2]);
	}
	
	
	template <typename T>
	bool operator==
	(
	tvec4<T> const & v1,
	tvec4<T> const & v2
	)
	{
	return (v1.x == v2.x) && (v1.y == v2.y) && (v1.z == v2.z) && (v1.w == v2.w);
	}

	template <typename T>
	bool operator!=(tvec4<T> const & v1, tvec4<T> const & v2)
	{
		return (v1.x != v2.x) || (v1.y != v2.y) || (v1.z != v2.z) || (v1.w != v2.w);
	}

	template <typename T>
	tvec4<T> operator- (tvec4<T> const & v)
	{
		return tvec4<T>(
			-v.x,
			-v.y,
			-v.z,
			-v.w);
	}

	template <typename T>
	tvec4<T> rotateX(const tvec4<T>& v, T angle)
	{
		tvec4<T> res(v);
		T c = cos(DEG2RAD(angle));
		T s = sin(DEG2RAD(angle));

		res.y = v.y * c - v.z * s;
		res.z = v.y * s + v.z * c;
		return res;
	}

	template <typename T>
	tvec4<T> rotateY(tvec4<T> const & v, T angle)
	{
		tvec4<T> res = v;

		T c = cos(DEG2RAD(angle));
		T s = sin(DEG2RAD(angle));

		res.x = v.x * c + v.z * s;
		res.z = -v.x * s + v.z * c;
		return res;
	}

	template <typename T>
	tvec4<T> rotateZ(tvec4<T> const & v, T angle)
	{

		tvec4<T> res = v;

		T c = cos(DEG2RAD(angle));
		T s = sin(DEG2RAD(angle));

		res.x = v.x * c - v.y * s;
		res.y = v.x * s + v.y * c;
		return res;
	}

	template <typename T>
	tvec4<T> operator- (tvec4<T> const & v, T const & s)
	{
		return tvec4<T>(
			v.x - s,
			v.y - s,
			v.z - s,
			v.w - s);
	}

	template <typename T>
	tvec4<T> operator-  (T const & s, tvec4<T> const & v)
	{
		return tvec4<T>(
			s - v.x,
			s - v.y,
			s - v.z,
			s - v.w);
	}

	template <typename T>
	tvec4<T> operator-
		(
			tvec4<T> const & v1,
			tvec4<T> const & v2
			)
	{
		return tvec4<T>(
			v1.x - v2.x,
			v1.y - v2.y,
			v1.z - v2.z,
			v1.w - v2.w);
	}


	template <typename T>
	tvec3<T> operator++ (tvec3<T> const & v, int)
	{
		return tvec3<T>(
			v.x + T(1),
			v.y + T(1),
			v.z + T(1));
	}

	template <typename T>
	tvec3<T> operator-- (tvec3<T> const & v, int)
	{
		return tvec3<T>(
			v.x - T(1),
			v.y - T(1),
			v.z - T(1));
	}

	template <typename T>
	bool operator==(tvec3<T> const & v1, tvec3<T> const & v2)
	{
		return (v1.x == v2.x) && (v1.y == v2.y) && (v1.z == v2.z);
	}

	template <typename T>
	bool operator!=(tvec3<T> const & v1, tvec3<T> const & v2)
	{
		return (v1.x != v2.x) || (v1.y != v2.y) || (v1.z != v2.z);
	}

	template <typename T>
	tvec2<T> operator++ (tvec2<T> const & v, int)
	{
		return  tvec2<T>(
			v.x + T(1),
			v.y + T(1)
			);
	}

	template <typename T>
	tvec2<T> operator-- (tvec2<T> const & v, int)
	{
		return  tvec2<T>(
			v.x - T(1),
			v.y - T(1)
			);
	}

	template <typename T>
	tvec2<T> operator/(tvec2<T> const & v, T const & s)
	{
		return tvec2<T>(
			v.x / T(s),
			v.y / T(s));
	}

	template <typename T>
	tvec2<T> operator/(T const & s, tvec2<T> const & v)
	{
		return tvec2<T>(
			T(s) / v.x,
			T(s) / v.y);
	}

	template <typename T>
	tvec2<T> operator/  (tvec2<T> const & v1, tvec2<T> const & v2)
	{
		return  tvec2<T>(
			v1.x / T(v2.x),
			v1.y / T(v2.y)
			);
	}


	template <typename T>
	tvec2<T> rotate(tvec2<T> const & v, T angle)
	{
		tvec2<T> res;
		T const c(cos(DEG2RAD(angle)));
		T const s(sin(DEG2RAD(angle)));
		res.x = v.x * c - v.y * s;
		res.y = v.x * s + v.y * c;
		return res;
	}

	template <typename T>
	bool operator==(tvec2<T> const & v1, tvec2<T> const & v2)
	{
		return (v1.x == v2.x) && (v1.y == v2.y);
	}

	template <typename T>
	bool operator!=(tvec2<T> const & v1, tvec2<T> const & v2)
	{
		return (v1.x != v2.x) || (v1.y != v2.y);
	}

	typedef tellipsoidModel<real>  ellipsoid;
	typedef AxisAlignedBox2D<float> AABB2D;
	typedef AxisAlignedBox2D<real>  aabb2dr;

	typedef trect<real>             rect4;
	typedef trect<int>              rect4i;

	typedef tmat2x2<real>       matrix2r;
	typedef tmat2x2<float>      matrix2;
	typedef tmat2x2<double>     matrix2d;

	typedef tquat<float>        quaternion;
	typedef tquat<float>        quatf;
	typedef tquat<real>         quatr;
}