//
// Created by xgallom on 2/15/19.
//

#ifndef XRPG_DISPATCH_H
#define XRPG_DISPATCH_H

#include "Graphics/OutputBuffer.h"

namespace Run
{
	template<typename T>
	static bool dispatch()
	{
		OutputBuffer::clear();
		T::render();
		OutputBuffer::update();

		T::update();

		return true;
	}

	inline bool dispatchQuit()
	{
		return false;
	}
}

#endif //XRPG_DISPATCH_H
