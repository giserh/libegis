#pragma once

#include <algorithm>
#include <string>

namespace libegis {

	class ScalarStatistic
	{
	public:

		ScalarStatistic()
		{

		}

		~ScalarStatistic()
		{

		}

		void update(double x) {
			sumx += x;
			sumx2 += x*x;
			if (N == 0) {
				min = max = x;
			}
			else {
				min = fmin(min, x);
				max = fmax(max, x);
			}
			++N;
		}

		void update(const ScalarStatistic &other) {
			sumx += other.sumx;
			sumx2 += other.sumx2;
			if (N == 0) {
				min = other.min;
				max = other.max;
			}
			else if (other.N != 0) {
				min = fmin(min, other.min);
				max = fmax(max, other.max);
			}
			N += other.N;
		}

		double getMean() {
			compute();
			return mean;
		}

		double getMin() {
			return min;
		}

		double getMax() {
			return max;
		}

		double getVariance() {
			compute();
			return var;
		}

		double getStdDeviation() {
			compute();
			return stddev;
		}

		int getNumSamples() {
			return N;
		}

		std::string toString() {
			return "value = " + std::to_string(getMean()) + "+/-" + std::to_string(getStdDeviation()) + " based on " + std::to_string(N) + " samples";
		}

	private:
		double sumx = 0;
		double sumx2 = 0;
		int N = 0;
		int N_at_lastcompute = 0;
		double mean = 0;
		double var = 0;
		double stddev = 0;
		double min = 0;
		double max = 0;

		void compute() {
			if (N != N_at_lastcompute) { // N > 0 for this to ever happen
				mean = sumx / N;
				double meanx2 = sumx2 / N;
				// variance is really divided by N-1 to be unbiased, but okay
				var = meanx2 - mean*mean;
				if (var > 0) {
					stddev = sqrt(var);
				}
				else {
					stddev = 0;
				}
				N_at_lastcompute = N;
			}
		}
	};
}
