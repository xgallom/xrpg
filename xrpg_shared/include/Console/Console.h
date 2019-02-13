//
// Created by xgallom on 10. 2. 2019.
//

#ifndef XRPG_CONSOLE_H
#define XRPG_CONSOLE_H

#include <Graphics/Color.h>
#include <Graphics/Coords.h>

#include <string>

namespace Console
{
	bool init();

	Coords size();

	Coords pos();
	void setPos(Coords coords);

	int get();
	std::string read(size_t max);

	void write(char c);
	void write(const char str[]);
	void write(const char *str, size_t size);

	void color(ColorAttribute colorAttribute);
}

#endif //XRPG_CONSOLE_H
