//
// Created by EinoPlasma on 2024/5/1.
//

#include "SDL2/SDL.h"

// make a window
SDL_Window *windowInit() {
    // return SDL_CreateWindow("LightSong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
}


int main(int argc, char **argv) {
    SDL_Window* window = nullptr;

    SDL_Renderer* render = nullptr;

    window = SDL_CreateWindow("LightSong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);

    SDL_Texture* HelloTex = nullptr;

    SDL_Surface* surface = nullptr;

    SDL_Delay(10000);


    return 0;
}