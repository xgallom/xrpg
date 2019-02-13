//
// Created by xgallom on 10. 2. 2019.
//

#include "Run.h"

#include "MainMenu.h"
#include "NewGame.h"
#include "LoadGame.h"
#include "LoadLevel.h"

#include "Context/GlobalContext.h"

#include <Graphics/OutputBuffer.h>

namespace Run
{
	bool init()
	{
		return OutputBuffer::init({80, 25});
	}

	template<typename T>
	static bool run()
	{
		OutputBuffer::clear();
		T::render();
		OutputBuffer::update();

		T::update();

		return true;
	}

	static bool quit()
	{
		return false;
	}

	bool run()
	{
		static constexpr bool (* const runTable[GlobalState::Size]) (void) = {
				&run<MainMenu >,
				&run<NewGame  >,
				&run<LoadGame >,
				&run<LoadLevel>,
				&quit
		};

		return (*runTable[GlobalContext::state()])();
	}

	void deinit()
	{
		OutputBuffer::deinit();
	}
}