#include <string>
#include "Pixel.h"

namespace libegis {

	Pixel::Pixel()
	{
	}

	Pixel::Pixel(int x, int y, int value)
	{
		this->x = x;
		this->y = y;
		this->value = value;
	}

	Pixel::~Pixel()
	{
	}

	int Pixel::getX()
	{
		return x;
	}

	int Pixel::getY()
	{
		return y;
	}

	int Pixel::getRow()
	{
		return x;
	}

	int Pixel::getCol()
	{
		return y;
	}

	int Pixel::getValue()
	{
		return value;
	}

	int Pixel::getDistanceSquared(Pixel other) {
		return getDistanceSquared(other.x, other.y);
	}

	int Pixel::getDistanceSquared(int otherx, int othery) {
		int distx = this->getX() - otherx;
		int disty = this->getY() - othery;
		return (distx*distx) + (disty*disty);
	}

	int Pixel::compareLocation(Pixel a, Pixel other)
	{
		if (other.x == a.x) {
			return (a.y - other.y);
		}
		else {
			return (a.x - other.x);
		}
	}

	int Pixel::compareValue(Pixel a, Pixel other)
	{
		return a.value - other.value;
	}

	int Pixel::compareTo(Pixel other)
	{
		// TODO: check if "other == null" (Java) really can be implemented as "sizeof(other) == 0"
		if (sizeof(other) == 0) {
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

	std::string Pixel::toString()
	{
		std::string result = "[" + std::to_string(x) + "," + std::to_string(y) + " " + std::to_string(value) + "]";
		return result;
	}
}