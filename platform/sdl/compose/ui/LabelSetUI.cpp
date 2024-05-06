//
// Created by EinoPlasma on 2024/5/5.
//

#include "LabelSetUI.h"
#include "../../sdlUtils.h"

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
                // TODO: 1.写director（Environment）的存档、读档、getSaveInfos功能 2.根据getSaveInfos获取到内容生成buttons
                if (targetUiEvent->buttonData == "save 1") {
                    director->writeSave(1);
                } else if (targetUiEvent->buttonData == "load 1") {
                    director->loadSave(1);
                }
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

    std::unique_ptr<LabelSetUI>
    createTestLoadAndSaveUi(SDL_Renderer *renderer, const std::shared_ptr<core::Director> &director, TTF_Font *font) {
        auto testLoadAndSaveUi = std::make_unique<LabelSetUI>(renderer, director);
        std::vector<std::string> selections = {"save 1", "load 1"};
        for(size_t i = 0; i < selections.size(); i++) {
            std::string selection = selections[i];

            // make button texture
            SDL_Surface* tmpSurface = TTF_RenderUTF8_Shaded_Wrapped(font, selection.c_str(), { 30, 30, 30 , 200},  { 255, 255, 255 , 200}, 500);
            SDL_Texture* textTextureNotHover = SDL_CreateTextureFromSurface(renderer, tmpSurface);
            SDL_FreeSurface(tmpSurface);

            tmpSurface = TTF_RenderUTF8_Shaded_Wrapped(font, selection.c_str(), { 160, 160, 160 , 200},  { 255, 255, 255 , 200}, 500);
            SDL_Texture* textTextureHover = SDL_CreateTextureFromSurface(renderer, tmpSurface);
            SDL_FreeSurface(tmpSurface);

            SDL_Texture* buttonTexture = concatenateTextures(renderer,textTextureNotHover, textTextureHover);

            int textTextureNotHover_w, textTextureNotHover_h;
            SDL_QueryTexture(textTextureNotHover, nullptr, nullptr, &textTextureNotHover_w, &textTextureNotHover_h);
            int textTextureHover_w, textTextureHover_h;
            SDL_QueryTexture(textTextureHover, nullptr, nullptr, &textTextureHover_w, &textTextureHover_h);

            SDL_Rect textureRectNotHover = {0, 0, textTextureNotHover_w, textTextureNotHover_h};
            SDL_Rect textureRectHover = {textTextureHover_w, 0, textTextureHover_w, textTextureHover_h};


            //SDL_Rect targetRenderRect = {100, 100 + (int)(i * (textTextureNotHover_h + 10)), textTextureNotHover_w, textTextureNotHover_h};
            SDL_Rect targetRenderRect = sdl::makeRenderRect(50, 20 + (int)(i * 10),director->getConfig().imagesize_width, director->getConfig().imagesize_height, textTextureNotHover_w, textTextureNotHover_h);
            std::shared_ptr<Button> button = std::make_shared<Button>(textureRectNotHover, textureRectHover, buttonTexture, targetRenderRect, selection);

            testLoadAndSaveUi->addButton(button);
        }

        return testLoadAndSaveUi;
    }
} // sdl