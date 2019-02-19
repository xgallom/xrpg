//
// Created by xgallom on 2/16/19.
//

#include "Audio/AudioStream.h"

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

		s_framesPerBuffer = 256;

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

		if(streamInfo) {
			std::cerr << streamInfo->sampleRate << "\n";
			std::cerr << streamInfo->outputLatency << "\n";
		}

		return true;
	}

	bool startStream()
	{
		AudioThread::start();

		AudioContext::callbackData()->reset();

		auto music = std::make_unique<Data::WavFileStream>("data/music/title.wav");

		if(music->prepare()) {
			AudioPlayer::addMusic(std::move(music));
		}

		music = std::make_unique<Data::WavFileStream>("data/music/docks.wav");

		if(music->prepare()) {
			AudioPlayer::addMusic(std::move(music));
		}

		if(const auto err = Pa_StartStream(AudioContext::stream()); err != paNoError) {
			std::cerr
				<< "Failed to start audio stream\n"
				<< Pa_GetErrorText(err);

			return false;
		}

		std::vector<std::unique_ptr<Data::WavFileBuffer>> sounds;
		sounds.emplace_back(std::make_unique<Data::WavFileBuffer>("data/sound/cursor/select.wav"));

		if(!sounds[0]->prepare()) {
			return false;
		}

		AudioPlayer::replaceSounds(std::move(sounds));
		AudioPlayer::playSound(0);

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

	bool abortStream()
	{
		AudioThread::stop();

		if(const auto err = Pa_AbortStream(AudioContext::stream()); err != paNoError) {
			std::cerr
				<< "Failed to abort audio stream\n"
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
