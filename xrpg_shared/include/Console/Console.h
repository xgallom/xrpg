//
// Created by xgallom on 10. 2. 2019.
//

#ifndef XRPG_CONSOLE_H
#define XRPG_CONSOLE_H

#include "ConsoleInput.h"

#include <Graphics/Color.h>
#include <Graphics/Coords.h>

namespace Console
{
	bool init();
	void deinit();

	Coords size();

	Coords pos();
	void setPos(Coords coords);

	void cls();
	void flush();

	void write(char c);
	void write(const char str[]);
	void write(const char *str, size_t size);

	void color(ColorAttribute colorAttribute);
}

#endif //XRPG_CONSOLE_H
