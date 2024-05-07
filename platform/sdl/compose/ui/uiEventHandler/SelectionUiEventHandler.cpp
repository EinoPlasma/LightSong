//
// Created by EinoPlasma on 2024/5/6.
//

#include "SelectionUiEventHandler.h"

namespace sdl {
    void SelectionUiEventHandler::handleUiEvent(std::unique_ptr<UiEvent> uiEvent, std::shared_ptr<core::Director> director) {
        if (uiEvent->type() == UiEventType::BUTTON_LEFT_CLICK) {
            auto targetUiEvent = dynamic_cast<ButtonLeftClick*>(uiEvent.get());
            // TODO: 1.写director（Environment）的存档、读档、getSaveInfos功能 2.根据getSaveInfos获取到内容生成buttons
            std::stringstream ss;
            ss << targetUiEvent->buttonData;
            std::string prompt, index_literal;
            ss >> prompt;
            ss >> index_literal;
            unsigned int index = std::stoi(index_literal);
            if (prompt == "select") {
                director->setFSEL(index);
            }
            deactivateUi();
        }
    }
} // sdl