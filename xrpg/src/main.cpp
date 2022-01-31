#include <core/error.h>
#include <SDL.h>
#include "run/run.h"
#include <core/ticks.h>

#include <graphics/color-palette.h>

void hardLight(uint8_t *__restrict dest, const uint8_t *__restrict src, size_t count)
{
    do {
        // b1: 1 - Target
        // b2: 1 - 2 * (Blend - 0.5)
        // b12: b1 * b2
        // bigger: (Blend > 0.5) * (1 - b12)
        //
        // s1: Target
        // s2: 2 * Blend
        // s12: s1 * s2
        // smaller: (Blend <= 0.5) * s12
        const int
                s = *src++,
                d = *dest,

                b1 = 255 - d,
                b2 = 255 - 2 * (s - 127),
                b12 = b1 * b2 / 255,
                bigger = (s > 127) * (255 - b12),

                s1 = d,
                s2 = 2 * s,
                s12 = s1 * s2 / 255,
                smaller = (s <= 127) * s12;

        *dest++ = uint8_t(std::min(bigger + smaller, 255));
    } while (--count);
}

void hardLight(
        uint8_t *__restrict into,
        const uint8_t *__restrict dest,
        const uint8_t *__restrict src,
        size_t count)
{
    do {
        // b1: 1 - Target
        // b2: 1 - 2 * (Blend - 0.5)
        // b12: b1 * b2
        // bigger: (Blend > 0.5) * (1 - b12)
        //
        // s1: Target
        // s2: 2 * Blend
        // s12: s1 * s2
        // smaller: (Blend <= 0.5) * s12
        const int
                s = *src++,
                d = *dest++,

                b1 = 255 - d,
                b2 = 255 - 2 * (s - 127),
                b12 = b1 * b2 / 255,
                bigger = (s > 127) * (255 - b12),

                s1 = d,
                s2 = 2 * s,
                s12 = s1 * s2 / 255,
                smaller = (s <= 127) * s12;

        *into++ = uint8_t(std::min(bigger + smaller, 255));
    } while (--count);
}

void prepare(Engine &engine)
{
    auto imagePixels = reinterpret_cast<uint32_t *>(engine.font->pixels);
    auto pixels = reinterpret_cast<uint32_t *>(engine.environment->pixels);
    auto light = reinterpret_cast<uint32_t *>(engine.light->pixels);

    Ticks now = Ticks::now();
    auto n = 0;
    for (auto y = 0; y < engine.screenH; ++y) {
        for (auto row = 0; row < 16; ++row) {
            const auto pxY = (y % 16) * 16 + row;
            for (auto x = 0; x < engine.screenW; ++x) {
                memcpy(light + n, graphics::RowColorPalette[(y * engine.screenW + x) % 256], sizeof(uint32_t) * 16);
                for (auto col = 0; col < 16; ++col) {
                    const auto pxX = (x % 16) * 16 + col;
                    auto m = pxY * 256 + pxX;
                    pixels[n] = imagePixels[m];
//                    pixels[n] = 0;
//                    light[n] = graphics::ColorPalette[200];
                    ++n;
                }
            }
        }
    }
    printf("%llu\n", now.reset());
}

void redraw(Engine &engine)
{
    const auto preLight = reinterpret_cast<const uint8_t *>(engine.environment->pixels);
    const auto light = reinterpret_cast<const uint8_t *>(engine.light->pixels);

    uint8_t *pixels;
    int pitch;
    SDL_LockTexture(engine.output, nullptr, reinterpret_cast<void **>(&pixels), &pitch);
    hardLight(pixels, preLight, light, size_t(pitch) * size_t(engine.screenPxH()));
    SDL_UnlockTexture(engine.output);

/*
    SDL_UpdateTexture(
            engine.output,
            nullptr,
            engine.outSurface->pixels,
            engine.outSurface->pitch
    );
*/
}

int main()
{
    Engine engine;

    printf("%llu\n", sizeof(engine));
    std::vector<uint64_t> fps;
    fps.reserve(1024 * 1024);
    if (engine.init()) {
        prepare(engine);

        auto lastRender = Ticks::now();
        while (true) {
            SDL_Event e;
            while (SDL_PollEvent(&e)) {
                switch (e.type) {
                    case SDL_QUIT:
                        uint64_t fpsVal = 0;
                        for (const auto &v: fps)
                            fpsVal += v;
                        printf("%llu %llu\n", fps.size(), fpsVal / fps.size());
                        return 0;
                }
            }

            redraw(engine);

            SDL_RenderCopy(engine.renderer, engine.output, nullptr, nullptr);
            SDL_RenderPresent(engine.renderer);
            fps.push_back(1000 / lastRender.reset());
        }
    } else
        printSdlError();

    return 0;
}
