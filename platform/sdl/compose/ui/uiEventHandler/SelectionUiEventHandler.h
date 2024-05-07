//
// Created by EinoPlasma on 2024/5/6.
//

#ifndef LIGHTSONG_SELECTIONUIEVENTHANDLER_H
#define LIGHTSONG_SELECTIONUIEVENTHANDLER_H

#include "UiEventHandler.h"

namespace sdl {

    /*
     * 接受UiEventType::BUTTON_LEFT_CLICK事件，接受一个std::string参数，参数放在UiEvent::ButtonLeftClick.buttonData中，根据参数值有1种操作
     * 1.选择：”select [index]“，其中index为选项号，unsigned int型，例如”save 1“
     */
    class SelectionUiEventHandler : public UiEventHandler {
    private:
        bool flagShouldDeactivate = false;
        void deactivateUi() {flagShouldDeactivate = true;}
    public:
        bool shouldDeactivate() override {return flagShouldDeactivate;};
        void handleUiEvent(std::unique_ptr<UiEvent> uiEvent, std::shared_ptr<core::Director> director) override;
    };

} // sdl

#endif //LIGHTSONG_SELECTIONUIEVENTHANDLER_H
