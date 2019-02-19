//
// Created by xgallom on 2/16/19.
//

#include "AudioContextPrivate.h"

#include "AudioCallback.h"
#include "Storage/Settings.h"

namespace Audio
{
	namespace AudioContext
	{
		void AudioLevels::apply(const Settings &settings)
		{
			master.store(settings.audioLevelMaster, std::memory_order_relaxed);
			music.store(settings.audioLevelMusic, std::memory_order_relaxed);
			sound.store(settings.audioLevelSound, std::memory_order_relaxed);
		}

		AudioLevels &audioLevels()
		{
			return callbackData()->level;
		}

		PaStream *&stream()
		{
			static PaStream *s_stream = nullptr;

			return s_stream;
		}

		AudioCallbackData *callbackData()
		{
			static AudioCallbackData s_callbackData = {};

			return &s_callbackData;
		}
	}
}
