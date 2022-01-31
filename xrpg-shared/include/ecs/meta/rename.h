//
// Created by gallo on 27-Jan-22.
//

#ifndef XRPG_XRPG_SHARED_INCLUDE_ECS_META_RENAME_H
#define XRPG_XRPG_SHARED_INCLUDE_ECS_META_RENAME_H

#include "type.h"

namespace ecs::meta {
    template<template<typename ...> typename New, typename Old>
    struct RenameImpl;

    template<template<typename ...> typename New,
            template<typename ...> typename Old, typename ... Ts>
    struct RenameImpl<New, Old<Ts ...>> : Type<New<Ts ...>> {
    };

    template<template<typename ...> typename New, typename Old>
    using Rename = typename RenameImpl<New, Old>::T;
}

#endif //XRPG_XRPG_SHARED_INCLUDE_ECS_META_RENAME_H
