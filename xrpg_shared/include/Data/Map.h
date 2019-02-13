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
};

#endif //XRPG_MAP_H
