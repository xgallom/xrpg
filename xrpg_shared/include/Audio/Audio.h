//
// Created by xgallom on 2/16/19.
//

#ifndef XRPG_AUDIO_H
#define XRPG_AUDIO_H

#include "Storage/Music.h"

namespace Audio
{
	bool init();
	void deinit();

	bool start();
	bool stop();

	void addMusic(::Music::Enum music);
}

#endif //XRPG_AUDIO_H
