//
// Created by xgallom on 2/17/19.
//

#ifndef XRPG_AUDIODATAINFO_H
#define XRPG_AUDIODATAINFO_H

#include <cstdint>
#include <vector>

namespace Audio::Data
{
	static constexpr uint16_t
			ChannelCountMono = 1,
			ChannelCountStereo = 2;

	struct DataInfo {
		uint32_t sampleRate = 0;
		uint16_t channelCount = 0;
	};

	struct Buffer {
		DataInfo dataInfo = {};
		const int16_t *index = nullptr;

		struct {
			const int16_t *begin = nullptr;
			const int16_t *end = nullptr;

			inline size_t size() const { return static_cast<size_t>(end - begin); }
		} data = {};
	};

	struct StreamChunk {
		DataInfo dataInfo = {};
		std::vector<int16_t> data = {};

		StreamChunk() = default;
		explicit StreamChunk(const DataInfo &a_dataInfo) : dataInfo{a_dataInfo} {}
	};
}

#endif //XRPG_DATAINFO_H
