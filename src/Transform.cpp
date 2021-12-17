#include "Transform.h"
#include <iostream>

std::ostream& operator<<(std::ostream& os, const Position& pos)
{
	os << "x: " << pos.x << ", y: " << pos.y;
	return os;
}

std::ostream& operator<<(std::ostream& os, const Transform& tr)
{
	os << "position: {"
		<< tr.pos
		<< "}, direction: "
		<< enums::toString(tr.dir);
	return os;
}