#pragma once

#include <vector>
#include "LatLon.h"

namespace libegis {

	class LatLonGrid
	{
	public:
		LatLonGrid();
		LatLonGrid(std::vector< std::vector<int> > &data, int missing, LatLon nwCorner, double latres, double lonres);
		LatLonGrid(int nrows, int ncols, int missing, LatLon nwCorner, double latres, double lonres);
		~LatLonGrid();


		LatLonGrid copyOf(LatLonGrid &original);
		LatLonGrid crop(int startRow, int startCol, int numLat, int numLon);
		std::vector< std::vector<int> > getData();
		int getMissing();
		LatLon getNwCorner();
		double getLatRes();
		double getLonRes();
		// LatLon getLocation(Pixel p); 
		LatLon getLocation(int row, int col);
		LatLon getLocation(double row, double col);
		LatLon getSeCorner();
		int getNumLat();
		int getNumLon();
		int getValue(int row, int col);
		void setValue(int row, int col, int value);
		void setMissing(int i);
		const int getRow(LatLon location);
		// const Pixel getPixel(LatLon location);
		int getCol(LatLon location);
		const int getValue(LatLon location);
		const bool isValid(int row, int col);
		void fill(int newval);
		void replace(int oldval, int newval);
		static LatLonGrid add(LatLonGrid a, LatLonGrid b);
		// int getValue(Pixel p);
		// std::vector<Pixel> asPixels();
		std::vector< std::vector<int> > longitudewrap(int Ny);
		LatLonGrid remapTo(LatLonGrid other);

	private:
		std::vector< std::vector<int> > data;
		int missing;
		LatLon nwCorner;
		double latRes;
		double lonRes;
	};

}