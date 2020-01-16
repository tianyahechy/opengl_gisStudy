#pragma once
#include <cstdio>
#include <cassert>
#include <cmath>
#include <vector>
#include <map>
#include <limits>
#include <xutility>

namespace CELL
{
	typedef unsigned char			byte;
	typedef long long				int64;
	typedef unsigned long long		uint64;
	typedef unsigned short			ushort;
	typedef unsigned int			uint;
	typedef unsigned long			ulong;
	typedef double					real;

#define	PI							3.14159265358979323846264338327
#define DEG2RAD(theta)				(0.01745329251994329 * theta)
#define RAD2DEG						57.2957795130823208

	template <class T>
	inline T tmin(T a, T b)
	{
		return a < b ? a : b;
	}

	template <class T>
	inline T tmax(T a, T b)
	{
		return a > b ? a : b;
	}

}