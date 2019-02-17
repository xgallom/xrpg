//
// Created by xgallom on 2/17/19.
//

#include "File.h"

namespace Audio::Data
{
	static constexpr uint16_t
		AudioFormatPcm = 1,
		ChannelCountMono = 1,
		ChannelCountStereo = 2;

	static constexpr uint32_t
		WavFormatSize = 16,
		WavHeaderSize = WavFormatSize + 20;

	File::File(const std::string &fileName) : fileStream(fileName, std::ios::binary | std::ios::in) {}

	bool File::isOpen() const
	{
		return fileStream.is_open();
	}

	int File::get()
	{
		return fileStream.get();
	}

	WavFile::WavFile(const std::string &fileName) : File(fileName) {}

	Result<WavFileInfo> WavFile::parseHeader()
	{
		WavFileInfo fileInfo{};

		if(!parseRiff())
			return {};

		const auto formatResult = parseFormat();

		if(!formatResult)
			return {};

		fileInfo.format = formatResult();
		fileInfo.dataSize = parseData();

		if(!fileInfo.dataSize)
			return {};

		m_remaining = fileInfo.dataSize;

		return fileInfo;
	}

	int16_t WavFile::parseShort()
	{
		return static_cast<int16_t>(get() | (get() << 8));
	}

	uint16_t WavFile::parseUShort()
	{
		return static_cast<uint16_t>(get() | (get() << 8));
	}

	uint32_t WavFile::parseUInt()
	{
		return static_cast<uint32_t>(get() | (get() << 8) | (get() << 16) | (get() << 24));
	}

	bool WavFile::parse(const char *str)
	{
		while(*str) {
			if(*str++ != get())
				return false;
		}

		return true;
	}

	uint32_t WavFile::parseRiff()
	{
		if(!parse("RIFF"))
			return 0;

		const auto size = parseUInt();

		if(!parse("WAVE"))
			return 0;

		return size;
	}

	Result<WavFormat> WavFile::parseFormat()
	{
		if(!parse("fmt ") || parseUInt() != WavFormatSize)
			return {};

		WavFormat wavFormat{};

		wavFormat.audioFormat = parseUShort();
		wavFormat.channelCount = parseUShort();
		wavFormat.sampleRate = parseUInt();
		wavFormat.byteRate = parseUInt();
		wavFormat.blockAlign = parseUShort();

		const auto bitsPerSample = parseUShort();
		wavFormat.bytesPerSample = static_cast<uint16_t>(bitsPerSample / 8);

		if(
			wavFormat.audioFormat != AudioFormatPcm ||
			!wavFormat.channelCount || wavFormat.channelCount > ChannelCountStereo
		)
			return {};

		return wavFormat;
	}

	uint32_t WavFile::parseData()
	{
		if(!parse("data"))
			return 0;

		return parseUInt();
	}

	int WavFile::get()
	{
		--m_remaining;
		return File::get();
	}
}
