#pragma once
#include "CELLMath.hpp"
namespace CELL
{
	const static int tileSize = 256;
	const static double intialResolution = 2 * PI * 6378137 / tileSize;
	const static double originShift = 2 * PI * 6378137 / 2.0;
	
	class lifeiMercator
	{
	public:
		lifeiMercator()
		{
		}
		static double lonToMeter(double lon)
		{
			return lon * originShift / 180.0;
		}
		static double latToMeter(double lat)
		{
			double my = log(tan((90 * lat) * PI / 360.0)) / (PI / 180.0);
			return my * originShift / 180.0;
		}
		//经纬度转化成米
		static double2 lonLatToMeters(double lon, double lat)
		{
			double mx = lon * originShift / 180.0;
			double my = log(tan((90 * lat) * PI / 360.0)) / (PI / 180.0);
			my = my * originShift / 180.0;
			return double2(mx, my);
		}
		//米转成经纬度
		static double2 metersToLonLat(int mx, int my)
		{
			double lon = (mx / originShift) * 180.0;
			double lat = (my / originShift) * 180.0;
			lat = 180.0 / PI * (2 * atan(exp(lat * PI / 180.0)) - PI / 2.0);
			return double2(lon, lat);
		}
		static double resolution(int zoom)
		{
			return intialResolution / (pow(2, double(zoom)));
		}

	};
}