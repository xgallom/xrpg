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
#include <Run/Dispatch.h>

namespace Run
{
	bool init()
	{
		return OutputBuffer::init({80, 25});
	}

	bool run()
	{
		static constexpr bool (* const runTable[GlobalState::Size]) (void) = {
				&dispatch<MainMenu >,
				&dispatch<NewGame  >,
				&dispatch<LoadGame >,
				&dispatch<LoadLevel>,
				&dispatchQuit
		};

		return (*runTable[GlobalContext::state()])();
	}

	void deinit()
	{
		OutputBuffer::deinit();
	}
}