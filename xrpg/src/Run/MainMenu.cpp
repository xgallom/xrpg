//
// Created by xgallom on 10. 2. 2019.
//

#include "MainMenu.h"

#include "Context/GlobalContext.h"
#include "NewGame.h"
#include "LoadGame.h"
#include "Settings.h"
#include "Quit.h"

#include <Console/ConsoleInput.h>
#include <Graphics/Menu.h>

namespace Run
{
	enum Index {
		NewGame = 0,
		LoadGame,
		Settings,
		Quit,

		Size
	};

	static constexpr auto First = NewGame, Last = Quit;

	static constexpr Menu<Size, 9> MainMenuMenu = {
			"New Game ",
			"Load Game",
			"Settings ",
			"Quit     "
	};

	static int s_activeIndex = First;

	static void handle();

	void MainMenu::render()
	{
		border();
		MainMenuMenu.renderCenter(s_activeIndex);
	}

	void MainMenu::update()
	{
		switch(Console::getAsync()) {
			case '8':
			case 'w':
			case '<':
				if(s_activeIndex > First)
					--s_activeIndex;
				break;

			case '2':
			case 's':
			case '>':
				if(s_activeIndex < Last)
					++s_activeIndex;
				break;

			case '5':
			case '\n':
			case '\r':
				handle();
				break;

			default:
				break;
		}
	}

	void MainMenu::transit()
	{
		GlobalContext::state() = GlobalState::MainMenu;
	}

	static void handle()
	{
		switch(s_activeIndex) {
			case NewGame:  NewGame::transit();  break;
			case LoadGame: LoadGame::transit(); break;
			case Settings: Settings::transit(); break;
			case Quit:     quit();     break;

			default:       return;
		}
	}
}
