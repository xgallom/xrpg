#include "Run/Run.h"

#include <iostream>

int main()
{
	if(!Run::init()) {
		std::cerr << "Error initializing Console\n";
		return EXIT_FAILURE;
	}

	while(Run::run()) {}

	return EXIT_SUCCESS;
}
