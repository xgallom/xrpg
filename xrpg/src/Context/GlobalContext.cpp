//
// Created by xgallom on 10. 2. 2019.
//

#include "GlobalContext.h"

#include <Data/Player.h>

namespace GlobalContext
{
	GlobalState::Enum &state()
	{
		static GlobalState::Enum s_value = GlobalState::MainMenu;

		return s_value;
	}

	Player &player()
	{
		static Player s_player = Player{};

		return s_player;
	}
}
