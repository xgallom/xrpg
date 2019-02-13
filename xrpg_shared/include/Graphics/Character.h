//
// Created by xgallom on 2/13/19.
//

#ifndef XRPG_CHARACTER_H
#define XRPG_CHARACTER_H

#include "Color.h"

struct Character {
	using value_type = unsigned short;

	value_type value = 0;

	constexpr Character() = default;
	constexpr Character(char c, ColorAttribute ca)
			: value(static_cast<value_type>(c | (ca.value << 8)))
	{}

	constexpr bool operator!=(Character r) const { return value != r.value; }
};

#endif //XRPG_CHARACTER_H
