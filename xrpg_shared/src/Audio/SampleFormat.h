//
// Created by xgallom on 2/16/19.
//

#ifndef XRPG_SAMPLEFORMAT_H
#define XRPG_SAMPLEFORMAT_H

#include <portaudio.h>

namespace Audio
{
	namespace SampleFormat
	{
		enum Enum : PaSampleFormat {
			Float32 = 0x00000001 /* paFloat32 */
		};
	}
}

#endif //XRPG_SAMPLEFORMAT_H
