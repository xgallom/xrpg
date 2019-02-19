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
		ChannelCount = MaxSounds + 1 /* Music track */;

	namespace Processing
	{
		struct Sample {
			float
				left = 0.0f,
				right = 0.0f;
		};
		inline Sample operator *(Sample s, float f) { return {s.left * f, s.right * f}; }

		static constexpr Sample NoSample = {};

		inline float level(std::atomic<int> &value) {
			return static_cast<float>(value.load(std::memory_order_relaxed)) / 100;
		}

		inline float normalize(int16_t sample) {
			static constexpr auto Level = 1.0f / ChannelCount;
			return Level * static_cast<float>(sample) / std::numeric_limits<int16_t>::max();
		}

		inline Sample normalize(int16_t left, int16_t right) {
			return {normalize(left), normalize(right)};
		}

		inline void outputSample(float *&output, unsigned long &frameCount, Sample sample) {
			*output++ = sample.left;
			*output++ = sample.right;
			--frameCount;
		}

		inline void addSample(float *&output, unsigned long &frameCount, Sample sample) {
			*output++ += sample.left;
			*output++ += sample.right;
			--frameCount;
		}

		inline void outputSilence(float *output, unsigned long frameCount)
		{
			while(frameCount)
				outputSample(output, frameCount, NoSample);
		}

		inline void outputMusic(float *output, unsigned long frameCount, float level, const Data::StreamChunk &streamChunk) {
			for(auto i = streamChunk.data.cbegin(), end = streamChunk.data.cend(); i != end;) {
				const auto left  = *i++;
				const auto right = *i++;

				outputSample(output, frameCount, normalize(left, right) * level);
			}

			outputSilence(output, frameCount);
		}

		inline bool outputSoundMono(float *output, unsigned long frameCount, float level, Data::Buffer &soundBuffer) {
			for(; soundBuffer.index != soundBuffer.data.end; ++soundBuffer.index) {
				if(!frameCount)
					return false;

				const auto sample = normalize(*soundBuffer.index) * level;

				// Resample 22050 -> 44100
				addSample(output, frameCount, {sample, sample});
				addSample(output, frameCount, {sample, sample});
			}

			return true;
		}

		inline bool outputSoundStereo(float *output, unsigned long frameCount, float level, Data::Buffer &soundBuffer) {
			for(; soundBuffer.index < soundBuffer.data.end; ++soundBuffer.index) {
				if(!frameCount)
					return false;

				const auto left  = normalize(*soundBuffer.index++) * level;
				const auto right = normalize(*soundBuffer.index)   * level;

				// Resample 22050 -> 44100
				addSample(output, frameCount, {left, right});
				addSample(output, frameCount, {left, right});
			}

			return true;
		}
	}
}

#endif //XRPG_AUDIOPROCESSING_H
