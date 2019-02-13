//
// Created by xgallom on 2/13/19.
//

#include "Console/Console.h"
#include <cstring>

namespace Console
{
	void write(char c)
	{
		write(&c, 1);
	}

	void write(const char str[])
	{
		write(str, strlen(str));
	}

	std::string read(size_t max)
	{
		std::string input;

		write('\xdb');

		for(;;) {
			const auto c = get();

			switch(c) {
				case '\n':
				case '\r':
					return input;

				case '\b':
				case '\x7f':
					if(!input.empty()) {
						write("\b \b\b\xdb");
						input.pop_back();
					}

					break;

				default:
					if(input.size() < max) {
						char str[] = "\b \xdb";
						str[1] = static_cast<char>(c);

						write(str);

						input.push_back(static_cast<char>(c));
					}

					break;
			}
		}
	}
}
