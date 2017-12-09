#pragma once

#include <vector>
#include <cmath>

namespace libegis {

	class Remapper
	{
	public:
		static int nearestNeighbor(double rowno, double colno, std::vector< std::vector<int> > input, int missing)
		{
			const int row = (int)round(rowno);
			const int col = (int)round(colno);
			const int nrows = input.size();
			const int ncols = (nrows > 0) ? input[0].size() : 0;
			if (row >= 0 && col >= 0 && row < nrows && col < ncols) {
				return input[row][col];
			}
			else {
				return missing;
			}
		}

		static int bilinearInterpolation(double rowno, double colno, std::vector< std::vector<int> > input, int missing)
		{
			const int row0 = (int)floor(rowno);
			const int col0 = (int)floor(colno);
			const int row1 = (int)ceil(rowno);
			const int col1 = (int)ceil(colno);
			const int nrows = input.size();
			const int ncols = (nrows > 0) ? input[0].size() : 0;

			int npts = 0;
			double totwt = 0;
			double totval = 0;
			for (int row = row0; row <= row1; ++row) {
				for (int col = col0; col <= col1; ++col) {
					if (row >= 0 && col >= 0 && row < nrows && col < ncols && input[row][col] != missing) {
						double rowwt = 1 - abs(rowno - row);
						double colwt = 1 - abs(colno - col);
						double wt = rowwt * colwt;
						npts++;
						totwt += wt;
						totval += wt * input[row][col];
					}
				}
			}

			// weighted average
			if (npts == 0) {
				return missing;
			}
			else {
				return (int)round(totval / totwt);
			}
		}
	};
}