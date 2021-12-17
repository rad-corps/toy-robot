
#include <iostream>   // std::cout std::cin
#include <cstring>    // strcmp
#include <cassert>    // assert
#include <fstream>    // std::ifstream

#include "ToyRobot.h"
#include "applicationLoop.h"
#include "unitTests.h"

/**
 * @brief Application entry point. 
 *        If optional filename is supplied, a filestream is supplied
 *        to appLoop. Otherwise std::cin is supplied to appLoop
 */
int main(int argc, char** argv)
{
	std::cout
		<< "||=======================================||\n"
		<< "|| Toy Robot Application by Adam Hulbert ||\n"
		<< "||=======================================||\n"
		<< "Type HELP for a list of commands\n";

	// generic mode, no command line parameter sent in, lets just use std::cin for input
	if (argc <= 1)
	{
		app::appLoop(&std::cin);
	}

	// pick our run mode based on the supplied command line parameters
	for (int i = 0; i < argc; ++i)
	{
		if (strcmp(argv[i], "-run-unit-tests") == 0)
		{
			unit_tests::run();
			break;
		}
		else if (strcmp(argv[i], "-file") == 0)
		{
			// next array element should be the file name, but we need to make sure its available
			if (i != argc - 1)
			{
				std::ifstream fileStream{ argv[i+1] };
				assert(fileStream.is_open());
				app::appLoop(&fileStream);
				break;
			}
			else
			{
				std::cerr << "File flag supplied but file name not supplied" << std::endl;
			}
		}
	}

	std::cout << "Press ENTER to exit application" << std::endl;
	std::cin.get();
	return 0;
}