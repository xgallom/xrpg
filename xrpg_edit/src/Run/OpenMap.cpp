//
// Created by xgallom on 2/16/19.
//

#include "OpenMap.h"

#include "FileNamePrompt.h"

namespace Run
{
	struct OpenMapPrompt : public FileNamePrompt<OpenMapPrompt> {
		static constexpr char ErrorText[] = "Error opening file";

		static bool handleAccept(const std::string &fileName)
		{
			auto level = Storage::Level::restore(fileName);

			if(!level)
				return false;

			GlobalContext::map() = std::move(level().map);

			return true;
		}
	};

	void OpenMap::render()      { OpenMapPrompt::render();  }
	void OpenMap::update(int c) { OpenMapPrompt::update(c); }
	void OpenMap::transit()
	{
		GlobalContext::state() = GlobalState::OpenMap;
		OpenMapPrompt::transit();
	}
}
