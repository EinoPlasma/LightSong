//
// Created by EinoPlasma on 2024/5/1.
//

#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "core/GameConfig.h"

#include "core/Director.h"


int main(int argc, char **argv) {

    system("chcp 65001");

    std::unique_ptr<core::Director> director = std::make_unique<core::Director>(R"(C:\LightSong\reference\games\Ever17\s60v5\Ever17)");

    std::string winTitle = director->getConfig().gametitle;
    int screenWidth = director->getConfig().imagesize_width;
    int screenHeight = director->getConfig().imagesize_height;

    // init a window, then display R"(C:\LightSong\reference\games\Ever17\s60v5\Ever17\chara\sa04awl.bmp)"

    SDL_Window *window = SDL_CreateWindow(winTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);

    SDL_Renderer *render = SDL_CreateRenderer(window, -1, 0);

    SDL_Texture *helloTex = SDL_CreateTextureFromSurface(render, IMG_Load(R"(C:\LightSong\reference\games\Ever17\s60v5\Ever17\chara\sa04awl.png)"));

    SDL_RenderClear(render);

    SDL_RenderCopy(render, helloTex, nullptr, nullptr);

    SDL_RenderPresent(render);

    std::cout << "Echo test" << std::endl;

    SDL_Delay(10000);

    SDL_DestroyTexture(helloTex);

    SDL_DestroyRenderer(render);

    SDL_DestroyWindow(window);

    SDL_Quit();


    return 0;
}