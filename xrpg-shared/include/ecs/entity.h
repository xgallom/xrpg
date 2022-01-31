//
// Created by gallo on 27-Jan-22.
//

#ifndef XRPG_XRPG_SHARED_INCLUDE_ECS_ENTITY_H
#define XRPG_XRPG_SHARED_INCLUDE_ECS_ENTITY_H

#include <bitset>
#include "components/components.h"

namespace ecs {
    struct Entity {
        std::bitset<Components::Size> flags;

        template<Components::Enum Pos>

    };
}

#endif //XRPG_XRPG_SHARED_INCLUDE_ECS_ENTITY_H
