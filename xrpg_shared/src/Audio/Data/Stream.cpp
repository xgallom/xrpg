//
// Created by xgallom on 2/17/19.
//

#include "Stream.h"

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

	StreamChunk WavFileStream::getChunk()
	{
		StreamChunk chunk{};

		const auto size = chunkSize();

		chunk.dataInfo = {m_fileInfo.format.sampleRate, m_fileInfo.format.channelCount};
		chunk.data.reserve(size);

		if(m_wavFile.remaining<uint16_t>() < size)
			return {};

		for(uint32_t n = 0; n < size; ++n)
			chunk.data.push_back(m_wavFile.parseShort());

		return chunk;
	}

	uint32_t WavFileStream::chunkSize() const
	{
		return m_fileInfo.format.channelCount * framesPerAudioBuffer();
	}
}
