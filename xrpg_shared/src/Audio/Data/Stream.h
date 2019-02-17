//
// Created by xgallom on 2/17/19.
//

#ifndef XRPG_AUDIODATASTREAM_H
#define XRPG_AUDIODATASTREAM_H

#include "File.h"

#include "DataInfo.h"

#include <vector>

namespace Audio::Data
{
	struct StreamChunk {
		DataInfo dataInfo = {};
		std::vector<int16_t> data = {};
	};

	struct WavFileStream {
		explicit WavFileStream(const std::string &fileName);

		bool prepare();
		StreamChunk getChunk();


	private:
		uint32_t chunkSize() const;

		WavFile m_wavFile;
		WavFileInfo m_fileInfo = {};
		std::vector<int16_t> m_data = {};
	};
}

#endif //XRPG_STREAM_H
