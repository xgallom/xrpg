//
// Created by xgallom on 10. 2. 2019.
//

#include "GlobalContext.h"

#include <Data/Player.h>
#include <Data/Map.h>

namespace GlobalContext
{
	GlobalState::Enum &state()
	{
		static GlobalState::Enum s_value = GlobalState::Editor;

		return s_value;
	}

	Player &player()
	{
		static Player s_player = Player{};

		return s_player;
	}

	Map &map()
	{
		static Map s_map = Map{};

		return s_map;
	}

	std::string &fileName()
	{
		static std::string s_fileName = {};

		return s_fileName;
	}
}
