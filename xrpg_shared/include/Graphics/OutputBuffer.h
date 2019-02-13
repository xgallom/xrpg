//
// Created by xgallom on 10. 2. 2019.
//

#ifndef XRPG_OUTPUT_BUFFER_H
#define XRPG_OUTPUT_BUFFER_H

#include "Coords.h"
#include "Color.h"

#include <cstddef>

struct Character {
	using value_type = unsigned short;

	value_type value = 0;

	constexpr Character() = default;
	constexpr Character(char c, ColorAttribute ca)
		: value(static_cast<value_type>(c | (ca.value << 8)))
	{}

	constexpr bool operator!=(Character r) const { return value != r.value; }
};

namespace OutputBuffer
{
	static const constexpr Coords Size = {80, 25};

	bool init();

	void clear();
	void update();

	Character &at(size_t index);
	Character &at(Coords coords);
}


void write(Coords pos, Character ch);
void write(Coords pos, Character *ch, size_t size);
void write(Coords pos, ColorAttribute ca, const char *str, size_t size);

constexpr Coords center(Coords coords) { return center(OutputBuffer::Size, coords); }

#endif //XRPG_OUTPUT_BUFFER_H
