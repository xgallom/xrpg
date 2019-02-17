//
// Created by xgallom on 2/16/19.
//

#include "AudioContext.h"

namespace Audio
{
	PaStream *&stream()
	{
		static PaStream *s_stream = nullptr;

		return s_stream;
	}
}
