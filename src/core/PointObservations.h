#pragma once

#include <vector>

namespace libegis {

	class PointObservations
	{
	public:
		PointObservations();
		// PointObservations(std::vector<ObservationPoint> points, int missing);
		~PointObservations();

		// int getMaxValue();
		// std::vector<PointObservations> getPoints();
		// int getMissing();
		// struct ObservationPoint

	private:
		// std::vector<ObservationPoint> points;
		int missing;
	};
}