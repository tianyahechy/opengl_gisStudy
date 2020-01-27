#pragma once
#include "lifeiMathUtil.h"
#include "tvec3.h"
#include "tvec4.h"
#include "tmat3x3.h"
#include "tmat4x4.h"

namespace CELL
{
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

    
}
