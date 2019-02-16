//
// Created by xgallom on 10. 2. 2019.
//

#include "MainMenu.h"

#include "Context/GlobalContext.h"
#include "LoadGame.h"
#include "NewGame.h"
#include "Quit.h"

#include <Console/ConsoleInput.h>
#include <Graphics/Menu.h>

namespace Run
{
	enum Index {
		NewGame = 0,
		LoadGame,
		Quit,

		Size
	};

	static constexpr auto First = NewGame, Last = Quit;

	static constexpr Menu<Size, 9> MainMenuMenu = {
			"New Game ",
			"Load Game",
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
		switch(Console::get()) {
			case '8':
			case 'w':
				if(s_activeIndex > First)
					--s_activeIndex;
				break;

			case '2':
			case 's':
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
			case Quit:     quit();     break;

			default:       return;
		}
	}
}
