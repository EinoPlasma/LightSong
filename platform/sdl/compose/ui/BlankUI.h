//
// Created by EinoPlasma on 2024/5/5.
//

#ifndef LIGHTSONG_BLANKUI_H
#define LIGHTSONG_BLANKUI_H

#include "UI.h"

namespace sdl {

    class BlankUI : public UI {
    private:
        void handleUiEvents() {};
    public:
        void render() override {};
        void update(unsigned int dt) override {};
        void handleSdlEvent(const SDL_Event *event) override {};
        bool isUiAlive() override { return false; };
    };

} // sdl

#endif //LIGHTSONG_BLANKUI_H
