//
// Created by gallo on 27-Jan-22.
//

#ifndef XRPG_XRPG_SHARED_INCLUDE_ECS_COMPONENTS_COMPONENTS_H
#define XRPG_XRPG_SHARED_INCLUDE_ECS_COMPONENTS_COMPONENTS_H

#include <cstdint>

namespace ecs {
    namespace Tags {
        enum Enum : uint32_t {
            Exists,
        };

        static constexpr auto Size = Exists + 1u;
    }

    namespace Components {
        enum Enum : uint32_t {
            Position = Tags::Size,
        };

        static constexpr auto Size = Position + 1u;
    }
}

#endif //XRPG_XRPG_SHARED_INCLUDE_ECS_COMPONENTS_COMPONENTS_H
