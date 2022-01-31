//
// Created by gallo on 27-Jan-22.
//

#ifndef XRPG_XRPG_SHARED_INCLUDE_ECS_META_TYPE_H
#define XRPG_XRPG_SHARED_INCLUDE_ECS_META_TYPE_H

namespace ecs::meta {
    template<typename T_>
    struct Type {
        using T = T_;
    };
}

#endif //XRPG_XRPG_SHARED_INCLUDE_ECS_META_TYPE_H
