//
// Created by xgallom on 2/18/19.
//

#ifndef XRPG_AUDIOCALLBACK_H
#define XRPG_AUDIOCALLBACK_H

#include "AudioProcessing.h"
#include "AudioContextPrivate.h"

#include <portaudio.h>

#include <array>
#include <bitset>

namespace Audio
{
	struct AudioCallbackData {
		std::bitset<MaxSounds> soundFlags = {};
		std::array<Data::Buffer, MaxSounds> soundBuffers = {};

		AudioContext::AudioLevels level;

		void reset();
	};

	namespace AudioCallback
	{
		int callback(
				const void *,
				void *outputPtr,
				unsigned long frameCount,
				const PaStreamCallbackTimeInfo *,
				PaStreamCallbackFlags,
				void *callbackDataPtr
		) noexcept;
	}
}


#endif //XRPG_AUDIOCALLBACK_H
