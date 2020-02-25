#pragma once
#include "lifeiMathUtil.h"
#include "tvec2.h"

namespace CELL
{
	class GlobalMercator_2
	{
	protected:
		int		_tileSize;			//每张瓦片的大小
		real	_initialResolution;	//初始分辨率，每像素对应多少米
		real	_originShift;		//整个地球投影出来的边长

	public:
		GlobalMercator_2()
		{
			_tileSize = 256;
			_initialResolution = 2 * PI * 6378137 / _tileSize;
			_originShift = 2 * PI * 6378137 / 2.0;
		}
		//经纬度转换成米
		real2 LatLonToMeters(real lat, real lon)
		{
			//从WGS84经纬度转到EPSG:900913的xy
			real mx = lon * _originShift / 180.0;
			real my = log(tan((90 + lat) * PI / 360.0)) / (PI / 180.0);
			my = my * _originShift / 180.0;
			return real2(mx, my);
		}

		//米转换成经纬度
		real2 MetersToLatLon(int mx, int my)
		{
			real lon = (mx / _originShift) * 180.0f;
			real lat = (my / _originShift) * 180.0f;
			lat = real(180 / PI * (2 * atan(exp(lat * PI / 180.0)) - PI / 2.0));
			return real2(lon, lat);
		}

		real resolution(int zoom)
		{
			return _initialResolution / (pow(2, real(zoom)));
		}
		//像素转换成米
		real2 PixelsToMeters(int px, int py, int zoom)
		{
			real res = resolution(zoom);
			real mx = px * res - _originShift;
			real my = py * res - _originShift;
			return real2(mx, my);
		}

		//米转换成像素
		int2 MetersToPixels(real mx, real my, int zoom)
		{
			real res = resolution(zoom);

		}
	};
}