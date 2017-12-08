#pragma once

#include <string>

namespace libegis {

	class Pixel
	{
	public:
		Pixel();
		Pixel(int x, int y, int value);
		~Pixel();

		int getX();
		int getY();
		int getRow();
		int getCol();
		int getValue();
		// bool equals(Pixel p); // original: public boolean equals(Object o) using "import java.util.Comparator;"
		int getDistanceSquared(Pixel other);
		int getDistanceSquared(int otherx, int othery);
		int compareLocation(Pixel a, Pixel other);
		int compareValue(Pixel a, Pixel other);
		int compareTo(Pixel other);
		std::string toString();

	private:
		int x, y, value;
	};

}