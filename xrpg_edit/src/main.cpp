//
// Created by xgallom on 2/15/19.
//

#include "Run/Run.h"

#include <iostream>

int main()
{
	if(!Run::init()) {
		std::cerr << "Error initializing Console\n";
		return EXIT_FAILURE;
	}

	while(Run::run()) {}

	Run::deinit();

	return EXIT_SUCCESS;
}
