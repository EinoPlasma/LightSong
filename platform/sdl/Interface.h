//
// Created by EinoPlasma on 2024/5/1.
//

#ifndef LIGHTSONG_INTERFACE_H
#define LIGHTSONG_INTERFACE_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "memory"
#include "../../core/Director.h"

namespace sdl {

    class Interface {
    private:
        // game logic
        std::string root_path;
        std::unique_ptr<core::Director> director = nullptr;
        // rendering
        // SDL_Window* window; // Interface只用window，不负责关
        // SDL_Renderer* renderer; // Interface只用renderer，不负责关
        // TTF_Font* font;
//        std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> font;
//        // Mix_Music* backgroundMusic_;
//        // TODO: 设计mixer类管理音量等设置
//        std::unique_ptr<Mix_Music, decltype(&Mix_FreeMusic)> backgroundMusic;

        // animation
        // event
        // sound
    public:
        std::string winTitle;
        int screenWidth;
        int screenHeight;

        explicit Interface(const char* root_path);

        std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> loadImageAsTexture(const char* path);


    };

    // make a function load a audio file as a chunk
    std::unique_ptr<Mix_Chunk, decltype(&Mix_FreeChunk)> loadSound(const char* path);



} // sdl

#endif //LIGHTSONG_INTERFACE_H
