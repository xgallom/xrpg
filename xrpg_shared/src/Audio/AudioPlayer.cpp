//
// Created by xgallom on 2/19/19.
//

#include "Audio/AudioPlayer.h"

#include <atomic>
#include <list>
#include <mutex>

namespace Audio::AudioPlayer
{
	struct {
		std::atomic_flag
			soundsAccessible = ATOMIC_FLAG_INIT;

		size_t
			soundToPlay = 0,
			soundsSize  = 0;

		std::mutex musicAccessMutex = {};

		std::list<std::unique_ptr<Data::WavFileStream>> musicList = {};
		std::vector<std::unique_ptr<Data::WavFileBuffer>> sounds = {};
	} static s_state;

	void addMusic(std::unique_ptr<Data::WavFileStream> &&music)
	{
		std::lock_guard lock(s_state.musicAccessMutex);

		s_state.musicList.push_back(std::move(music));
	}

	void replaceSounds(std::vector<std::unique_ptr<Data::WavFileBuffer>> &&sounds)
	{
		while(s_state.soundsAccessible.test_and_set(std::memory_order_acquire)) {}

		s_state.sounds = std::move(sounds);
		const auto size = s_state.sounds.size();

		s_state.soundToPlay = size;
		s_state.soundsSize = size;

		s_state.soundsAccessible.clear(std::memory_order_release);
	}

	void playSound(size_t index)
	{
		for(;;) {
			while(s_state.soundsAccessible.test_and_set(std::memory_order_acquire)) {}

			if(s_state.soundToPlay >= s_state.soundsSize)
				break;

			s_state.soundsAccessible.clear(std::memory_order_relaxed);
		}

		s_state.soundToPlay = index;
		s_state.soundsAccessible.clear(std::memory_order_release);
	}

	std::unique_ptr<Data::StreamChunk> getStreamChunk()
	{
		std::lock_guard lock(s_state.musicAccessMutex);

		if(s_state.musicList.empty())
			return nullptr;

		auto chunk = s_state.musicList.front()->getChunk();

		if(!chunk)
			s_state.musicList.pop_front();

		return chunk;
	}

	Result<Data::Buffer> getBuffer()
	{
		while(s_state.soundsAccessible.test_and_set(std::memory_order_acquire)) {}

		if(s_state.soundToPlay < s_state.soundsSize) {
			const auto buffer = s_state.sounds[s_state.soundToPlay]->getBuffer();
			s_state.soundToPlay = s_state.soundsSize;

			s_state.soundsAccessible.clear(std::memory_order_release);

			return buffer;
		}

		s_state.soundsAccessible.clear(std::memory_order_relaxed);

		return {};
	}
}
