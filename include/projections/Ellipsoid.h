#pragma once

namespace libegis {

	class Ellipsoid
	{
	public:
		double eqr;
		double eccsq;

		Ellipsoid(double eqr, double eccsq)
		{
			this->eqr = eqr;
			this->eccsq = eccsq;
		}

		static Ellipsoid WGS84()
		{
			return Ellipsoid(6378137, 0.00669438);
		}

		static Ellipsoid NAD27() {
			return Ellipsoid(6378206, 0.006768658);
		}
	};
}