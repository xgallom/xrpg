//
// Created by xgallom on 2/18/19.
//

#ifndef XRPG_AUDIOTHREAD_H
#define XRPG_AUDIOTHREAD_H

#include "Data/DataInfo.h"
#include "Util/AtomicStream.h"

namespace Audio
{
	namespace AudioThread
	{
		void start();
		void stop();

		AtomicStream<Data::StreamChunk> &getAudioStream();
		AtomicBuffer<Data::Buffer> &getAudioBuffer();
	}
}

#endif //XRPG_AUDIOTHREAD_H
