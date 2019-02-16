//
// Created by xgallom on 2/16/19.
//

#ifndef XRPG_NEWMAP_H
#define XRPG_NEWMAP_H

namespace Run
{
	struct NewMap {
		static void render();
		static void update(int c);
		static void transit();
	};
}

#endif //XRPG_NEWMAP_H
