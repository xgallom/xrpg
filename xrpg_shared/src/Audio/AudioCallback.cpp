//
// Created by xgallom on 2/18/19.
//

#include "AudioCallback.h"

#include "AudioThread.h"

#include <iostream>

namespace Audio
{
	size_t AudioCallbackData::nextFreeIndex() const
	{
		for(size_t i = 0; i < MaxSounds; ++i) {
			if(!soundFlags.test(i))
				return i;
		}

		return MaxSounds;
	}

	void AudioCallbackData::insert(size_t index, const Data::Buffer &data)
	{
		soundFlags.set(index);
		soundBuffers[index] = data;
	}

	void AudioCallbackData::remove(size_t index)
	{
		soundFlags.reset(index);
	}

	template<typename Func>
	void AudioCallbackData::forEach(Func f)
	{
		for(size_t i = 0; i < MaxSounds; ++i) {
			if(soundFlags.test(i))
				f(soundBuffers[i], i);
		}
	}

	namespace AudioCallback
	{
		int callback(
				const void *,
				void *outputPtr,
				unsigned long frameCount,
				const PaStreamCallbackTimeInfo *,
				PaStreamCallbackFlags,
				void *callbackDataPtr
		) noexcept
		{
			auto &audioData = *reinterpret_cast<AudioCallbackData *>(callbackDataPtr);
			auto *output = reinterpret_cast<float *>(outputPtr);

			auto &audioStream = AudioThread::getAudioStream();
			auto &audioBuffer = AudioThread::getAudioBuffer();

			const auto masterLevel = Processing::level(audioData.level.master);
			const auto musicLevel  = masterLevel * Processing::level(audioData.level.music);
			const auto soundLevel  = masterLevel * Processing::level(audioData.level.sound);

			const auto musicResult = audioStream.tryAcquire();

			if(musicResult) {
				Processing::outputMusic(output, frameCount, musicLevel, *musicResult());
				audioStream.release();
			}
			else
				Processing::outputSilence(output, frameCount);

			{
				size_t freeIndex;

				while((freeIndex = audioData.nextFreeIndex()) < MaxSounds) {
					const auto soundResult = audioBuffer.tryAcquire();

					if(!soundResult)
						break;

					audioData.insert(freeIndex, soundResult());

					audioBuffer.release();
				}
			}

			audioData.forEach([&audioData, output, frameCount, soundLevel](Data::Buffer &sound, size_t index) {
				switch(sound.dataInfo.channelCount) {
					case Data::ChannelCountMono:
						if(Processing::outputSoundMono(output, frameCount, soundLevel, sound))
							audioData.remove(index);
						break;

					case Data::ChannelCountStereo:
						if(Processing::outputSoundStereo(output, frameCount, soundLevel, sound))
							audioData.remove(index);
						break;

					default:
						std::cerr << "Invalid channel count: " << sound.dataInfo.channelCount << "\n";
						break;
				}
			});

			/*
			while(frameCount--) {
				std::cerr << *output++ << " ";
				std::cerr << *output++ << " : ";
			}
			std::cerr << "\n";
			 */

			return 0;
		}
	}
}
