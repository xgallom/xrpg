//
// Created by xgallom on 2/16/19.
//

#ifndef XRPG_AUDIOCONTEXT_H
#define XRPG_AUDIOCONTEXT_H

#include <portaudio.h>

namespace Audio
{
	static constexpr auto SampleRate = 44100;

	PaStream *&stream();
}


#endif //XRPG_AUDIOCONTEXT_H
