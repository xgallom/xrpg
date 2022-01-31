//
// Created by gallo on 24-Jan-22.
//

#ifndef XRPG_XRPG_SHARED_INCLUDE_ENGINE_AUDIO_H
#define XRPG_XRPG_SHARED_INCLUDE_ENGINE_AUDIO_H

#include "engine-data.h"

namespace engine {
    struct Audio : EngineData {
        bool init();
        void deinit();
    };
}

#endif //XRPG_XRPG_SHARED_INCLUDE_ENGINE_AUDIO_H
