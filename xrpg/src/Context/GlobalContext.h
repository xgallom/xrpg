//
// Created by xgallom on 10. 2. 2019.
//

#ifndef XRPG_GLOBALCONTEXT_H
#define XRPG_GLOBALCONTEXT_H

namespace GlobalState
{
	enum Enum {
		MainMenu = 0,
		NewGame,
		LoadGame,
		Settings,
		LoadLevel,
		Quit,

		Size
	};
}

class Player;
class Map;

namespace GlobalContext
{
	GlobalState::Enum &state();
	Player &player();
	Map &map();
}

#endif //XRPG_GLOBALCONTEXT_H
