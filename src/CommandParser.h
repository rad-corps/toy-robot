#pragma once

#include <string>     // std::string std::getline
#include "Transform.h"

class CommandParser
{
public:
	CommandParser() {}

	// remove default/assignment/move construction
	CommandParser(const CommandParser&) = delete;
	CommandParser(CommandParser&&) = delete;
	void operator=(const CommandParser&) = delete;
	void operator=(CommandParser&&) = delete;

	enums::Command parseCommand(const std::string& commandStr) const;
	bool parsePlaceCommand(const std::string& commandStr, Transform& out) const;

private:
};