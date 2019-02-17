//
// Created by xgallom on 2/16/19.
//

#include "Audio/AudioStream.h"

#include "AudioContext.h"
#include "SampleFormat.h"

#include <iostream>
#include <Audio/Data/Stream.h>

namespace Audio
{
	struct AudioData {
		Data::WavFileStream *stream = nullptr;
	};

	static constexpr int
		InputChannelCount = 0,
		OutputChannelCount = 2;

	static AudioData s_audioData = {};
	static unsigned long s_framesPerBuffer = 0;

	static int audioCallback(
			const void *,
			void *outputPtr,
			unsigned long,
			const PaStreamCallbackTimeInfo *,
			PaStreamCallbackFlags,
			void *audioDataPtr
	) noexcept
	{
		//clock_t begin = clock();

		auto &audioData = *reinterpret_cast<AudioData *>(audioDataPtr);
		auto *output = reinterpret_cast<float *>(outputPtr);

		const auto chunk = audioData.stream->getChunk();

		for(const auto sample : chunk.data)
			*output++ = static_cast<float>(sample) / std::numeric_limits<int16_t>::max();

		//clock_t end = clock();

		//std::cerr << double(end - begin) / CLOCKS_PER_SEC << "\n";

		return 0;
	}

	bool openDefaultStream()
	{
		auto *&s_stream = stream();

		if(s_stream)
			return false;

		s_framesPerBuffer = 256;

		const auto err = Pa_OpenDefaultStream(
				&s_stream,
				InputChannelCount,
				OutputChannelCount,
				SampleFormat::Float32,
				SampleRate,
				s_framesPerBuffer,
				audioCallback,
				&s_audioData
		);

		if(err != paNoError) {
			std::cerr
				<< "Failed to open audio stream\n"
				<< Pa_GetErrorText(err);

			return false;
		}

		auto streamInfo = Pa_GetStreamInfo(s_stream);

		if(streamInfo) {
			std::cerr << streamInfo->sampleRate << "\n";
			std::cerr << streamInfo->outputLatency << "\n";
		}

		return true;
	}

	bool startStream()
	{
		s_audioData.stream = new Data::WavFileStream("data/music/tristram.wav");

		if(!s_audioData.stream->prepare()) {
			std::cerr << "Failed to prepare audio stream\n";
			return false;
		}

		if(const auto err = Pa_StartStream(stream()); err != paNoError) {
			std::cerr
				<< "Failed to start audio stream\n"
				<< Pa_GetErrorText(err);

			return false;
		}

		return true;
	}

	bool stopStream()
	{
		if(const auto err = Pa_StopStream(stream()); err != paNoError) {
			std::cerr
				<< "Failed to stop audio stream\n"
				<< Pa_GetErrorText(err);

			return false;
		}

		return true;
	}

	bool abortStream()
	{
		auto *s_stream = stream();

		if(Pa_IsStreamActive(s_stream)) {
			if(const auto err = Pa_AbortStream(stream()); err != paNoError) {
				std::cerr
					<< "Failed to abort audio stream\n"
					<< Pa_GetErrorText(err);

				return false;
			}
		}

		return true;
	}

	bool closeStream()
	{
		auto *&s_stream = stream();

		if(s_stream && abortStream()) {
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
