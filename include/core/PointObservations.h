#pragma once

#include <vector>
#include <string>
#include "core\LatLon.h"

namespace libegis {

	class PointObservations
	{
	public:
		PointObservations() {}

		// ObservationPoint type declaration
		static class ObservationPoint : public LatLon
		{
		public:
			int value;

			ObservationPoint(double lat, double lon, const int& value) {
				LatLon(lat, lon);
				this->value = value;
			}

			int getValue() {
				return value;
			}

			std::string toString() {
				std::string result = "[" + std::to_string(getLat()) + "," + std::to_string(getLon()) + "," + std::to_string(getValue()) + "]";
				return result;
			}
		};

		PointObservations(std::vector<ObservationPoint> points, int missing)
		{
			this->points = points;
			this->missing = missing;
		}

		~PointObservations() {}

		int getMaxValue()
		{
			int result = missing;
			for (int i = 0; i < points.size(); ++i) {
				if (result == missing || points[i].getValue() > result) {
					result = points[i].getValue();
				}
			}
			return result;
		}

		int getMissing()
		{

		}

		std::vector<ObservationPoint> getPoints()
		{
			return points;
		}

	private:
		std::vector<ObservationPoint> points;
		int missing;
	};
}