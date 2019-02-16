//
// Created by xgallom on 12. 2. 2019.
//

#include "LoadLevel.h"

#include "Context/GlobalContext.h"
#include "Quit.h"

#include <Console/ConsoleInput.h>
#include <Graphics/Border.h>
#include <Graphics/Message.h>
#include <Graphics/OutputBuffer.h>
#include <Storage/Storage.h>

#include <cstring>
#include <sstream>

namespace Run
{
	enum State {
		Loading = 0,
		Finished,
		Failed,

		Size
	};

	static constexpr char Text[Size][14] = {
			"Loading",
			"Load finished",
			"Load failed"
	};

	static int s_state = Loading;

	static void load();

	void LoadLevel::render()
	{
		border();

		switch(s_state) {
			case Loading : message(Text[Loading ], Color::LWhite); break;
			case Finished: message(Text[Finished], Color::LGreen); break;
			case Failed  : message(Text[Failed  ], Color::LRed  ); break;
		}
	}

	void LoadLevel::update()
	{
		switch(s_state) {
			case Loading:
				load();
				break;

			case Finished:
				Console::get();
				break;

			case Failed:
				Console::get();
				quit();
				break;
		}
	}

	void LoadLevel::transit()
	{
		GlobalContext::state() = GlobalState::LoadLevel;
		s_state = Loading;
	}


	static void load()
	{
		auto level = Storage::Level::restore("");

		if(level) {
			GlobalContext::map() = std::move(level().map);
			s_state = Finished;
		}
		else
			s_state = Failed;
	}
}
