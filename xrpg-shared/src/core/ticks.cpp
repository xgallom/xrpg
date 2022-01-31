//
// Created by gallo on 23-Jan-22.
//

#include <core/ticks.h>
#include <SDL_timer.h>

Ticks Ticks::now()
{
    return Ticks{SDL_GetTicks64()};
}

uint64_t Ticks::reset()
{
    const auto tmp = value;
    return (value = now().value) - tmp;
}

bool Ticks::interval(Ticks duration, Ticks ticksNow)
{
    const auto didTrigger = ticksNow >= value;
    if (didTrigger)
        value = uint64_t(now) + duration;
    return didTrigger;
}
