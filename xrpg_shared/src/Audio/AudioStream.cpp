//
// Created by xgallom on 2/16/19.
//

#include "AudioStream.h"

#include "AudioCallback.h"
#include "AudioThread.h"
#include "AudioPlayer.h"
#include "Storage/Storage.h"

#include <iostream>
#include <thread>

namespace Audio
{
	static unsigned long s_framesPerBuffer = 0;

	bool openDefaultStream()
	{
		auto *&s_stream = AudioContext::stream();

		if(s_stream)
			return false;

		s_framesPerBuffer = AudioContext::FramesPerBuffer;

		AudioContext::callbackData()->level.apply(Storage::Settings::restore()());

		const auto err = Pa_OpenDefaultStream(
				&s_stream,
				AudioContext::InputChannelCount,
				AudioContext::OutputChannelCount,
				AudioContext::SampleFormat,
				AudioContext::SampleRate,
				s_framesPerBuffer,
				AudioCallback::callback,
				AudioContext::callbackData()
		);

		if(err != paNoError) {
			std::cerr
				<< "Failed to open audio stream\n"
				<< Pa_GetErrorText(err);

			return false;
		}

		auto streamInfo = Pa_GetStreamInfo(s_stream);

		std::cerr << "Stream buffer size: " << s_framesPerBuffer << " frames\n";

		if(streamInfo) {
			std::cerr << "Stream sample rate: " << streamInfo->sampleRate << "\n";
			std::cerr << "Stream latency:     " << streamInfo->outputLatency << "\n";
		}

		return true;
	}

	bool startStream()
	{
		AudioThread::start();

		AudioContext::callbackData()->reset();

		if(const auto err = Pa_StartStream(AudioContext::stream()); err != paNoError) {
			std::cerr
				<< "Failed to start audio stream\n"
				<< Pa_GetErrorText(err);

			return false;
		}

		return true;
	}

	bool stopStream()
	{
		AudioThread::stop();

		if(const auto err = Pa_StopStream(AudioContext::stream()); err != paNoError) {
			std::cerr
				<< "Failed to stop audio stream\n"
				<< Pa_GetErrorText(err);

			return false;
		}

		return true;
	}

	bool closeStream()
	{
		auto *&s_stream = AudioContext::stream();

		if(s_stream) {
			stopStream();

			if(const auto err = Pa_CloseStream(s_stream); err != paNoError) {
				std::cerr
					<< "Failed to close audio stream\n"
					<< Pa_GetErrorText(err);

				return false;
			}

			s_stream = nullptr;

			return true;
		}

		return false;
	}

	unsigned long framesPerAudioBuffer()
	{
		return s_framesPerBuffer;
	}
}
