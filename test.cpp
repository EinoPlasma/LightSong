//
// Created by EinoPlasma on 2024/5/9.
//


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Texture* MaskTexture(SDL_Renderer* renderer, SDL_Texture* &mask, SDL_Texture* &diffuse) {
    SDL_Texture* result = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 300, 300);
    SDL_SetTextureBlendMode(result, SDL_BLENDMODE_BLEND);

    SDL_SetRenderTarget(renderer, result);
    SDL_SetTextureBlendMode(mask, SDL_BLENDMODE_MOD);
    SDL_SetTextureBlendMode(diffuse, SDL_BLENDMODE_NONE);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, diffuse, NULL, NULL);
    SDL_RenderCopy(renderer, mask, NULL, NULL);

    SDL_SetRenderTarget(renderer, NULL);
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);
    SDL_RenderClear(renderer);

    return result;
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Texture Masking", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 300, 300, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Surface* SurfaceA = IMG_Load("A.png");
    SDL_Surface* SurfaceB = IMG_Load("B.png");

    SDL_Texture* TextureA = SDL_CreateTextureFromSurface(renderer, SurfaceA);
    SDL_Texture* TextureB = SDL_CreateTextureFromSurface(renderer, SurfaceB);

    SDL_Texture* TextureC = MaskTexture(renderer, TextureA, TextureB);

    SDL_Surface* SurfaceD = IMG_Load("D.png");
    SDL_Texture* TextureD = SDL_CreateTextureFromSurface(renderer, SurfaceD);

    SDL_RenderCopy(renderer, TextureD, NULL, NULL);
    SDL_RenderCopy(renderer, TextureC, NULL, NULL);

    SDL_RenderPresent(renderer);

    bool quit = false;
    SDL_Event event;

    while (!quit) {
        SDL_PollEvent(&event);

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
            }
        }

        SDL_Delay(100);
    }

    SDL_FreeSurface(SurfaceA);
    SDL_FreeSurface(SurfaceB);
    SDL_FreeSurface(SurfaceD);

    SDL_DestroyTexture(TextureA);
    SDL_DestroyTexture(TextureB);
    SDL_DestroyTexture(TextureC);
    SDL_DestroyTexture(TextureD);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}