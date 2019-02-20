//
// Created by xgallom on 2/18/19.
//

#ifndef XRPG_AUDIOPROCESSING_H
#define XRPG_AUDIOPROCESSING_H

#include "Data/DataInfo.h"

#include <atomic>
#include <limits>
#include <cstdint>
#include <cstddef>

namespace Audio
{
	static constexpr size_t
		MaxSounds = 4,
		MaxMusicTracks = 1,
		ChannelCount = MaxSounds + MaxMusicTracks;

	namespace Processing
	{
		struct Sample {
			float
				left = 0.0f,
				right = 0.0f;
		};

		float level(std::atomic<int> &value);

		void outputSilence(float *output, unsigned long frameCount);
		void outputMusic(float *output, unsigned long frameCount, float level, const Data::StreamChunk &streamChunk);
		bool outputSoundMono(float *output, unsigned long frameCount, float level, Data::Buffer &soundBuffer);
		bool outputSoundStereo(float *output, unsigned long frameCount, float level, Data::Buffer &soundBuffer);
	}
}

#endif //XRPG_AUDIOPROCESSING_H
