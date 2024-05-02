//
// Created by EinoPlasma on 2024/5/1.
//

#include "Interface.h"

namespace sdl {

    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> Interface::loadImageAsTexture(const char* path) {
        // return {IMG_LoadTexture(renderer.get(), path), SDL_DestroyTexture};
    }

    Interface::Interface(const char *root_path){
        this->root_path = root_path;
        director = std::make_unique<core::Director>(this->root_path);

        winTitle = director->getConfig().gametitle;
        screenWidth = director->getConfig().imagesize_width;
        screenHeight = director->getConfig().imagesize_height;
    }
} // sdl