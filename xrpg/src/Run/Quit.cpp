//
// Created by xgallom on 2/13/19.
//

#include "Quit.h"

#include "Context/GlobalContext.h"

namespace Run
{
	void quit()
	{
		GlobalContext::state() = GlobalState::Quit;
	}
}
