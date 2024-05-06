//
// Created by EinoPlasma on 2024/5/5.
//

#ifndef LIGHTSONG_LABELSETUI_H
#define LIGHTSONG_LABELSETUI_H

#include <SDL_ttf.h>
#include "UI.h"
#include "uiEventHandler/SaveAndLoadUiEventHandler.h"

namespace sdl {

    class LabelSetUI : public UI {
    private:
        SDL_Renderer* renderer;
        std::vector<std::shared_ptr<Button>> buttons;
        std::shared_ptr<core::Director> director = nullptr;
        std::deque<std::unique_ptr<sdl::UiEvent>> uiEventQueue = {};
        std::unique_ptr<SaveAndLoadUiEventHandler> uiEventHandler = std::make_unique<SaveAndLoadUiEventHandler>();
        void handleUiEvents() override;
        void deactivateUi();
        bool flagUiAlive = true; // 用户做出选择（收到正确的点击事件）后，该值置为false，然后本对象的render()方法将不再渲染SelectionUI到屏幕。
    public:
        void render() override;
        void update(unsigned int dt) override;
        bool isUiAlive() override {return flagUiAlive;}

        void addButton(const std::shared_ptr<Button>& button);

        void handleSdlEvent(const SDL_Event *event) override;

        LabelSetUI(SDL_Renderer* renderer, std::shared_ptr<core::Director> director) : renderer(renderer), director(std::move(director)) {};
        ~LabelSetUI();
    };

    std::unique_ptr<LabelSetUI> createTestLoadAndSaveUi(SDL_Renderer* renderer, const std::shared_ptr<core::Director>& director, TTF_Font *font);



} // sdl

#endif //LIGHTSONG_LABELSETUI_H
