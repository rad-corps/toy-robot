#include "Enums.h"
#include <map>
#include <memory>
#include <iostream>

namespace
{
	using enums::Command;
	using enums::Direction;
	
	const std::map<Command, std::string> m_commandToString =
	{
		{Command::PLACE, "PLACE"},
		{Command::MOVE, "MOVE"},
		{Command::LEFT, "LEFT"},
		{Command::RIGHT, "RIGHT"},
		{Command::REPORT, "REPORT"},
		{Command::HELP, "HELP"},
		{Command::QUIT, "QUIT"},
		{Command::INVALID_COMMAND, "INVALID_COMMAND"}
	};

	const std::map<Direction, std::string> m_directionToString =
	{
		{Direction::NORTH, "NORTH"},
		{Direction::EAST, "EAST"},
		{Direction::SOUTH, "SOUTH"},
		{Direction::WEST, "WEST"},
	};
}

namespace enums
{
	const std::string& toString(const Command& ct)
	{
		return m_commandToString.at(ct);
	}
	const std::string& toString(const Direction& dir)
	{
		return m_directionToString.at(dir);
	}
	bool toCommand(const std::string& strCommand, Command& out)
	{
		out = Command::INVALID_COMMAND;
		for (auto iter = m_commandToString.cbegin(); iter != m_commandToString.cend(); ++iter)
		{
			// don't match the whole command, just the beggining of it
			if (strCommand.find(iter->second) == 0)
			{
				out = iter->first;
				return true;
			}
		}
		return false;
	}
	bool toDirection(const std::string& strDir, Direction& out)
	{
		for (auto iter = m_directionToString.cbegin(); iter != m_directionToString.cend(); ++iter)
		{
			if (strDir == iter->second)
			{
				out = iter->first;
				return true;
			}
		}
		return false;
	}
}

std::ostream& operator<<(std::ostream& os, const enums::Direction& dir)
{
	os << enums::toString(dir);
	return os;
}