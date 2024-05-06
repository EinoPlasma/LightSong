//
// Created by EinoPlasma on 2024/5/6.
//

#ifndef LIGHTSONG_SAVEANDLOADUIEVENTHANDLER_H
#define LIGHTSONG_SAVEANDLOADUIEVENTHANDLER_H

#include "UiEventHandler.h"

#include <utility>
#include "../../../../../core/Director.h"

namespace sdl {
    /*
     * 接受UiEventType::BUTTON_LEFT_CLICK事件，接受一个std::string参数，参数放在UiEvent::ButtonLeftClick.buttonData中，根据参数值有两种操作
     * 1.存档：”save [index]“，其中index为存档号，unsigned char型，例如”save 1“
     * 1.读档：”load [index]“，其中index为存档号，unsigned char型，例如”load 1“
     */
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
