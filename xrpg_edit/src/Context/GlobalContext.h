//
// Created by xgallom on 10. 2. 2019.
//

#ifndef XRPG_GLOBALCONTEXT_H
#define XRPG_GLOBALCONTEXT_H

#include <Graphics/Coords.h>
#include <Util/Flag.h>

#include <string>

namespace GlobalState
{
	enum Enum {
		Editor = 0,
		Menu,
		NewMap,
		SaveMap,
		OpenMap,

		Quit
	};
}

class Map;

namespace GlobalContext
{
	GlobalState::Enum &state();
	Map &map();
	Coords &pos();
	std::string &fileName();
}

#endif //XRPG_GLOBALCONTEXT_H
