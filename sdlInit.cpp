//
// Created by EinoPlasma on 2024/5/1.
//

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

// make a window
SDL_Window *windowInit() {
    return SDL_CreateWindow("LightSong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
}


int main(int argc, char **argv) {
    // init a window, then display R"(C:\LightSong\reference\games\Ever17\s60v5\Ever17\chara\sa04awl.bmp)"

    SDL_Window *window = windowInit();

    SDL_Renderer *render = SDL_CreateRenderer(window, -1, 0);

    SDL_Texture *helloTex = SDL_CreateTextureFromSurface(render, IMG_Load(R"(C:\LightSong\reference\games\Ever17\s60v5\Ever17\chara\sa04awl.png)"));

    SDL_RenderClear(render);

    SDL_RenderCopy(render, helloTex, nullptr, nullptr);

    SDL_RenderPresent(render);

    SDL_Delay(10000);

    SDL_DestroyTexture(helloTex);

    SDL_DestroyRenderer(render);

    SDL_DestroyWindow(window);

    SDL_Quit();



//    SDL_Window* window = nullptr;
//
//    SDL_Renderer* render = nullptr;
//
//    window = SDL_CreateWindow("LightSong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
//
//    SDL_Texture* helloTex = nullptr;
//
//    SDL_Surface* surface = nullptr;
//
//    surface = SDL_LoadBMP(R"(C:\LightSong\reference\games\Ever17\s60v5\Ever17\chara\sa04awl.bmp)");
//
//
//
//    helloTex = SDL_CreateTextureFromSurface(render, surface);
//
//    SDL_FreeSurface(surface);
//
//    SDL_RenderClear(render);
//
//    SDL_RenderCopy(render, helloTex, nullptr, nullptr);
//
//    SDL_RenderPresent(render);
//
//    SDL_Delay(10000);
//
//    SDL_DestroyTexture(helloTex);
//
//    SDL_DestroyRenderer(render);
//
//    SDL_DestroyWindow(window);
//
//    SDL_Quit();


    return 0;
}