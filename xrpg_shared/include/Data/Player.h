//
// Created by xgallom on 11. 2. 2019.
//

#ifndef XRPG_PLAYER_H
#define XRPG_PLAYER_H

#include "Stats.h"
#include "Attributes.h"

#include <string>

static constexpr attribute
	AttribMin = 8,
	AttribMax = 18,
	AttribDefault = 10,
	AttribWeak = 9,
	AttribStrong = 16;

struct Player {
	std::string name = std::string{};

	Stat
		hp = Stat{},
		xp = Stat{};

	Attributes attrib = Attributes{AttribDefault, AttribDefault, AttribDefault};
};

#endif //XRPG_PLAYER_H
