#pragma once

#include <algorithm>
#include <string>
#include <cmath>

# define M_PI          3.141592653589793238462643383279502884L /* pi */

namespace libegis {

	class LatLon
	{
	public:
		LatLon() {}

		LatLon(double lat, double lon)
		{
			this->lat = lat;
			this->lon = lon;
		}

		~LatLon() {}

		double getLat()
		{
			return lat;
		}

		double getLon()
		{
			return lon;
		}

		double distanceInKms(LatLon other)
		{
			double lat1 = toRadians(this->lat);
			double lat2 = toRadians(other.lat);
			double lon1 = toRadians(this->lon);
			double lon2 = toRadians(other.lon);

			// double R = 6371; // spherical earth radius
			double lat0 = (lat2 + lat1) / 2;
			double a = 6378.137; // WGS-84
			double f = 1.0 / 298.257223563;
			double esq = f*(2 - f);
			double R = a * (1 - esq) / pow(sq(1 - esq*(sin(lat0))), 1.5);
			double dlon = lon2 - lon1;
			double dlat = lat2 - lat1;
			double term = sq(sin(dlat / 2)) + cos(lat1) * cos(lat2) * sq(sin(dlon / 2));
			return (2 * R * asin(std::fmin(1, sqrt(term))));
			std::min(1, 9999);
		}

		const double toRadians(double deg)
		{
			return deg * M_PI / 180.0;
		}

		std::string toString()
		{
			return "[" + std::to_string(getLat()) + "," + std::to_string(getLon()) + "]";
		}

	private:
		double lat, lon;
		const static double sq(double x)
		{
			return x*x;
		}
	};

}