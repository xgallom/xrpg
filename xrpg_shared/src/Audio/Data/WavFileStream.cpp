//
// Created by xgallom on 2/17/19.
//

#include "WavFileStream.h"

#include "Audio/AudioStream.h"

namespace Audio::Data
{
	WavFileStream::WavFileStream(const std::string &fileName) : m_wavFile(fileName)
	{}

	bool WavFileStream::prepare()
	{
		const auto result = m_wavFile.parseHeader();

		if(!result)
			return false;

		m_fileInfo = result();

		return true;
	}

	std::unique_ptr<StreamChunk> WavFileStream::getChunk()
	{
		const auto size = chunkSize();

		std::unique_ptr<StreamChunk> chunk = std::make_unique<StreamChunk>(
			DataInfo{m_fileInfo.format.sampleRate, m_fileInfo.format.channelCount}
		);

		chunk->data.reserve(size);

		if(auto remaining = m_wavFile.remaining<int16_t>(); remaining < size)
			return nullptr;

		for(uint32_t n = 0; n < size; ++n) {
			const auto result = m_wavFile.parseShort();

			chunk->data.push_back(result ? result() : static_cast<int16_t>(0));
		}

		return chunk;
	}

	uint32_t WavFileStream::chunkSize() const
	{
		return m_fileInfo.format.channelCount * framesPerAudioBuffer();
	}
}
