//
// Created by gallo on 27-Jan-22.
//

#ifndef XRPG_XRPG_SHARED_INCLUDE_ECS_META_INDEX_OF_H
#define XRPG_XRPG_SHARED_INCLUDE_ECS_META_INDEX_OF_H

#include <type_traits>
#include "type-list.h"

namespace ecs::meta {
    template<typename T, typename TypeList>
    struct IndexOf;

    template<typename T, typename ... Ts>
    struct IndexOf<T, TypeList<T, Ts ...>> :
            std::integral_constant<std::size_t, 0> {
    };

    template<typename T, typename T2, typename ... Ts>
    struct IndexOf<T, TypeList<T2, Ts ...>> :
            std::integral_constant<std::size_t, 1 + IndexOf<T, TypeList<Ts ...>>::value> {
    };

}

#endif //XRPG_XRPG_SHARED_INCLUDE_ECS_META_INDEX_OF_H
