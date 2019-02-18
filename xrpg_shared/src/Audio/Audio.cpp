//
// Created by xgallom on 2/16/19.
//

#include "Audio/Audio.h"
#include "Audio/AudioStream.h"
#include "AudioContext.h"

#include <iostream>
#include <Audio/Data/File.h>

namespace Audio
{
	bool init()
	{
		if(const auto err = Pa_Initialize(); err != paNoError) {
			std::cerr
				<< "Failed to initialize audio\n"
				<< Pa_GetErrorText(err);

			return false;
		}

		auto wavFile = Data::WavFile("data/music/tristram.wav");

		if(!wavFile.isOpen()) {
			std::cerr << "Error opening audio file\n";
			return false;
		}

		const auto result = wavFile.parseHeader();

		if(!result) {
			std::cerr << "Error parsing audio file header\n";
			return false;
		}

		const auto &fileInfo = result();

		std::cerr
			<< "Data size:        " << fileInfo.dataSize              << "\n"
			<< "Audio format:     " << fileInfo.format.audioFormat    << "\n"
			<< "Channel count:    " << fileInfo.format.channelCount   << "\n"
			<< "Sample rate:      " << fileInfo.format.sampleRate     << "\n"
			<< "Byte rate:        " << fileInfo.format.byteRate       << "\n"
			<< "Block alignment:  " << fileInfo.format.blockAlign     << "\n"
			<< "Bytes per sample: " << fileInfo.format.bytesPerSample << "\n"
			;

		return true;
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
}
