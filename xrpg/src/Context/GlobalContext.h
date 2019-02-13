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
		Load,
		Quit,

		Size
	};
}

class Player;

namespace GlobalContext
{
	GlobalState::Enum &state();
	Player &player();
}

#endif //XRPG_GLOBALCONTEXT_H
