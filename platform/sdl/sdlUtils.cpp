//
// Created by EinoPlasma on 2024/5/5.
//

#include "sdlUtils.h"

namespace sdl {

    SDL_Texture* concatenateTextures(SDL_Renderer* renderer, SDL_Texture* texture1, SDL_Texture* texture2) {
        int width1, height1;
        SDL_QueryTexture(texture1, NULL, NULL, &width1, &height1);

        int width2, height2;
        SDL_QueryTexture(texture2, NULL, NULL, &width2, &height2);

        int targetWidth = width1 + width2;
        int targetHeight = (height1 > height2) ? height1 : height2;

        SDL_Texture* targetTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, targetWidth, targetHeight);

        auto rect1 = (SDL_Rect){0, 0, width1, targetHeight};
        auto rect2 = (SDL_Rect){width1, 0, width2, targetHeight};

        SDL_SetRenderTarget(renderer, targetTexture);
        SDL_RenderCopy(renderer, texture1, NULL, &rect1);
        SDL_RenderCopy(renderer, texture2, NULL, &rect2);
        SDL_SetRenderTarget(renderer, NULL);

        return targetTexture;
    }
} // sdl