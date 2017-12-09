#pragma once

#include <string>

namespace libegis {

	class LatLon
	{
	public:
		LatLon();
		~LatLon();
		LatLon(double lat, double lon);

		double getLat();
		double getLon();
		double distanceInKms(LatLon other);
		const double toRadians(double deg);
		std::string toString();

	private:
		double lat, lon;
		const static double sq(double x);
	};

}