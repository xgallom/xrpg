//
// Created by xgallom on 2/16/19.
//

#ifndef XRPG_AUDIOCONTEXTPRIVATE_H
#define XRPG_AUDIOCONTEXTPRIVATE_H

#include "Audio/AudioContext.h"

#include <portaudio.h>

namespace Audio
{
	struct AudioCallbackData;

	namespace AudioContext
	{
		static constexpr int
				SampleRate = 44100,
				InputChannelCount = 0,
				OutputChannelCount = 2;
		static constexpr unsigned long FramesPerBuffer = 512;
		static constexpr PaSampleFormat SampleFormat = 0x00000001; /* paFloat32 */

		PaStream *&stream();
		AudioCallbackData *callbackData();
	}
}


#endif //XRPG_AUDIOCONTEXTPRIVATE_H
