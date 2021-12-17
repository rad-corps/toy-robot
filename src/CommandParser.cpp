#include "CommandParser.h"
#include "Enums.h"
#include <iostream>

// anonymous namespace for this compilation unit only
namespace
{
	// return -1 for parse failures. 
	int stringToInteger(const std::string& str)
	{
		int ret = -1;
		try
		{
			ret = std::stoi(str);
		}
		catch (const std::invalid_argument& e)
		{
			std::cout << "Could not parse " << str << " to integer: " << e.what() << std::endl;
		}
		catch (const std::out_of_range& e)
		{
			std::cout << str << " out of range of integer bounds: " << e.what() << std::endl;
		}
		return ret;
	}
}

enums::Command CommandParser::parseCommand(const std::string& commandStr) const
{
	// check if this is a known command
	enums::Command ct;
	enums::toCommand(commandStr, ct);
	return ct;
}

bool CommandParser::parsePlaceCommand(const std::string& commandStr, Transform& out) const
{
	size_t strIdx;

	// verify the format of the command string
	const std::string& CMD_PLACE = enums::toString(enums::Command::PLACE);

	if (commandStr.find(CMD_PLACE) != 0 || commandStr[CMD_PLACE.size()] != ' ')
	{
		return false;
	}

	// single string containing all parameter commands
	std::string params = commandStr.substr(CMD_PLACE.size() + 1);

	// tokenise x parameter
	strIdx = params.find(",");
	const std::string x = params.substr(0, strIdx);
	params.erase(0, strIdx + 1);

	// tokenise y parameter
	strIdx = params.find(",");
	const std::string y = params.substr(0, strIdx);
	params.erase(0, strIdx + 1);

	// tokenise direction parameter
	const std::string direction = params;

	// stringToInteger will return a -1 if there was an issue with parsing
	out.pos.x = stringToInteger(x);
	out.pos.y = stringToInteger(y);

	// stringToInteger returns a -1 on parse failures. 
	if (out.pos.x == -1 || out.pos.y == -1)
	{
		return false;
	}
	enums::Direction tempDir;
	if (enums::toDirection(direction, tempDir))
	{
		out.dir = tempDir;
	}
	else
	{
		// invalid direction
		std::cout << "Could not parse direction: " << direction << '\n';
		return false;
	}
	return true;
}