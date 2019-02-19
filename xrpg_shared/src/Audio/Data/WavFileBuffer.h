//
// Created by xgallom on 2/18/19.
//

#ifndef XRPG_WAVFILEBUFFER_H
#define XRPG_WAVFILEBUFFER_H

#include "WavFile.h"

#include "DataInfo.h"

#include <memory>

namespace Audio::Data
{
	class WavFileBuffer {
	public:
		explicit WavFileBuffer(const std::string &fileName);

		bool prepare();
		Buffer getBuffer() const;

	private:
		std::unique_ptr<WavFile> m_wavFile;
		WavFileInfo m_fileInfo = {};
		std::vector<int16_t> m_data = {};
	};
}

#endif //XRPG_WAVFILEBUFFER_H
