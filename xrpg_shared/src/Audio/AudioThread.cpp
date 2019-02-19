//
// Created by xgallom on 2/18/19.
//

#include "AudioThread.h"
#include "AudioPlayer.h"

#include <memory>
#include <thread>
#include <atomic>
#include <iostream>

namespace Audio::AudioThread
{
	struct {
		std::atomic<bool> running = true;

		AtomicStream<Data::StreamChunk> atomicStream{};
		AtomicBuffer<Data::Buffer> atomicBuffer{};
	} static s_threadContext;

	static std::unique_ptr<std::thread> s_thread;

	static void threadHandler()
	{
		std::unique_ptr<Data::StreamChunk> musicChunk = nullptr;

		while(s_threadContext.running.load(std::memory_order_acquire)) {
			bool wasActive = false;

			if(musicChunk) {
				if(s_threadContext.atomicStream.canPublish()) {
					wasActive = true;

					s_threadContext.atomicStream.publish(std::move(musicChunk));
				}
				else
					s_threadContext.atomicStream.cleanUp();
			}
			else {
				musicChunk = AudioPlayer::getStreamChunk();

				if(musicChunk)
					wasActive = true;
			}

			if(s_threadContext.atomicBuffer.canPublish()) {
				const auto result = AudioPlayer::getBuffer();

				if(result) {
					wasActive = true;
					s_threadContext.atomicBuffer.publish(result());
				}
			}

			if(!wasActive)
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
	}

	void start()
	{
		s_threadContext.running.store(true, std::memory_order_release);

		s_thread = std::make_unique<std::thread>(threadHandler);
	}

	void stop()
	{
		s_threadContext.running.store(false, std::memory_order_release);

		s_thread->join();

		s_thread.reset();
	}

	AtomicStream<Data::StreamChunk> &getAudioStream()
	{
		return s_threadContext.atomicStream;
	}

	AtomicBuffer<Data::Buffer> &getAudioBuffer()
	{
		return s_threadContext.atomicBuffer;
	}
}
