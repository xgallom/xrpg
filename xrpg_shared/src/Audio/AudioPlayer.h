//
// Created by xgallom on 2/19/19.
//

#ifndef XRPG_AUDIOPLAYER_H
#define XRPG_AUDIOPLAYER_H

#include "Data/WavFileBuffer.h"
#include "Data/WavFileStream.h"
#include "Util/Result.h"

#include <memory>

namespace Audio
{
	namespace AudioPlayer
	{
		void addMusic(std::unique_ptr<Data::WavFileStream> &&music);
		void replaceSounds(std::vector<std::unique_ptr<Data::WavFileBuffer>> &&sounds);

		void playSound(size_t index);

		std::unique_ptr<Data::StreamChunk> getStreamChunk();
		Result<Data::Buffer> getBuffer();
	}
}

#endif //XRPG_AUDIOPLAYER_H
