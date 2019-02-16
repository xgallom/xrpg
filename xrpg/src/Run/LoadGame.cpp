//
// Created by xgallom on 11. 2. 2019.
//

#include "LoadGame.h"

#include "Context/GlobalContext.h"
#include "MainMenu.h"
#include "Quit.h"
#include "LoadLevel.h"

#include <Console/ConsoleInput.h>
#include <Graphics/Border.h>
#include <Graphics/Input.h>
#include <Graphics/Message.h>
#include <Graphics/OutputBuffer.h>
#include <Storage/Storage.h>

#include <cstring>

namespace Run
{
	enum State {
		Listing = 0,
		ListingFailed,
		LoadingFailed,
		Empty,

		Accept,
		Cancel,

		Size
	};
	static constexpr auto First = Accept, Last = Cancel;

	static constexpr size_t TextSize = 24;

	static constexpr char Text[Size][TextSize] = {
			"Reading directory",
			"Error reading directory",
			"Error loading save file",
			"No saved games",

			"         Accept        ",
			"         Cancel        "
	};

	static int s_state = First;
	static size_t s_selection = 0;
	Storage::List s_saves;

	static void renderUi();
	static void list();
	static void updateUi();
	static void handle();
	static void load(const std::string &save);

	void LoadGame::render()
	{
		border();

		switch(s_state) {
			case Listing      : message(Text[Listing      ], Color::LWhite ); break;
			case ListingFailed: message(Text[ListingFailed], Color::LRed   ); break;
			case LoadingFailed: message(Text[LoadingFailed], Color::LRed   ); break;
			case Empty        : message(Text[Empty        ], Color::LYellow); break;

			default: renderUi(); break;
		}
	}

	void LoadGame::update()
	{
		switch(s_state) {
			case Listing:
				list();
				break;

			case ListingFailed:
			case Empty:
			case LoadingFailed:
				Console::get();
				MainMenu::transit();
				break;

			default:
				updateUi();
				break;
		}
	}

	void LoadGame::transit()
	{
		GlobalContext::state() = GlobalState::LoadGame;
		s_state = First;
		s_selection = 0;
	}

	static void renderUi()
	{
		const auto screenSize = OutputBuffer::size();
		const auto screenCenter = static_cast<Coords::value_type>(screenSize.x / 2);

		const auto
			tl = Coords{2, 1},
			bc = Coords{0, static_cast<Coords::value_type>(screenSize.y - 3)} +
				 Coords{center(screenCenter, TextSize), 0};

		border({{0, 0}, screenSize - Coords{0, 4}});

		Coords::value_type n = 0;
		for(const auto &save : s_saves) {
			write(tl + Coords{0, n}, n == s_selection ? Color::LBlue : Color::White, save.c_str(), save.size());
			++n;
		}

		Input::button(
			bc,
			s_state == Accept ? Color::LWhite : Color::White,
			Text[Accept],
			strlen(Text[Accept])
		);
		Input::button(
			bc + Coords{screenCenter, 0},
			s_state == Cancel ? Color::LWhite : Color::White,
			Text[Cancel],
			strlen(Text[Cancel])
		);
	}

	static void list()
	{
		auto result = Storage::Save::list();

		if(result) {
			s_saves = std::move(result());

			if(!s_saves.empty())
				s_state = Accept;
			else
				s_state = Empty;
		}
		else
			s_state = ListingFailed;
	}

	static void updateUi()
	{
		const auto c = Console::get();

		switch(c) {
			case '2':
			case 's':
				if(s_selection < s_saves.size() - 1)
					++s_selection;
				break;

			case '8':
			case 'w':
				if(s_selection > 0)
					--s_selection;
				break;

			case '4':
			case 'a':
				if(s_state == Cancel)
					s_state = Accept;
				break;

			case '6':
			case 'd':
				if(s_state == Accept)
					s_state = Cancel;
				break;

			case '5':
			case '\n':
			case '\r':
				handle();
				break;
		}
	}

	static void handle()
	{
		switch(s_state) {
			case Accept:
				load(s_saves[s_selection]);
				break;

			case Cancel:
				MainMenu::transit();
				break;
		}
	}

	static void load(const std::string &save)
	{
		auto result = Storage::Save::restore(save);

		if(result) {
			GlobalContext::player() = result().player;

			LoadLevel::transit();
		}
		else
			s_state = LoadingFailed;
	}
}
