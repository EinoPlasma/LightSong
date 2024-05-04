//
// Created by EinoPlasma on 2024/5/5.
//

#ifndef LIGHTSONG_COMPOSER_H
#define LIGHTSONG_COMPOSER_H

#include <SDL2/SDL.h>

namespace sdl {

    class Composer {
    private:
        SDL_Renderer* renderer = nullptr;
    public:
        virtual void update(unsigned int dt) = 0;
        virtual void render() = 0;
    };

} // sdl

#endif //LIGHTSONG_COMPOSER_H
