//
// Created by gallo on 24-Jan-22.
//

#include <engine/renderer.h>
#include "config.h"
#include "graphics/color-palette.h"
#include <SDL_surface.h>

namespace engine {
    bool Renderer::init()
    {
        graphics::initColorPalette();

        const auto initFlags = uint32_t(IMG_Init(Config::ImgFlags));
        if ((initFlags & Config::ImgFlags) != Config::ImgFlags)
            return false;

        window = SDL_CreateWindow(
                "XRpg",
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                800,
                600,
                /*SDL_WINDOW_FULLSCREEN_DESKTOP |*/ SDL_WINDOW_ALLOW_HIGHDPI
        );
        if (!window)
            return false;

        renderer = SDL_CreateRenderer(
                window,
                -1,
                SDL_RENDERER_ACCELERATED /*| SDL_RENDERER_PRESENTVSYNC*/
        );
        if (!renderer)
            return false;

        return prepareRenderer()
               && loadFont()
               && setViewport()
               && createOutput();
    }

    void Renderer::deinit()
    {
        if (renderer)
            SDL_DestroyRenderer(renderer);
        if (window)
            SDL_DestroyWindow(window);

        IMG_Quit();
    }

    bool Renderer::prepareRenderer()
    {
        bool wasSuccessful = !SDL_RenderSetIntegerScale(renderer, SDL_TRUE)
                             && !SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE)
                             && !SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
        return wasSuccessful;
    }

    bool Renderer::loadFont()
    {
        const auto glyphs = IMG_Load("assets/img/glyphs-16x16.png");
        if (glyphs) {
            font = SDL_ConvertSurfaceFormat(glyphs, Config::PixelFormat, 0);
            SDL_SetSurfaceBlendMode(font, SDL_BLENDMODE_NONE);
        }
        return font;
    }

    bool Renderer::setViewport()
    {
        SDL_Rect viewport;
        SDL_RenderGetViewport(renderer, &viewport);

        // Half resolution
/*
        screenW = (viewport.w - viewport.x) / 16 / 2;
        screenH = (viewport.h - viewport.y) / 16 / 2;
        const auto
                pxW = screenW * 16 * 2,
                pxH = screenH * 16 * 2;
*/
        // Full resolution
        screenW = (viewport.w - viewport.x) / 16;
        screenH = (viewport.h - viewport.y) / 16;
        const auto
                pxW = screenW * 16,
                pxH = screenH * 16;

        viewport = {
                (viewport.w - pxW) / 2,
                (viewport.h - pxH) / 2,
                pxW,
                pxH
        };

        return !SDL_RenderSetViewport(renderer, &viewport);
    }

    bool Renderer::createOutput()
    {
        environment = SDL_CreateRGBSurfaceWithFormat(
                0,
                screenPxW(),
                screenPxH(),
                Config::PixelDepth,
                Config::PixelFormat
        );
        SDL_SetSurfaceBlendMode(environment, SDL_BLENDMODE_NONE);

        light = SDL_CreateRGBSurfaceWithFormat(
                0,
                screenPxW(),
                screenPxH(),
                Config::PixelDepth,
                Config::PixelFormat
        );
        SDL_SetSurfaceBlendMode(light, SDL_BLENDMODE_NONE);

        output = SDL_CreateTexture(
                renderer,
                Config::PixelFormat,
                SDL_TEXTUREACCESS_STREAMING,
                screenPxW(),
                screenPxH()
        );
        SDL_SetTextureBlendMode(output, SDL_BLENDMODE_NONE);

        return environment && light && output;
    }
}
