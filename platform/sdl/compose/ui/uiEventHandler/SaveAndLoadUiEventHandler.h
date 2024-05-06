//
// Created by EinoPlasma on 2024/5/6.
//

#ifndef LIGHTSONG_SAVEANDLOADUIEVENTHANDLER_H
#define LIGHTSONG_SAVEANDLOADUIEVENTHANDLER_H

#include "UiEventHandler.h"

#include <utility>
#include "../../../../../core/Director.h"

namespace sdl {

    class SaveAndLoadUiEventHandler : public UiEventHandler {
    private:
        bool flagShouldDeactivate = false;
        void deactivateUi() {flagShouldDeactivate = true;}
    public:
        bool shouldDeactivate() override {return flagShouldDeactivate;};
        void handleUiEvent(std::unique_ptr<UiEvent> uiEvent, std::shared_ptr<core::Director> director) override;
    };

} // sdl

#endif //LIGHTSONG_SAVEANDLOADUIEVENTHANDLER_H
