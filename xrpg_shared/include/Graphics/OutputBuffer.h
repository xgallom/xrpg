//
// Created by xgallom on 10. 2. 2019.
//

#ifndef XRPG_OUTPUT_BUFFER_H
#define XRPG_OUTPUT_BUFFER_H

#include "Character.h"
#include "Coords.h"
#include "Color.h"

#include <cstddef>

namespace OutputBuffer
{
	bool init(Coords size = {});
	void deinit();

	void clear();
	void clear(Region region);
	void update();

	Coords size();

	Character &at(size_t index);
	Character &at(Coords coords);
}


void write(Coords pos, Character ch);
void write(Coords pos, Character *ch, size_t size);
void write(Coords pos, ColorAttribute ca, const char *str, size_t size);

inline Coords center(Coords coords) { return center(OutputBuffer::size(), coords); }

#endif //XRPG_OUTPUT_BUFFER_H
