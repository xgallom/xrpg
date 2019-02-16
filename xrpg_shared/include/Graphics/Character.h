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

	constexpr char ch() const { return static_cast<char>(value & 0xff); }
	constexpr ColorAttribute ca() const { return value >> 8; }

	void setCh(char c) { value = static_cast<value_type>(c) | (value & static_cast<value_type>(0xff00)); }
	void setCa(ColorAttribute ca) {value = (value & static_cast<value_type>(0x00ff)) | (static_cast<value_type>(ca.value) << 8); }
};

#endif //XRPG_CHARACTER_H
