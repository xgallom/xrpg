//
// Created by xgallom on 10. 2. 2019.
//

#include "Run.h"

#include "MainMenu.h"
#include "NewGame.h"
#include "LoadGame.h"
#include "Load.h"

#include "Context/GlobalContext.h"

#include <Graphics/OutputBuffer.h>

namespace Run
{
	bool init()
	{
		return OutputBuffer::init();
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
				&run<MainMenu>,
				&run<NewGame >,
				&run<LoadGame>,
				&run<Load    >,
				&quit
		};

		return (*runTable[GlobalContext::state()])();
	}
}