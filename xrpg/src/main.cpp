//
// Created by xgallom on 2/13/19.
//

#include "Run/Run.h"

#include <iostream>
#include <vector>

static std::vector<std::string> createArguments(int argc, char *argv[])
{
	/* Remove program name from arguments */
	--argc;
	++argv;

	std::vector<std::string> arguments;
	arguments.reserve(static_cast<size_t>(argc));

	while(argc--)
		arguments.emplace_back(*argv++);

	return arguments;
}

int main(int argc, char *argv[])
{
	if(const auto arguments = createArguments(argc, argv); !Run::init(arguments)) {
		std::cerr << "Error initializing application\n";
		std::cerr.flush();

		return EXIT_FAILURE;
	}

	while(Run::run()) {}

	Run::deinit();
	std::cerr.flush();

	return EXIT_SUCCESS;
}
