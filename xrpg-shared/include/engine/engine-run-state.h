//
// Created by gallo on 24-Jan-22.
//

#ifndef XRPG_XRPG_SHARED_INCLUDE_ENGINE_ENGINE_RUN_STATE_H
#define XRPG_XRPG_SHARED_INCLUDE_ENGINE_ENGINE_RUN_STATE_H

#include "renderer.h"

struct EngineRunState;

namespace engine {
//    using RunHandlerId = uint32_t;
    template<typename ...Args>
    using RunHandler = void (EngineRunState::*)(Args ...args);
/*    using RunHandlers = const RunHandler *;

    template<typename T>
    constexpr RunHandler update() { return RunHandler(&T::update); }
    template<typename T>
    constexpr RunHandler render() { return RunHandler(&T::render); }

    template<typename ...Ts>
    struct RunHandlersData {
        RunHandler updateHandlers[sizeof...(Ts)], renderHandlers[sizeof...(Ts)];
        constexpr RunHandlersData() :
                updateHandlers{update<Ts>() ...},
                renderHandlers{render<Ts>() ...} {}
    };

    namespace EngineRunHandlerId {
        enum Enum : RunHandlerId {
            Start,
            Quit,
            Custom
        };
    }
*/

    struct EngineData : Renderer, Events {
    };
}

struct EngineRunState : engine::EngineData {
    template<typename U>
    inline U &as() { return reinterpret_cast<U &>(*this); }
};

#endif //XRPG_XRPG_SHARED_INCLUDE_ENGINE_ENGINE_RUN_STATE_H
