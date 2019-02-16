//
// Created by xgallom on 11. 2. 2019.
//

#ifndef XRPG_INPUT_H
#define XRPG_INPUT_H

#include "Coords.h"
#include "Color.h"

#include <cstddef>
#include <string>

namespace Input
{
	void text(Coords pos, ColorAttribute promptColor, ColorAttribute valueColor, const char prompt[],
			  size_t promptSize, const std::string &value);

	void slider(Coords pos, ColorAttribute promptColor, ColorAttribute valueColor, const char prompt[],
			    size_t promptSize, size_t strSize, int value, int min, int max);

	void integer(Coords pos, ColorAttribute promptColor, ColorAttribute valueColor, const char prompt[],
				 size_t promptSize, int value);

	void button(Coords pos, ColorAttribute color, const char text[], size_t textSize);
}

#endif //XRPG_INPUT_H
