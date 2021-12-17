#include "Enums.h"
#include <map>
#include <memory>
#include <iostream>

namespace
{
	const std::map<enums::Command, std::string> m_commandToString =
	{
		{enums::Command::PLACE, "PLACE"},
		{enums::Command::MOVE, "MOVE"},
		{enums::Command::LEFT, "LEFT"},
		{enums::Command::RIGHT, "RIGHT"},
		{enums::Command::REPORT, "REPORT"},
		{enums::Command::HELP, "HELP"},
		{enums::Command::QUIT, "QUIT"},
		{enums::Command::INVALID_COMMAND, "INVALID_COMMAND"}
	};

	const std::map<enums::Direction, std::string> m_directionToString =
	{
		{enums::Direction::NORTH, "NORTH"},
		{enums::Direction::EAST, "EAST"},
		{enums::Direction::SOUTH, "SOUTH"},
		{enums::Direction::WEST, "WEST"},
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