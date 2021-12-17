#include "ToyRobot.h"
#include <iostream> // std::cout
#include <string>
#include <sstream>

namespace
{
	constexpr int TABLE_W = 5;
	constexpr int TABLE_H = 5;
}

using enums::Direction;
using enums::RotateDir;

/**
 * @brief Construct a new Toy Robot:: Toy Robot object
 *        Initial position set to -1 to indicate that it has not yet been placed
 */
ToyRobot::ToyRobot()
: m_transform{Position{-1,-1}, Direction::NORTH}
{}

bool ToyRobot::place(const Transform& transform)
{
	if (transform.pos.x < 0
		|| transform.pos.y < 0
		|| transform.pos.x >= TABLE_W
		|| transform.pos.y >= TABLE_H)
	{
		// outside of table boundaries
		return false;
	}

	m_transform = transform;
	return true;
}

bool ToyRobot::isPlaced() const
{
	if (m_transform.pos.x == -1 && m_transform.pos.y == -1)
	{
		return false;
	}
	return true;
}

bool ToyRobot::rotate(const RotateDir& rotateDir)
{
	// ignore command if not placed
	if (!isPlaced())
	{
		return false;
	}

	int nextDirection = static_cast<int>(m_transform.dir);

	// increment/decrement with bounds checking
	if (rotateDir == RotateDir::RIGHT)
	{
		nextDirection = ++nextDirection > 3 ? 0 : nextDirection;
	}
	else
	{
		nextDirection = --nextDirection < 0 ? 3 : nextDirection;
	}

	m_transform.dir = static_cast<Direction>(nextDirection);

	return true;
}

bool ToyRobot::move()
{
	// ignore commands if not placed
	if (!isPlaced())
	{
		return false;
	}

	// create local copy to move and check before assigning to instance property
	Position pos = m_transform.pos;

	// process the movement
	switch (m_transform.dir)
	{
	case Direction::NORTH:
		++pos.y;
		break;
	case Direction::EAST:
		++pos.x;
		break;
	case Direction::SOUTH:
		--pos.y;
		break;
	case Direction::WEST:
		--pos.x;
		break;
	}

	// bounds checking
	if (pos.x < 0 ||
		pos.y < 0 ||
		pos.x >= TABLE_W ||
		pos.y >= TABLE_H)
	{
		return false;
	}

	// assign now that we have checked bounds
	m_transform.pos = pos;

	// success
	return true;
}


std::string ToyRobot::generateReport(int reportFlags) const
{
	std::stringstream out;

	if (!isPlaced())
	{
		if (reportFlags & ReportFlags::VERBOSE)
		{
			out << std::string{ "Toy robot has not yet been placed" } << std::endl;
		}
		return out.str();
	}

	const std::string& strDir = enums::toString(m_transform.dir);

	if (reportFlags | ReportFlags::TABLE_VIEW)
	{
		char robot = '\0';

		switch (m_transform.dir)
		{
		case Direction::NORTH:
			robot = '^';
			break;
		case Direction::EAST:
			robot = '>';
			break;
		case Direction::SOUTH:
			robot = 'v';
			break;
		case Direction::WEST:
			robot = '<';
			break;
		}

		// draw the robot on the table.
		if (reportFlags & ReportFlags::TABLE_VIEW)
		{
			for (int y = TABLE_H - 1; y >= 0; --y)
			{
				for (int x = 0; x < TABLE_W; ++x)
				{
					// add space between positions to account for terminal text generally being
					// twice as high as it is wide. 
					out << ' ';

					// draw the robot or draw an available space '.'
					if (x == m_transform.pos.x && y == m_transform.pos.y)
					{
						out << robot;
					}
					else
					{
						out << '.';
					}
				}
				out << '\n';
			}
		}

	}


	if (reportFlags & ReportFlags::TRANSFORM)
	{
		// output the report main requirement line for report
		out << m_transform.pos.x
			<< ","
			<< m_transform.pos.y
			<< ","
			<< strDir
			<< '\n';
	}


	// rely on compiler Return Value Optimastion here rather than explicit call to std::move
	return std::string{ out.str() };
}

void ToyRobot::report(int reportFlags) const
{
	std::cout << generateReport(reportFlags) << std::endl;
}

std::ostream& operator<<(std::ostream& os, const ToyRobot& tr)
{
	os << tr.generateReport(ToyRobot::ReportFlags::TRANSFORM);
	return os;
}