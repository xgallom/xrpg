//
// Created by xgallom on 2/17/19.
//

#ifndef XRPG_WAVFILE_H
#define XRPG_WAVFILE_H

#include "Util/Result.h"

#include <fstream>

namespace Audio::Data
{
	struct File {
		explicit File(const std::string &fileName);

		std::fstream fileStream;

		bool isOpen() const;
		int get();
	};

	struct WavFormat {
		uint16_t audioFormat = 0;
		uint16_t channelCount = 0;
		uint32_t sampleRate = 0;
		uint32_t byteRate = 0;
		uint16_t blockAlign = 0;
		uint16_t bytesPerSample = 0;
	};

	struct WavFileInfo {
		uint32_t dataSize = 0;
		WavFormat format = {};
	};

	struct WavFile : public File {
		explicit WavFile(const std::string &fileName);

		template<typename type>
		uint32_t remaining() const { return m_remaining / sizeof(type); }

		Result<WavFileInfo> parseHeader();
		Result<int16_t> parseShort();

	private:
		uint16_t parseUShort();
		uint32_t parseUInt();
		bool parse(const char *str);
		uint32_t parseRiff();
		Result<WavFormat> parseFormat();
		uint32_t parseData();

		int get();

		uint32_t m_remaining = 0;
	};
}

#endif //XRPG_WAVFILE_H
