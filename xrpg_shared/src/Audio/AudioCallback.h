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

		size_t nextFreeIndex() const;
		void insert(size_t index, const Data::Buffer &data);
		void remove(size_t index);

		template<typename Func>
		void forEach(Func f);

		AudioContext::AudioLevels level;

		inline void reset() {
			soundFlags = {};
		}
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
