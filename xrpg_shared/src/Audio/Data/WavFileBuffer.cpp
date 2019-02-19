//
// Created by xgallom on 2/18/19.
//

#include "WavFileBuffer.h"

namespace Audio::Data
{
	WavFileBuffer::WavFileBuffer(const std::string &fileName) : m_wavFile(std::make_unique<WavFile>(fileName)) {}

	bool WavFileBuffer::prepare()
	{
		const auto result = m_wavFile->parseHeader();

		if(!result)
			return false;

		m_fileInfo = result();

		m_data.reserve(m_fileInfo.dataSize);

		for(uint32_t n = 0; n < m_fileInfo.dataSize; ++n) {
			const auto inputResult = m_wavFile->parseShort();
			if(!inputResult) {
				m_fileInfo.dataSize = n;
				break;
			}

			m_data.push_back(inputResult());
		}

		m_wavFile.reset();

		return true;
	}

	Buffer WavFileBuffer::getBuffer() const
	{
		const auto *begin = &*m_data.begin();

		return {
				{m_fileInfo.format.sampleRate, m_fileInfo.format.channelCount},
				begin,
				{begin, &*m_data.end()}
		};
	}
}
