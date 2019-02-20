//
// Created by xgallom on 2/16/19.
//

#ifndef XRPG_AUDIOSTREAM_H
#define XRPG_AUDIOSTREAM_H

namespace Audio
{
	bool openDefaultStream();
	bool startStream();
	bool stopStream();
	bool closeStream();

	unsigned long framesPerAudioBuffer();
}

#endif //XRPG_AUDIOSTREAM_H
