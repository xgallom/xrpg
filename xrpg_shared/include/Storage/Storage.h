 //
// Created by xgallom on 11. 2. 2019.
//

#ifndef XRPG_STORAGE_H
#define XRPG_STORAGE_H

#include "Save.h"
#include "Level.h"
#include "Util/Result.h"

namespace Storage
{
	using List = std::vector<std::string>;

	namespace Save {
		Result<List> list();
		bool store(const ::Save &save);
		Result<::Save> restore(const std::string &save);
	}

	namespace Level {
		bool store(const std::string &fileName, const ::Level &level);
		Result<::Level> restore(const std::string &fileName);
	}
}

#endif //XRPG_STORAGE_H
