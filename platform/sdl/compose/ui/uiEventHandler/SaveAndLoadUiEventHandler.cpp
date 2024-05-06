//
// Created by EinoPlasma on 2024/5/6.
//

#include "SaveAndLoadUiEventHandler.h"

namespace sdl {


    void SaveAndLoadUiEventHandler::handleUiEvent(std::unique_ptr<UiEvent> uiEvent, std::shared_ptr<core::Director> director) {
        if (uiEvent->type() == UiEventType::BUTTON_LEFT_CLICK) {
            auto targetUiEvent = dynamic_cast<ButtonLeftClick*>(uiEvent.get());
            // TODO: 1.写director（Environment）的存档、读档、getSaveInfos功能 2.根据getSaveInfos获取到内容生成buttons
            if (targetUiEvent->buttonData == "save 1") {
                director->writeSave(1);
            } else if (targetUiEvent->buttonData == "load 1") {
                director->loadSave(1);
            }
            deactivateUi();
        }
    }
} // sdl