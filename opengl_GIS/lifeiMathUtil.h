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

#define	PI							3.14159265358979323846264338327
#define	TWO_PI						( PI * 2)
#define HALF_PI						(3.14159265358979323846264338327 * 0.5)

#define DEG2RAD(theta)				(0.01745329251994329 * theta)
#define RAD2DEG						57.2957795130823208
#define LOG2						0.69314718055994529
#define WGS_84_RADIUS_EQUATOR_		6378137.0
#define WGS_84_RADIUS_POLAR_		6356752.3142
}