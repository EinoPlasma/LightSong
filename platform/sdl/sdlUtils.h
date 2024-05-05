//
// Created by EinoPlasma on 2024/5/5.
//

#ifndef LIGHTSONG_SDLUTILS_H
#define LIGHTSONG_SDLUTILS_H

#include "SDL2/SDL.h"

namespace sdl {

    SDL_Texture* concatenateTextures(SDL_Renderer* renderer, SDL_Texture* texture1, SDL_Texture* texture2);
    SDL_Rect makeRenderRect(int centerXPercent, int centerYPercent, unsigned int screenWidth, unsigned int screenHeight, unsigned int textureWidth, unsigned int textureHeight);
} // sdl

#endif //LIGHTSONG_SDLUTILS_H
