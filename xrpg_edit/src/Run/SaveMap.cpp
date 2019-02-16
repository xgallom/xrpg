//
// Created by xgallom on 2/16/19.
//

#include "SaveMap.h"

#include "FileNamePrompt.h"

namespace Run
{
	struct SaveMapPrompt : public FileNamePrompt<SaveMapPrompt> {
		static constexpr char ErrorText[] = "Error saving file";

		static bool handleAccept(const std::string &fileName)
		{
			return Storage::Level::store(fileName, {GlobalContext::map()});
		}
	};

	void SaveMap::render()      { SaveMapPrompt::render();  }
	void SaveMap::update(int c) { SaveMapPrompt::update(c); }
	void SaveMap::transit()
	{
		GlobalContext::state() = GlobalState::SaveMap;
		SaveMapPrompt::transit();
	}
}
