//
// Created by EinoPlasma on 2024/5/5.
//

#include "LabelSetUI.h"

namespace sdl {
    LabelSetUI::~LabelSetUI() {
        for(auto &button : buttons) {
            SDL_DestroyTexture(button->texture);
        }
    }

    void LabelSetUI::handleUiEvents() {
        while (!uiEventQueue.empty()) {
            std::unique_ptr<UiEvent> uiEvent = std::move(uiEventQueue.front());
            uiEventQueue.pop_front();

            if (uiEvent->type() == UiEventType::BUTTON_LEFT_CLICK) {
                auto targetUiEvent = dynamic_cast<ButtonLeftClick*>(uiEvent.get());
                unsigned int fsel = std::stoi(targetUiEvent->buttonData);
                // TODO: 1.写director（Environment）的存档、读档、getSaveInfos功能 2.根据getSaveInfos获取到内容生成buttons
                director->setFSEL(fsel);
                deactivateUi();
            }
        }
    }

    void LabelSetUI::deactivateUi() {
        flagUiAlive = false;
    }

    void LabelSetUI::addButton(const std::shared_ptr<Button> &button) {
        buttons.push_back(button);
    }

    void LabelSetUI::render() {
        if (!flagUiAlive) {
            return;
        }

        for (auto &button : buttons) {
            SDL_RenderCopy(renderer, button->texture, &button->sourceRect, &button->targetRenderRect);
        }
    }

    void LabelSetUI::update(unsigned int dt) {
        handleUiEvents();
    }

    void LabelSetUI::handleSdlEvent(const SDL_Event *event) {
        // if event is mouse hover
        if (event->type == SDL_MOUSEMOTION) {
            // change sourceRect for render hover or notHover texture
            for (auto &button : buttons) {
                if (event->motion.x >= button->targetRenderRect.x && event->motion.x <= button->targetRenderRect.x + button->targetRenderRect.w && event->motion.y >= button->targetRenderRect.y && event->motion.y <= button->targetRenderRect.y + button->targetRenderRect.h) {
                    // mouse in button
                    button->sourceRect = button->textureRectHover;
                } else {
                    button->sourceRect = button->textureRectNotHover;
                }
            }
        } else if (event->type == SDL_MOUSEBUTTONDOWN) {
            for (auto &button : buttons) {
                if (event->button.button == SDL_BUTTON_LEFT) {
                    // left click
                    if (event->motion.x >= button->targetRenderRect.x && event->motion.x <= button->targetRenderRect.x + button->targetRenderRect.w && event->motion.y >= button->targetRenderRect.y && event->motion.y <= button->targetRenderRect.y + button->targetRenderRect.h) {
                        // mouse in button
                        uiEventQueue.emplace_back(std::make_unique<ButtonLeftClick>(button->data));
                    }
                }
            }
        }
    }
} // sdl