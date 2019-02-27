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

		struct AudioLevels {
			float
				master,
				music,
				sound;
		};

		AudioLevels levels(std::atomic<int> &master, std::atomic<int> &music, std::atomic<int> &sound);

		void outputSilence(float *output, unsigned long frameCount);
		void outputMusic(float *output, unsigned long frameCount, float levelValue, const Data::StreamChunk &streamChunk);
		bool outputSoundMono(float *output, unsigned long frameCount, float levelValue, Data::Buffer &soundBuffer);
		bool outputSoundStereo(float *output, unsigned long frameCount, float levelValue, Data::Buffer &soundBuffer);
	}
}

#endif //XRPG_AUDIOPROCESSING_H
