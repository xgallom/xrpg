//
// Created by xgallom on 2/16/19.
//

#include "Audio/Audio.h"
#include "AudioStream.h"
#include "AudioPlayer.h"
#include "Storage/Storage.h"

#include <iostream>
#include <portaudio.h>

namespace Audio
{
	static bool initImplementation()
	{
		if(const auto err = Pa_Initialize(); err != paNoError) {
			std::cerr
					<< "Failed to initialize audio\n"
					<< Pa_GetErrorText(err);

			return false;
		}

		return true;
	}

	bool init()
	{
		if(initImplementation())
			return openDefaultStream();

		return false;
	}

	void deinit()
	{
		closeStream();

		if(const auto err = Pa_Terminate(); err != paNoError) {
			std::cerr
				<< "Failed to deinitialize audio\n"
				<< Pa_GetErrorText(err);
		}
	}

	bool start()
	{
		return startStream();
	}
	bool stop()
	{
		return stopStream();
	}

	void addMusic(::Music::Enum music)
	{
		const auto fileName = Storage::Music::fileNameFor(music);

		auto musicStream = std::make_unique<Data::WavFileStream>(fileName);

		if(musicStream->prepare()) {
			std::cerr << "Adding " << fileName << " to music playlist\n";
			AudioPlayer::addMusic(std::move(musicStream));
		}
		else
			std::cerr << "Failed to add " << fileName << " to music playlist\n";
	}
}
