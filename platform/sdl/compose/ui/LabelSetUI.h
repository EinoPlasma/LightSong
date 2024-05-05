//
// Created by EinoPlasma on 2024/5/5.
//

#ifndef LIGHTSONG_LABELSETUI_H
#define LIGHTSONG_LABELSETUI_H

#include "UI.h"

namespace sdl {

    class LabelSetUI : public UI {
    private:
        SDL_Renderer* renderer;
        std::vector<std::shared_ptr<Button>> buttons;
        std::shared_ptr<core::Director> director = nullptr;
        std::deque<std::unique_ptr<sdl::UiEvent>> uiEventQueue = {};
        void handleUiEvents() override;
        void deactivateUi();
        bool flagUiAlive = true; // 用户做出选择（收到正确的点击事件）后，该值置为false，然后本对象的render()方法将不再渲染SelectionUI到屏幕。

        void addButton(const std::shared_ptr<Button>& button);
    public:
        void render() override;
        void update(unsigned int dt) override;
        bool isUiAlive() override {return flagUiAlive;}

        void handleSdlEvent(const SDL_Event *event) override;

        LabelSetUI(SDL_Renderer* renderer, std::shared_ptr<core::Director> director) : renderer(renderer), director(std::move(director)) {};
        ~LabelSetUI();
    };

} // sdl

#endif //LIGHTSONG_LABELSETUI_H
