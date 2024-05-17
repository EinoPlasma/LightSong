//
// Created by EinoPlasma on 2024/5/5.
//

#ifndef LIGHTSONG_SDLUTILS_H
#define LIGHTSONG_SDLUTILS_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"

namespace sdl {

    SDL_Texture* concatenateTextures(SDL_Renderer* renderer, SDL_Texture* texture1, SDL_Texture* texture2);
    SDL_Rect makeRenderRect(int centerXPercent, int centerYPercent, unsigned int screenWidth, unsigned int screenHeight, unsigned int textureWidth, unsigned int textureHeight);
    void convertHexToSDLColor(const std::string& colorCode, SDL_Color* sdlColor);

    SDL_Texture* autoLoadImg(std::string path, SDL_Renderer* renderer);

    SDL_Texture* MaskTexture(SDL_Renderer* renderer, SDL_Texture* &mask, SDL_Texture* &diffuse);

} // sdl

bool isMixGroupPlaying(int mixGroupTag);



#endif //LIGHTSONG_SDLUTILS_H
