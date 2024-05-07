//
// Created by EinoPlasma on 2024/5/5.
//

#include <stdexcept>
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

    SDL_Rect
    makeRenderRect(int centerXPercent, int centerYPercent, unsigned int screenWidth, unsigned int screenHeight,
                        unsigned int textureWidth, unsigned int textureHeight) {
        // 返回一个通过一texture中点在屏幕上的位置的百分比来定义的XY坐标指定的renderRect
        if (abs(centerXPercent) > 100 || abs(centerYPercent) > 100) {
            throw std::runtime_error("invalid centerXPercent or centerYPercent");
        }
        if (centerXPercent < 0 || centerYPercent < 0) {
            SDL_Log("Warning: centerXPercent or centerYPercent is less than zero");
        }

        SDL_Rect renderRect;
        renderRect.w = textureWidth;
        renderRect.h = textureHeight;

        renderRect.x = (int) (((float)screenWidth * centerXPercent / 100.0) - textureWidth / 2.0);
        renderRect.y = (int) (((float)screenHeight * centerYPercent / 100.0) - textureHeight / 2.0);

        return renderRect;
    }



} // sdl


bool isMixGroupPlaying(int mixGroupTag) {
    int channels = Mix_GroupCount(mixGroupTag);
    if (channels == 0) {
        return false;
    }

    // TODO: 目前本函数仅能检测最新的那个通道，如果有多个通道，需要改进
    int channel = Mix_GroupNewer(mixGroupTag);
    if (channel != -1 && Mix_Playing(channel) != 0) {
        return true;
    }

    return false;
}