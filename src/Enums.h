#pragma once

#include <string>
/**
 * @brief Namespace the enums and enum helper functions as they are somewhat ambiguous
 *        without namespace context. A Command could be a class and the toString overloads
 *        make more sense with enums::toString namespace context
 */
namespace enums
{
	/**
	 * @brief Command enum represent a command issued by the application user
	 */
	enum class Command
	{
		PLACE,
		MOVE,
		LEFT,
		RIGHT,
		REPORT,
		HELP,
		QUIT,
		INVALID_COMMAND
	};

	/**
	 * @brief Direction enum represents the heading of the robot as 4 discreet directions
	 *        Explicitly defining these as a integers between 0-3 to allow overflow wrapping
	 */
	enum class Direction
	{
		NORTH = 0,
		EAST = 1,
		SOUTH = 2,
		WEST = 3
	};

	/**
	 * @brief RotateDir represents a rotation direction. 
	 * LEFT: anti-clockwise
	 * RIGHT: clockwise
	 */
	enum class RotateDir
	{
		LEFT,
		RIGHT
	};

	// enum to string converters
	const std::string& toString(const Command& ct);
	const std::string& toString(const Direction& ct);

	/**
	 * @brief Convert command string to Command enum
	 * 
	 * @param command user input command to attempt to match to a command enum
	 * @param out resultant enum assigned to out value
	 * @return true on success
	 * @return false on failure
	 */
	bool toCommand(const std::string& command, Command& out);

	/**
	 * @brief Convert direction string to Direction enum
	 * 
	 * @param direction Direction as a string
	 * @param out resultant Direction enum assigned to out value
	 * @return true on success
	 * @return false on failure
	 */
	bool toDirection(const std::string& direction, Direction& out);
}

std::ostream& operator<<(std::ostream& os, const enums::Direction& dir);
std::ostream& operator<<(std::ostream& os, const enums::Command& com);
