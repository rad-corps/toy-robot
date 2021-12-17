#include "applicationLoop.h"
#include "CommandParser.h"
#include "ToyRobot.h"

namespace app
{
	/**
	 * @brief Run the main application loop
	 *         - wait for command
	 *         - parse command
	 *         - execute command
	 * @param input a std::istream* this could be a file stream or std::cin
	 *              depending on how the application was started
	 */
	void appLoop(std::istream* input)
	{
		const CommandParser parser;
		ToyRobot robot;
		bool run = true;

		while (run)
		{
			// get user input
			std::string userInput;
			std::cout << "\n$ ";
			std::getline(*input, userInput);

			if (userInput == "")
			{
				run = false;
				break;
			}

			// force input to upper case to be leniant on input entered as lowercase.
			for (char& c : userInput)
			{
				// the std::transform ::toupper method generates an
				// int to char loss-of-data truncation warning.
				// little workaround to prevent compiler level 4 warning.
				c = static_cast<char>(std::toupper(c));
			}

			const enums::Command ct = parser.parseCommand(userInput);

			// echo the command. Particularly useful when running from file.
			std::cout << enums::toString(ct) << '\n';

			switch (ct)
			{
			case enums::Command::PLACE:
			{
				Transform transform;
				if (parser.parsePlaceCommand(userInput, transform))
				{
					std::cout
						<< transform.pos.x
						<< ','
						<< transform.pos.y
						<< ','
						<< enums::toString(transform.dir)
						<< '\n';

					robot.place(transform);
				}
			}break;
			case enums::Command::MOVE:
				robot.move();
				break;
			case enums::Command::LEFT:
				robot.rotate(enums::RotateDir::LEFT);
				break;
			case enums::Command::RIGHT:
				robot.rotate(enums::RotateDir::RIGHT);
				break;
			case enums::Command::REPORT:
				robot.report();
				break;
			case enums::Command::HELP:
				std::cout
					<< "Available Commands:\n"
					<< "   PLACE {X},{Y},{DIRECTION}\n"
					<< "   MOVE\n"
					<< "   LEFT\n"
					<< "   RIGHT\n"
					<< "   REPORT\n"
					<< "   QUIT\n";
				break;
			case enums::Command::QUIT:
				run = false;
				break;
			case enums::Command::INVALID_COMMAND:
				std::cout << "Could not parse command. Type \"HELP\"\n";
				break;
			}
		}
	}
}
