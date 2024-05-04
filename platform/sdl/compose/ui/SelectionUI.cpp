//
// Created by EinoPlasma on 2024/5/5.
//

#include "SelectionUI.h"
#include "../../sdlUtils.h"

namespace sdl {
    void SelectionUI::handleSdlEvent(const SDL_Event *event) {
        // if event is mouse hover
        if (event->type == SDL_MOUSEMOTION) {
            for (auto &button : buttons) {
                if (event->motion.x >= button->targetRenderRect.x && event->motion.x <= button->targetRenderRect.x + button->targetRenderRect.w && event->motion.y >= button->targetRenderRect.y && event->motion.y <= button->targetRenderRect.y + button->targetRenderRect.h) {
                    // mouse in button
                    button->flagHover = true;
                } else {
                    button->flagHover = false;
                }
            }
        } else if (event->type == SDL_MOUSEBUTTONDOWN) {
            for (auto &button : buttons) {
                if (event->button.button == SDL_BUTTON_LEFT) {
                    // left click
                    if (event->motion.x >= button->targetRenderRect.x && event->motion.x <= button->targetRenderRect.x + button->targetRenderRect.w && event->motion.y >= button->targetRenderRect.y && event->motion.y <= button->targetRenderRect.y + button->targetRenderRect.h) {
                        // mouse in button
                        unsigned int fsel = std::stoi(button->data);
                        director->setFSEL(fsel);
                        flagUiAlive = false;
                    }
                }
            }
        }
    }


    void SelectionUI::addButton(const std::shared_ptr<Button> &button) {
        buttons.push_back(button);
    }

    void SelectionUI::render() {
        if (!flagUiAlive) {
            return;
        }

        for (auto &button : buttons) {
            SDL_Rect sourceRect;
            if (button->flagHover) {
                sourceRect = button->textureRectHover;
            } else {
                sourceRect = button->textureRectNotHover;
            }
            SDL_RenderCopy(renderer, button->texture, &sourceRect, &button->targetRenderRect);
        }
    }

    SelectionUI::~SelectionUI() {
        for(auto &button : buttons) {
            SDL_DestroyTexture(button->texture);
        }
    }



    std::unique_ptr<SelectionUI> createSelectionUiFromSel(SDL_Renderer* renderer, const std::shared_ptr<core::Director>& director, TTF_Font *font, const std::vector<std::string>& selections) {

        auto selectionUi = std::make_unique<SelectionUI>(renderer, director);
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
            SDL_Rect textureRectHover = {textTextureHover_w + 1, 0, textTextureHover_w, textTextureHover_h};


            SDL_Rect targetRenderRect = {100, 100 + (int)(i * (textTextureNotHover_h + 10)), textTextureNotHover_w, textTextureNotHover_h};

            std::shared_ptr<Button> button = std::make_shared<Button>(textureRectNotHover, textureRectHover, buttonTexture, targetRenderRect, std::to_string(i));

            selectionUi->addButton(button);
        }

        return selectionUi;
    }
} // sdl