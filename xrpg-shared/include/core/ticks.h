//
// Created by gallo on 23-Jan-22.
//

#ifndef XRPG_XRPG_SHARED_INCLUDE_CORE_TICKS_H
#define XRPG_XRPG_SHARED_INCLUDE_CORE_TICKS_H

#include <cstdint>

struct Ticks {
    uint64_t value;

    uint64_t reset();
    bool interval(Ticks duration, Ticks ticksNow = now());
    static Ticks now();

    constexpr operator uint64_t() const { return value; }
};


#endif //XRPG_XRPG_SHARED_INCLUDE_CORE_TICKS_H
