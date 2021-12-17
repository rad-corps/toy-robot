#pragma once

#include "Enums.h"

/**
 * @brief Position represented by two ints. 
  */
struct Position
{
	int x;
	int y;

	Position() 
	: x{0}, y{0} {}

	Position(int x_, int y_) 
	: x{x_}, y{y_} {}

	bool operator==(const Position& compare) const
	{
		return compare.x == x && compare.y == y;
	}
};

/**
 * @brief A container for a position and direction
 */
struct Transform
{
	Position pos;
	enums::Direction dir;
	Transform()	: pos{}, dir{} {}
	Transform(const Position& pos_, const enums::Direction& dir_)
	: pos{pos_}, dir{dir_} {}

	bool operator==(const Transform& compare) const
	{
		return compare.pos == pos && compare.dir == dir;
	}
};

std::ostream& operator<<(std::ostream& os, const Position& pos);
std::ostream& operator<<(std::ostream& os, const Transform& tr);