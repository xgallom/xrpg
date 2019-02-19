//
// Created by xgallom on 2/17/19.
//

#ifndef XRPG_WAVFILESTREAM_H
#define XRPG_WAVFILESTREAM_H

#include "WavFile.h"

#include "DataInfo.h"

#include <memory>

namespace Audio::Data
{
	struct WavFileStream {
		explicit WavFileStream(const std::string &fileName);

		bool prepare();
		std::unique_ptr<StreamChunk> getChunk();


	private:
		uint32_t chunkSize() const;

		WavFile m_wavFile;
		WavFileInfo m_fileInfo = {};
		std::vector<int16_t> m_data = {};
	};
}

#endif //XRPG_WAVFILESTREAM_H
