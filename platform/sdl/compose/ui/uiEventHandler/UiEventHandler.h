//
// Created by EinoPlasma on 2024/5/6.
//

#ifndef LIGHTSONG_UIEVENTHANDLER_H
#define LIGHTSONG_UIEVENTHANDLER_H

#include "../UiEvent.h"
#include "memory"
#include "../../../../../core/Director.h"

namespace sdl {

    class UiEventHandler {
    public:
        virtual bool shouldDeactivate() = 0;
        virtual void handleUiEvent(std::unique_ptr<UiEvent> uiEvent, std::shared_ptr<core::Director> director) = 0;
    };

} // sdl

#endif //LIGHTSONG_UIEVENTHANDLER_H
