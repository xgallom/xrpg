//
// Created by xgallom on 2/13/19.
//

#ifndef XRPG_MAP_H
#define XRPG_MAP_H

#include "Graphics/Character.h"
#include "Graphics/Coords.h"

#include <vector>

struct Map {
	Coords size = {};

	std::vector<Character> data = std::vector<Character>{};

	Map() = default;
	explicit Map(Coords a_size) : size(a_size) { data.resize(a_size.area()); }

	inline const Character &at(Coords pos) const { return data[static_cast<size_t>(pos.y) * size.y + pos.x]; }
	inline Character &at(Coords pos) { return data[static_cast<size_t>(pos.y) * size.y + pos.x]; }
};

#endif //XRPG_MAP_H
