//
// Created by gallo on 24-Jan-22.
//

#ifndef XRPG_XRPG_SHARED_INCLUDE_ENGINE_EVENTS_H
#define XRPG_XRPG_SHARED_INCLUDE_ENGINE_EVENTS_H

#include "engine-data.h"

namespace engine {
    struct Events : EngineData {
        bool init();
        void pollEvents();
    };
}

#endif //XRPG_XRPG_SHARED_INCLUDE_ENGINE_EVENTS_H
