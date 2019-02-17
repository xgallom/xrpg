//
// Created by xgallom on 10. 2. 2019.
//

#ifndef XRPG_RUN_H
#define XRPG_RUN_H

#include <vector>
#include <string>

using Arguments = std::vector<std::string>;

namespace Run
{
	bool init(const Arguments &arguments);
	bool run();
	void deinit();
}

#endif //XRPG_RUN_H
