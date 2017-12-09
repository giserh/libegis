#pragma once

#include <string>

namespace libegis {

	class Pixel
	{
	public:
		Pixel() {}

		Pixel(int x, int y, int value)
		{
			this->x = x;
			this->y = y;
			this->value = value;
		}

		~Pixel() {}

		int getX()
		{
			return x;
		}

		int getY()
		{
			return y;
		}

		int getRow()
		{
			return x;
		}

		int getCol()
		{
			return y;
		}

		int getValue()
		{
			return value;
		}

		bool equals(Pixel &p) // original: public boolean equals(Object o) using "import java.util.Comparator;"
		{
			if (&p == this) {
				return true;
			}
			if (&p == NULL || !(p.equals(*this))) {
				return false;
			}
			Pixel other = (Pixel)p;
			return (other.x == x && other.y == y && other.value == value);
		}

		int getDistanceSquared(Pixel other)
		{
			return getDistanceSquared(other.x, other.y);
		}

		int getDistanceSquared(int otherx, int othery)
		{
			int distx = this->getX() - otherx;
			int disty = this->getY() - othery;
			return (distx*distx) + (disty*disty);
		}

		int compareLocation(Pixel a, Pixel other)
		{
			if (other.x == a.x) {
				return (a.y - other.y);
			}
			else {
				return (a.x - other.x);
			}
		}

		int compareValue(const Pixel &a, const Pixel &other)
		{
			return a.value - other.value;
		}

		int compareTo(const Pixel &other)
		{
			if (&other == NULL) {
				return 1;
			}
			if (other.value == value) {
				if (other.x == x) {
					return (y - other.y);
				}
				else {
					return (x - other.x);
				}
			}
			else {
				return value - other.value;
			}
		}
		std::string toString()
		{
			return "[" + std::to_string(x) + "," + std::to_string(y) + " " + std::to_string(value) + "]";
		}

	private:
		int x, y, value;
	};

}