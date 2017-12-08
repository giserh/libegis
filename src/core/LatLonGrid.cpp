#include <iostream>
#include "LatLonGrid.h"

namespace libegis {

	LatLonGrid::LatLonGrid()
	{

	}


	/**
	* @param data  Holds on to provided data (does not clone the data)
	* @param missing  Missing data value, typically -9999 or similar
	* @param nwCorner the true corner, not the center of the first grid point
	* @param latres A positive number
	* @param lonres A positive number
	*/
	LatLonGrid::LatLonGrid(std::vector< std::vector<int> > &data, int missing, LatLon nwCorner, double latres, double lonres)
	{
		this->data = data;
		this->missing = missing;
		this->nwCorner = nwCorner;
		this->latRes = latres;
		this->lonRes = lonres;
	}

	/**
	* Initialize a grid of data at zero.
	*
	* @param nrows
	* @param ncols
	* @param missing  Missing data value, typically -9999 or similar
	* @param nwCorner the true corner, not the center of the first grid point
	* @param latres   A positive number
	* @param lonres   A positive number
	*/
	LatLonGrid::LatLonGrid(int nrows, int ncols, int missing, LatLon nwCorner, double latres, double lonres)
	{
		std::vector< std::vector<int> > data(nrows, std::vector<int>(ncols));
		this->missing = missing;
		this->nwCorner = nwCorner;
		this->latRes = latres;
		this->lonRes = lonres;
	}

	LatLonGrid::~LatLonGrid()
	{

	}

	/**
	* Make a deep copy
	*/
	LatLonGrid LatLonGrid::copyOf(LatLonGrid &original)
	{
		std::vector< std::vector<int> > copy(original.getNumLat(), std::vector<int>(original.getNumLon()));
		for (int i = 0; i < original.getNumLat(); ++i) {
			for (int j = 0; j < original.getNumLon(); ++j) {
				copy[i][j] = original.data[i][j];
			}
		}
		return LatLonGrid(copy, original.missing, original.nwCorner, original.latRes, original.lonRes);
	}

	LatLonGrid LatLonGrid::crop(int startRow, int startCol, int numLat, int numLon)
	{
		std::vector< std::vector<int> > copy(numLat, std::vector<int>(numLon));
		for (int i = 0; i < numLat; ++i) {
			for (int j = 0; j < numLon; ++j) {
				copy[i][j] = data[i + startRow][j + startCol];
			}
		}
		LatLon origin = this->getLocation(startRow, startCol);
		LatLon nwCorner = LatLon(origin.getLat() + latRes / 2, origin.getLon() - lonRes / 2);
		return LatLonGrid(copy, missing, nwCorner, latRes, lonRes);
	}

	std::vector< std::vector<int> > LatLonGrid::getData()
	{
		return data;
	}

	int LatLonGrid::getMissing()
	{
		return missing;
	}

	/**
	* Note that this is the true corner, not the center of the first grid point.
	* @return
	*/
	LatLon LatLonGrid::getNwCorner()
	{
		return nwCorner;
	}

	double LatLonGrid::getLatRes()
	{
		return latRes;
	}

	double LatLonGrid::getLonRes()
	{
		return lonRes;
	}

	// LatLon LatLonGrid::getLocation(Pixel p)
	// {
	// 
	// }

	LatLon LatLonGrid::getLocation(int row, int col)
	{
		return LatLon(nwCorner.getLat() - (row + 0.5)*latRes,
			nwCorner.getLon() + (col + 0.5)*lonRes);
	}

	LatLon LatLonGrid::getLocation(double row, double col)
	{
		return LatLon(nwCorner.getLat() - (row + 0.5)*latRes,
			nwCorner.getLon() + (col + 0.5)*lonRes);
	}

	/**
	* This is the true corner, not the middle of the last grid point
	*/
	LatLon LatLonGrid::getSeCorner()
	{
		// latitude decreases, longitude increases
		return LatLon(nwCorner.getLat() - getNumLat()*latRes,
			nwCorner.getLon() + getNumLon()*lonRes);
	}

	int LatLonGrid::getNumLat()
	{
		return data.size();
	}

	int LatLonGrid::getNumLon()
	{
		return data[0].size();
	}

	int LatLonGrid::getValue(int row, int col)
	{
		return data[row][col];
	}

	void LatLonGrid::setValue(int row, int col, int value)
	{
		data[row][col] = value;
	}

	void LatLonGrid::setMissing(int i)
	{
		missing = i;
	}

	const int LatLonGrid::getRow(LatLon location)
	{
		int row = (int)((nwCorner.getLat() - location.getLat()) / latRes);
		return row;
	}

	// const Pixel getPixel(LatLon location)
	// {
	// 
	// }

	/*
		The returned col may be outside this grid's dimensions
	*/
	int LatLonGrid::getCol(LatLon location)
	{
		int col = (int)((location.getLon() - nwCorner.getLon()) / lonRes);
		return col;
	}

	const int LatLonGrid::getValue(LatLon location)
	{
		int row = getRow(location);
		int col = getCol(location);
		if (isValid(row, col)) {
			return data[row][col];
		}
		return missing;
	}

	/*
		Are the pixel coordinates in bounds?
	*/
	const bool LatLonGrid::isValid(int row, int col)
	{
		return row >= 0 && row < data.size() && col >= 0 && col < data[row].size();
	}

	void LatLonGrid::fill(int newval)
	{
		const int nrows = data.size();
		const int ncols = data[0].size();
		for (int i = 0; i < nrows; ++i) {
			for (int j = 0; j < ncols; ++j) {
				data[i][j] = newval;
			}
		}
	}

	void LatLonGrid::replace(int oldval, int newval)
	{
		const int nrows = data.size();
		const int ncols = data[0].size();
		for (int i = 0; i < nrows; ++i) {
			for (int j = 0; j < ncols; ++j) {
				if (data[i][j] == oldval) {
					data[i][j] = newval;
				}
			}
		}
	}

	LatLonGrid LatLonGrid::add(LatLonGrid a, LatLonGrid b)
	{
		int nrows = a.getNumLat();
		int ncols = a.getNumLon();
		if (b.getNumLat() != nrows || b.getNumLon() != ncols) {
			// TODO: Exception handling
			std::string errorMsg = "Grids are of different dimensions: first grid is " + std::to_string(nrows) + "x" + std::to_string(ncols) + " while second grid is " + std::to_string(b.getNumLat()) + "x" + std::to_string(b.getNumLon());
			std::cout << errorMsg << std::endl;
		}
		LatLonGrid result = result.copyOf(a);
		for (int i = 0; i < nrows; ++i) {
			for (int j = 0; j < ncols; ++j) {
				if (result.data[i][j] != result.missing) {
					int bval = b.data[i][j];
					if (bval != b.missing) {
						result.data[i][j] += bval;
					}
					else {
						result.data[i][j] = result.missing;
					}
				}
			}
		}
		return result;
	}

	// int LatLonGrid::getValue(Pixel p)
	// {
	// 
	// }
	// 
	// std::vector<Pixel> LatLonGrid::asPixels()
	// {
	// 
	// }
	
	std::vector< std::vector<int> > LatLonGrid::longitudewrap(int Ny)
	{
		int nrows = data.size();
		int ncols = data[0].size();
		int hy = Ny / 2;
		int outcols = ncols + 2 * hy;
		std::vector< std::vector<int> > result(nrows, std::vector<int>(outcols));
		for (int i = 0; i < nrows; ++i) for (int j = 0; j < outcols; ++j) {
			int incol = j - hy;
			if (incol < 0) incol += ncols; // wrap
			else if (incol >= ncols) incol -= ncols;
			result[i][j] = data[i][incol];
		}
		return result;
	}
	
	LatLonGrid LatLonGrid::remapTo(LatLonGrid other)
	{
		LatLonGrid result = result.copyOf(other);
		result.setMissing(this->getMissing());
		for (int i = 0; i < other.getNumLat(); ++i) {
			int row = getRow(other.getLocation(i, 0));
			for (int j = 0; j < other.getNumLon(); ++j) {
				int col = getCol(other.getLocation(i, j));
				if (this->isValid(row, col)) {
					result.setValue(i, j, data[row][col]);
				}
				else {
					result.setValue(i, j, result.missing);
				}
			}
		}
		return result;
	}
}