#pragma once

#include <cmath>
#include <string>
#include <core\LatLon.h>
#include <projections\Ellipsoid.h>

# define M_PI          3.141592653589793238462643383279502884L /* pi */

namespace libegis {

	// Lambert Conformation 2 Standard Parallels map projection.
	class LambertConformal2SP : public LatLon
	{
	public:
		static class Coord {
		public:
			Coord() {};

			double northing, easting;

			Coord(double northing, double easting) {
				this->northing = northing;
				this->easting = easting;
			}

			~Coord() {};

			std::string toString() {
			}

		};

		LambertConformal2SP() {};

		LambertConformal2SP(Ellipsoid ellipsoid, LatLon falseOriginLl,
							double lat_1, double lat_2, Coord falseOriginLam)
		{
			this->ellipsoid = ellipsoid;
			this->false_origin_ll = falseOriginLl;
			this->lat_1 = lat_1;
			this->lat_2 = lat_2;
			this->false_origin_lam = falseOriginLam;

			this->e = sqrt(ellipsoid.eccsq);
			double phi1 = toRadians(this->lat_1);
			double phi2 = toRadians(this->lat_2);
			double t1 = compute_t(e, phi1);
			double t2 = compute_t(e, phi2);
			double m1 = compute_m(e, phi1);
			double m2 = compute_m(e, phi2);

			this->n = (log(m1) - log(m2)) / (log(t1) - log(t2));
			this->F = m1 / (n* pow(t1, n));

			double phiF = toRadians(false_origin_ll.getLat());
			double tF = compute_t(e, phiF);
			this->rF = ellipsoid.eqr * F * pow(tF, n);
		}

		~LambertConformal2SP() {};

		Coord getLambert(LatLon in) 
		{
			double phi = toRadians(in.getLat());
			double t = compute_t(e, phi);
			double r = ellipsoid.eqr * F * pow(t, n);
			double lambda = toRadians(in.getLon());
			double lambdaF = toRadians(false_origin_ll.getLon());
			double theta = n * (lambda - lambdaF);

			double easting = false_origin_lam.easting + r * sin(theta);
			double northing = false_origin_lam.northing + rF - r * cos(theta);
			return Coord(northing, easting);
		}

		LatLon getLatLon(Coord lam) 
		{
			double eastdiff = (lam.easting - false_origin_lam.easting);
			double northdiff = (lam.northing - false_origin_lam.northing);
			double rFnorthdiff = rF - northdiff;
			double r = sqrt(eastdiff*eastdiff + rFnorthdiff*rFnorthdiff);
			if (n < 0) r = -r;
			double t = pow(r / (ellipsoid.eqr*F), 1 / n);
			double theta = atan(eastdiff / rFnorthdiff);

			double lon = toDegrees(theta / n) + false_origin_ll.getLon();

			// iterate to find phi
			double phi = M_PI / 2 - 2 * atan(t);
			double old_phi;
			int iter = 0;
			do {
				old_phi = phi;
				++iter;
				phi = M_PI / 2 - 2 * atan(t* pow((1 - e* sin(phi)) / (1 + e* sin(phi)), e / 2));
			} while (abs(phi - old_phi) > 0.00001 && iter < 5);

			double lat = toDegrees(phi);
			return LatLon(lat, lon);
		}

	private:
		Ellipsoid ellipsoid;
		LatLon false_origin_ll;
		Coord false_origin_lam;
		double lat_1, lat_2;
		double e, n, F, rF;

		static double compute_t(double e, double phi) {
			double esinphi = e* sin(phi);
			return tan(M_PI / 4 - phi / 2) / pow((1 - esinphi) / (1 + esinphi), e / 2);
		}

		static double compute_m(double e, double phi) {
			double esinphi = e* sin(phi);
			return cos(phi) / sqrt(1 - esinphi*esinphi);
	};

}