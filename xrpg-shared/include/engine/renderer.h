//
// Created by gallo on 24-Jan-22.
//

#ifndef XRPG_XRPG_SHARED_INCLUDE_ENGINE_RENDERER_H
#define XRPG_XRPG_SHARED_INCLUDE_ENGINE_RENDERER_H

#include "engine-data.h"

namespace engine {
    struct Renderer : EngineData {
        bool init();
        void deinit();

    private:
        bool prepareRenderer();
        bool loadFont();
        bool setViewport();
        bool createOutput();
    };
}

#endif //XRPG_XRPG_SHARED_INCLUDE_ENGINE_RENDERER_H
