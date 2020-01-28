#pragma once

#include "tmat4x4.h"

namespace CELL
{
	template <typename T>
	tmat4x4<T> ortho(
		T left,
		T right,
		T bottom,
		T top,
		T zNear,
		T zFar
		)
	{
		tmat4x4<T> res(1);
		res[0][0] = T(2) / (right - left);
		res[1][1] = T(2) / (top - bottom);
		res[2][2] = -T(2) / (zFar - zNear);
		res[3][0] = -(right + left) / (right - left);
		res[3][1] = -(top + bottom) / (top - bottom);
		res[3][2] = -(zNear + zFar) / (zFar - zNear);
		return res;
	}

	template<typename T>
	void frustum(T * matrix, T left, T right, T bottom, T top, T zNear, T zFar)
	{
		T temp = T(2.0) * zNear;
		T temp2 = right - left;
		T temp3 = top - bottom;
		T temp4 = zFar - zNear;

		matrix[0] = temp / temp2;
		matrix[1] = T(0.0);
		matrix[2] = T(0.0);
		matrix[3] = T(0.0);
		matrix[4] = T(0.0);
		matrix[5] = temp / temp3;
		matrix[6] = T(0.0);
		matrix[7] = T(0.0);
		matrix[8] = (right + left) / temp2;
		matrix[9] = (top + bottom) / temp3;
		matrix[10] = (-zFar - zNear) / temp4;
		matrix[11] = T(-1.0);
		matrix[12] = T(0.0);
		matrix[13] = T(0.0);
		matrix[14] = (-temp * zFar) / temp4;
		matrix[15] = T(0.0);
	}

	template<typename T>
	tmat4x4<T> perspective(T fovY, T aspect, T zNear, T zFar)
	{
		tmat4x4<T> res(0);
		T yMax = zNear * (T)tan((T)(fovY * PI / 360.0));
		T xMax = yMax * aspect;

		frustum<T>((T*)res.data(), -xMax, xMax, -yMax, yMax, zNear, zFar);
		return res;
	}

	template<typename T>
	tmat4x4<T> lookAt(
		tvec3<T> const& eye,
		tvec3<T> const& center,
		tvec3<T> const& up
		)
	{
		tvec3<T> zAxis = normalize(center - eye);
		tvec3<T> yAxis = normalize(up);
		tvec3<T> xAxis = normalize(cross(zAxis, yAxis));
		yAxis = normalize(cross(xAxis, zAxis));

		tmat4x4<T> res(1);
		res[0][0] = xAxis.x;
		res[1][0] = xAxis.y;
		res[2][0] = xAxis.z;
		res[0][1] = yAxis.x;
		res[1][1] = yAxis.y;
		res[2][1] = yAxis.z;
		res[0][2] = -zAxis.x;
		res[1][2] = -zAxis.y;
		res[2][2] = -zAxis.z;
		res[3][0] = -dot(xAxis, eye);
		res[3][1] = -dot(yAxis, eye);
		res[3][2] = dot(zAxis, eye);

		return res;

	}
	
	template<typename T>
	tmat4x4<T> lookAtL(
		tvec3<T> const& eye,
		tvec3<T> const& center,
		tvec3<T> const& up
		)
	{
		tvec3<T> zAxis = normalize(center - eye);
		tvec3<T> yAxis = normalize(up);
		tvec3<T> xAxis = normalize(cross(yAxis, zAxis));
		yAxis = normalize(cross(zAxis, xAxis));

		tmat4x4<T> res(1);
		res[0][0] = xAxis.x;
		res[1][0] = xAxis.y;
		res[2][0] = xAxis.z;
		res[0][1] = yAxis.x;
		res[1][1] = yAxis.y;
		res[2][1] = yAxis.z;
		res[0][2] = -zAxis.x;
		res[1][2] = -zAxis.y;
		res[2][2] = -zAxis.z;
		res[3][0] = -dot(xAxis, eye);
		res[3][1] = -dot(yAxis, eye);
		res[3][2] = dot(zAxis, eye);

		return res;

	}

}