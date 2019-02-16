//
// Created by xgallom on 10. 2. 2019.
//

#include "Run.h"

#include "Context/GlobalContext.h"
#include "Editor.h"

#include <Graphics/OutputBuffer.h>
#include <Run/Dispatch.h>

namespace Run
{
	bool init()
	{
		return OutputBuffer::init();
	}

	bool run()
	{
		if(GlobalContext::state() != GlobalState::Quit)
			return dispatch<Editor>();

		return dispatchQuit();
	}

	void deinit()
	{
		OutputBuffer::deinit();
	}
}