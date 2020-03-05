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
			int px = int((mx + _originShift) / res);
			int py = int((my + _originShift) / res);
			return int2(px, py);

		}

		int2 pixelsToTile(int px, int py)
		{
			int tx = int(ceil(px / real(_tileSize)) - 1);
			int ty = int(ceil(py / real(_tileSize)) - 1);
			return int2(tx, ty);
		}

		int2 MetersToTile(real mx, real my, int zoom)
		{
			int2 vPt = MetersToPixels(mx, my, zoom);
			return pixelsToTile(vPt.x, vPt.y);
		}
	};

	class lifeiSpatialReference_2
	{
	protected:
		GlobalMercator_2 _proj;

	public:
		lifeiSpatialReference_2()
		{

		}
		~lifeiSpatialReference_2()
		{

		}
		//将经度转化为x-tile key
		static int long2tilex(real lon, int z)
		{
			return (int)(floor((lon + 180.0) / 360.0 * pow(2.0, z)));
		}
		//将纬度转化为y-tile key
		static int lat2tiley(real lat, int z)
		{
			return (int)(floor((1.0 - log(tan(lat * PI / 180.0) + 1.0 / cos(lat * PI / 180.0)) / PI) / 2.0 * pow(2.0, z)));
		}
		//给定x-tile获取经度
		static real tilex2long(int x, int z)
		{
			return x / pow(2.0, z) * 360.0 - 180.0;
		}
		//给定y-tile获取纬度
		static real tiley2lat(int y, int z)
		{
			real n = PI - 2.0 * PI * y / pow(2.0, z);
			return 180.0 / PI * atan(0.5 * (exp(n) - exp(-n)));
		}

		static real2 tile2lonlat(int x, int y, int z)
		{
			real lon = tilex2long(x, z);
			real lat = tiley2lat(y, z);
			return real2(lon, lat);
		}

		real2 tile2World(int x, int y, int z)
		{
			real2 lonlat = tile2lonlat(x, y, z);
			return _proj.LatLonToMeters(lonlat.x, lonlat.y);
		}

		//根据经纬度与级别返回瓦片key
		static int2 getKey(unsigned level, real rLong, real rLat)
		{
			if (rLong <= - 180 )
			{
				rLong = -179.9;
			}
			if (rLong >= 180)
			{
				rLong = 179.9;
			}
			if (rLat < -85)
			{
				rLat = -85;
			}
			if (rLat > 85)
			{
				rLat = 85;
			}

			int xTile = long2tilex(rLong, level);
			int yTile = lat2tiley(rLat, level);
			return int2(xTile, yTile);
		}
	public:
		//经纬度转世界坐标
		real2 longlatToWorld(const real2& longlat)
		{
			real2 theLonLat = longlat;
			theLonLat.x = tmin<real>(179.9999f, theLonLat.x);
			theLonLat.x = tmax<real>(-179.9999f, theLonLat.x);
			theLonLat.y = tmin<real>(85.0f, theLonLat.y);
			theLonLat.y = tmax<real>(-85.0f, theLonLat.y);
			return _proj.LatLonToMeters(theLonLat.x, theLonLat.y);
		}

		//世界坐标转经纬度
		real2 worldToLongLat(const real2& world)
		{
			const real worldMin = -20037504.0f * 1000;
			const real worldMax = 20037504.0f * 1000;
			real dWorldX = (real)tmin<real>(world.x, worldMax);
			dWorldX = (real)tmax<real>(dWorldX, worldMin);
			real dWorldY = (real)tmin<real>(world.y, worldMax);
			dWorldY = (real)tmax<real>(dWorldY, worldMin);
			return _proj.MetersToLatLon((int)dWorldX, (int)dWorldY);
		}

		//得到当前级别下的tile的个数
		int getTileNumber(int lev)
		{
			return (int)pow(2, real(lev));
		}
	
	};

	typedef lifeiSpatialReference_2 spatialReference;
}