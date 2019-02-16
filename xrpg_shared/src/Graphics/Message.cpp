//
// Created by xgallom on 2/13/19.
//

#include "Graphics/Message.h"

#include "Graphics/OutputBuffer.h"

#include <cstring>

void message(const char msg[], ColorAttribute ca)
{
	const auto size = strlen(msg);

	write(
			center(Coords{static_cast<Coords::value_type>(size), 0}),
			ca,
			msg,
			size
	);
}

