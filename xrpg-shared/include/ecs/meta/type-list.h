//
// Created by gallo on 27-Jan-22.
//

#ifndef XRPG_XRPG_SHARED_INCLUDE_ECS_META_TYPE_LIST_H
#define XRPG_XRPG_SHARED_INCLUDE_ECS_META_TYPE_LIST_H

namespace ecs::meta {
    template<typename ... Ts>
    struct TypeList {
        static constexpr auto size = sizeof ...(Ts);
    };
}

#endif //XRPG_XRPG_SHARED_INCLUDE_ECS_META_TYPE_LIST_H
