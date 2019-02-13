//
// Created by xgallom on 12. 2. 2019.
//

#include "LoadLevel.h"

#include <Console/ConsoleInput.h>
#include <Graphics/Border.h>
#include <Graphics/OutputBuffer.h>
#include <Storage/Storage.h>

#include <sstream>
#include <cstring>

namespace Run
{
	enum Index {
		Initializing = 0,
		Loading,
		Finished,

		Size
	};

	void LoadLevel::render()
	{
		border();

		return;
		const auto level = Storage::Level::restore();

		if(level) {
			std::stringstream ss;
			ss << level().map.size.x << " " << level().map.size.y;

			write({0, 0}, Color::LWhite, ss.str().c_str(), ss.str().size());
		}
		else
			write({0, 0}, Color::LWhite, "Load failed.", strlen("Load failed."));
	}

	void LoadLevel::update()
	{
		//Console::get();
	}
}
