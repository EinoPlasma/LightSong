//
// Created by EinoPlasma on 2024/5/5.
//

#include <stdexcept>
#include <sstream>
#include <SDL_image.h>
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

    void convertHexToSDLColor(const std::string& colorCode, SDL_Color* sdlColor) {
        if (colorCode.size() != 7 || colorCode[0] != '#') {
            throw std::runtime_error("Invalid color code: " + colorCode);
        }

        std::string colorStr = colorCode.substr(1);  // 去除 # 符号
        std::stringstream ss;
        ss << std::hex << colorStr;
        unsigned int colorValue;
        ss >> colorValue;

        sdlColor->r = (colorValue >> 16) & 0xFF;
        sdlColor->g = (colorValue >> 8) & 0xFF;
        sdlColor->b = colorValue & 0xFF;
        // sdlColor->a = 0xFF;  // 默认不透明
    }

    SDL_Texture* MaskTexture(SDL_Renderer* renderer, SDL_Texture* &mask, SDL_Texture* &diffuse)
    {
        // from: https://www.reddit.com/r/sdl/comments/ndeq7s/solved_how_to_mask_a_texture_in_sdl/
        int resWidth, resHeight;
        SDL_Rect resRect = {0,0,-1,-1};
        SDL_QueryTexture(mask, nullptr, nullptr, &resRect.w, &resRect.h);
        SDL_Texture* result = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, resRect.w, resRect.h);
        SDL_SetTextureBlendMode(result, SDL_BLENDMODE_BLEND);

        SDL_Texture* previousTarget = SDL_GetRenderTarget(renderer);
        SDL_SetRenderTarget(renderer, result);
        SDL_SetTextureBlendMode(mask, SDL_BLENDMODE_MOD);
        SDL_SetTextureBlendMode(diffuse, SDL_BLENDMODE_NONE);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, diffuse, &resRect, &resRect);
        SDL_RenderCopy(renderer, mask, &resRect, &resRect);

        SDL_SetRenderTarget(renderer, previousTarget);
        // SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);
        // SDL_RenderClear(renderer);

        return result;
    }

    SDL_Texture* autoLoadImg(std::string path, SDL_Renderer* renderer) {
        // 尝试加载原始图像文件
        SDL_Surface* surface = IMG_Load(path.c_str());
        if (surface == nullptr) {
            // 加载失败，输出错误信息并返回空纹理
            throw std::runtime_error("Failed to load image: " + path);
        }

        // 创建纹理
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);

        // 获取文件路径的前缀和后缀
        std::string directory = path.substr(0, path.find_last_of("/\\") + 1);
        std::string filename = path.substr(path.find_last_of("/\\") + 1);
        std::string basename = filename.substr(0, filename.find_last_of('.'));
        std::string extension = filename.substr(filename.find_last_of('.') + 1);

        // 尝试加载对应的 _mask 文件
        std::string maskPath = directory + basename + "_mask." + extension;
        // SDL_Surface* maskSurface = IMG_Load(maskPath.c_str());
        SDL_Texture* maskTexture = IMG_LoadTexture(renderer, maskPath.c_str());
        if (maskTexture != nullptr) {
//            // 设置纹理的混合模式为反色（invert）
////            SDL_SetTextureBlendMode(maskTexture, SDL_BLENDMODE_ADD);
////            SDL_SetTextureColorMod(maskTexture, 255, 255, 255);  // 设置纹理的颜色为白色
//
//            SDL_Texture* masked = MaskTexture(renderer, texture, maskTexture);
//            SDL_DestroyTexture(texture);
//            SDL_DestroyTexture(maskTexture);
//            return masked;
            SDL_Log("Warning: Mask image not found for %s", path.c_str());
        }

        return texture;
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


