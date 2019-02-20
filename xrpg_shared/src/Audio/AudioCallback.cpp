//
// Created by xgallom on 2/18/19.
//

#include "AudioCallback.h"

#include "AudioThread.h"

#include <iostream>

namespace Audio
{
	void AudioCallbackData::reset()
	{
		soundFlags = {};
	}

	namespace AudioCallback
	{
		static void updateAudioData(AudioCallbackData &audioData, AtomicBuffer<Data::Buffer> &audioBuffer);
		static size_t nextFreeIndex(const AudioCallbackData &audioData);
		static void insert(AudioCallbackData &audioData, size_t index, const Data::Buffer &data);
		static void remove(AudioCallbackData &audioData, size_t index);

		template<typename Func>
		static void forEach(AudioCallbackData &audioData, Func f)
		{
			for(size_t i = 0; i < MaxSounds; ++i) {
				if(audioData.soundFlags.test(i))
					f(audioData.soundBuffers[i], i);
			}
		}

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
			const auto musicLevel = masterLevel * Processing::level(audioData.level.music);
			const auto soundLevel = masterLevel * Processing::level(audioData.level.sound);

			const auto musicResult = audioStream.tryAcquire();

			if(musicResult) {
				Processing::outputMusic(output, frameCount, musicLevel, *musicResult());
				audioStream.release();
			}
			else
				Processing::outputSilence(output, frameCount);

			updateAudioData(audioData, audioBuffer);

			forEach(audioData, [&audioData, output, frameCount, soundLevel](Data::Buffer &sound, size_t index) {
				switch(sound.dataInfo.channelCount) {
					case Data::ChannelCountMono:
						if(Processing::outputSoundMono(output, frameCount, soundLevel, sound))
							remove(audioData, index);
						break;

					case Data::ChannelCountStereo:
						if(Processing::outputSoundStereo(output, frameCount, soundLevel, sound))
							remove(audioData, index);
						break;

					default:
						std::cerr << "Invalid channel count: " << sound.dataInfo.channelCount << "\n";
						break;
				}
			});

			return 0;
		}

		static void updateAudioData(AudioCallbackData &audioData, AtomicBuffer<Data::Buffer> &audioBuffer)
		{
			size_t freeIndex;

			while((freeIndex = nextFreeIndex(audioData)) < MaxSounds) {
				const auto soundResult = audioBuffer.tryAcquire();

				if(!soundResult)
					break;

				insert(audioData, freeIndex, soundResult());

				audioBuffer.release();
			}
		}

		static size_t nextFreeIndex(const AudioCallbackData &audioData)
		{
			for(size_t i = 0; i < MaxSounds; ++i) {
				if(!audioData.soundFlags.test(i))
					return i;
			}

			return MaxSounds;
		}

		static void insert(AudioCallbackData &audioData, size_t index, const Data::Buffer &data)
		{
			audioData.soundFlags.set(index);
			audioData.soundBuffers[index] = data;
		}

		static void remove(AudioCallbackData &audioData, size_t index)
		{
			audioData.soundFlags.reset(index);
		}
	}
}

