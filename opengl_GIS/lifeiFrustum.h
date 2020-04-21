#pragma once
#include "Plane.h"

namespace CELL
{
	template<class T>
	class lifeiFrustum
	{
	public:
		Plane<T> _planes[6];
	public:
		enum 
		{
			FRUSTUM_LEFT	= 0,
			FRUSTUM_RIGHT	= 1,
			FRUSTUM_TOP		= 2,
			FRUSTUM_BOTTOM	= 3,
			FRUSTUM_FAR		= 4,
			FRUSTUM_NEAR	= 5,
		};

		void loadFrustum_2(const tmat4x4<T>& mvp)
		{
			const T* dataPtr = mvp.data();
			_planes[FRUSTUM_LEFT] = Plane<T>(dataPtr[12] - dataPtr[0], dataPtr[13] - dataPtr[1], dataPtr[14] - dataPtr[2], dataPtr[15] - dataPtr[3]);
			_planes[FRUSTUM_RIGHT] = Plane<T>(dataPtr[12] + dataPtr[0], dataPtr[13] + dataPtr[1], dataPtr[14] + dataPtr[2], dataPtr[15] + dataPtr[3]);
			_planes[FRUSTUM_TOP] = Plane<T>(dataPtr[12] - dataPtr[4], dataPtr[13] - dataPtr[5], dataPtr[14] - dataPtr[6], dataPtr[15] - dataPtr[7]);
			_planes[FRUSTUM_BOTTOM] = Plane<T>(dataPtr[12] + dataPtr[4], dataPtr[13] + dataPtr[5], dataPtr[14] + dataPtr[6], dataPtr[15] + dataPtr[7]);
			_planes[FRUSTUM_FAR] = Plane<T>(dataPtr[12] - dataPtr[8], dataPtr[13] - dataPtr[9], dataPtr[14] - dataPtr[10], dataPtr[15] - dataPtr[11]);
			_planes[FRUSTUM_NEAR] = Plane<T>(dataPtr[12] + dataPtr[8], dataPtr[13] + dataPtr[9], dataPtr[14] + dataPtr[10], dataPtr[15] + dataPtr[11]);
		}

		bool cubeInFrustum(T minX, T maxX, T minY, T maxY, T minZ, T maxZ) const
		{
			for (int i = 0; i < 6; i++)
			{
				if (_planes[i].distance(tvec3<T>(minX, minY, minZ)) > 0)
				{
					continue;
				}
				if (_planes[i].distance(tvec3<T>(minX, minY, maxZ)) > 0)
				{
					continue;
				}
				if (_planes[i].distance(tvec3<T>(minX, maxY, minZ)) > 0)
				{
					continue;
				}
				if (_planes[i].distance(tvec3<T>(minX, maxY, maxZ)) > 0)
				{
					continue;
				}
				if (_planes[i].distance(tvec3<T>(maxX, minY, minZ)) > 0)
				{
					continue;
				}
				if (_planes[i].distance(tvec3<T>(maxX, minY, maxZ)) > 0)
				{
					continue;
				}
				if (_planes[i].distance(tvec3<T>(maxX, maxY, minZ)) > 0)
				{
					continue;
				}
				if (_planes[i].distance(tvec3<T>(maxX, maxY, maxZ)) > 0)
				{
					continue;
				}
				return false;
			}
			return true;
		}

	};

	typedef lifeiFrustum<real>	Frustum;
}