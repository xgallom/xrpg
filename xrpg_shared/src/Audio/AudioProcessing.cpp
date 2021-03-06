//
// Created by xgallom on 2/18/19.
//

#include "AudioProcessing.h"

namespace Audio::Processing
{
	static constexpr Sample NoSample = {};

	static Sample operator *(Sample s, float f)
	{
		return {s.left * f, s.right * f};
	}

	static float level(std::atomic<int> &value)
	{
		return static_cast<float>(value.load(std::memory_order_relaxed)) / 100;
	}

	AudioLevels levels(std::atomic<int> &master, std::atomic<int> &music, std::atomic<int> &sound)
	{
		const auto
			masterLevel = level(master),
			musicLevel = level(music),
			soundLevel = level(sound);

		const auto
			musicRemaining = 1.0f - musicLevel,
			soundRemaining = 1.0f - soundLevel;

		const auto
			musicRemainingModifier = musicRemaining * MaxMusicTracks,
			soundRemainingModifier = soundRemaining * MaxSounds     ;

		const auto
			musicModifier = 1.0f + soundRemainingModifier / MaxMusicTracks,
			soundModifier = 1.0f + musicRemainingModifier / MaxSounds     ;

		auto normalizedMaster = masterLevel / ChannelCount;

		const auto
			computedMusicLevel = musicLevel * musicModifier * normalizedMaster,
			computedSoundLevel = soundLevel * soundModifier * normalizedMaster;

		return {
				masterLevel,
				computedMusicLevel,
				computedSoundLevel
		};
	}

	static float normalize(int16_t sample)
	{
		return static_cast<float>(sample) / std::numeric_limits<int16_t>::max();
	}

	static Sample normalize(int16_t left, int16_t right)
	{
		return {normalize(left), normalize(right)};
	}

	static void outputSample(float *&output, unsigned long &frameCount, Sample sample)
	{
		*output++ = sample.left;
		*output++ = sample.right;
		--frameCount;
	}

	static void addSample(float *&output, unsigned long &frameCount, Sample sample)
	{
		*output++ += sample.left;
		*output++ += sample.right;
		--frameCount;
	}

	void outputSilence(float *output, unsigned long frameCount)
	{
		while(frameCount)
			outputSample(output, frameCount, NoSample);
	}

	void outputMusic(float *output, unsigned long frameCount, float levelValue, const Data::StreamChunk &streamChunk)
	{
		for(auto i = streamChunk.data.cbegin(), end = streamChunk.data.cend(); i != end;) {
			const auto left  = *i++;
			const auto right = *i++;

			outputSample(output, frameCount, normalize(left, right) * levelValue);
		}

		outputSilence(output, frameCount);
	}

	bool outputSoundMono(float *output, unsigned long frameCount, float levelValue, Data::Buffer &soundBuffer)
	{
		for(; soundBuffer.index != soundBuffer.data.end; ++soundBuffer.index) {
			if(!frameCount)
				return false;

			const auto sample = normalize(*soundBuffer.index) * levelValue;

			// Resample 22050 -> 44100
			addSample(output, frameCount, {sample, sample});
			addSample(output, frameCount, {sample, sample});
		}

		return true;
	}

	bool outputSoundStereo(float *output, unsigned long frameCount, float levelValue, Data::Buffer &soundBuffer)
	{
		for(; soundBuffer.index < soundBuffer.data.end; ++soundBuffer.index) {
			if(!frameCount)
				return false;

			const auto left  = normalize(*soundBuffer.index++) * levelValue;
			const auto right = normalize(*soundBuffer.index)   * levelValue;

			// Resample 22050 -> 44100
			addSample(output, frameCount, {left, right});
			addSample(output, frameCount, {left, right});
		}

		return true;
	}
}
