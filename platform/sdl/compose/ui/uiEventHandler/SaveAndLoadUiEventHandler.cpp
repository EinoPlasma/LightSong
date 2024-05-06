//
// Created by EinoPlasma on 2024/5/6.
//

#include "SaveAndLoadUiEventHandler.h"

namespace sdl {


    void SaveAndLoadUiEventHandler::handleUiEvent(std::unique_ptr<UiEvent> uiEvent, std::shared_ptr<core::Director> director) {
        if (uiEvent->type() == UiEventType::BUTTON_LEFT_CLICK) {
            auto targetUiEvent = dynamic_cast<ButtonLeftClick*>(uiEvent.get());
            // TODO: 1.写director（Environment）的存档、读档、getSaveInfos功能 2.根据getSaveInfos获取到内容生成buttons
            std::stringstream ss;
            ss << targetUiEvent->buttonData;
            std::string prompt, index_literal;
            ss >> prompt;
            ss >> index_literal;
            unsigned char index = std::stoi(index_literal);
            if (prompt == "save") {
                director->writeSave(index);
            } else if (prompt == "load") {
                director->loadSave(index);
            }
            deactivateUi();
        }
    }
} // sdl