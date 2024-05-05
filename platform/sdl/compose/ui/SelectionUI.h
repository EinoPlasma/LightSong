//
// Created by EinoPlasma on 2024/5/5.
//

#ifndef LIGHTSONG_SELECTIONUI_H
#define LIGHTSONG_SELECTIONUI_H

#include "UI.h"
#include <SDL2/SDL_ttf.h>
#include <utility>

namespace sdl {
    // 选择界面，由命令 #sel #sel_text #sel_img #sel_imgs 调用
    // 在本类中，Button中的data字段定义为FSEL的值，传参时务必不要传入其他值
    class SelectionUI : public UI{
    private:
        SDL_Renderer* renderer;
        std::vector<std::shared_ptr<Button>> buttons;
        std::shared_ptr<core::Director> director = nullptr;
        std::deque<std::unique_ptr<sdl::UiEvent>> uiEventQueue = {};
        void handleUiEvents() override;
        void deactivateUi();
        bool flagUiAlive = true; // 用户做出选择（收到正确的点击事件）后，该值置为false，然后本对象的render()方法将不再渲染SelectionUI到屏幕。
    public:
        void render() override;
        void update(unsigned int dt) override;
        bool isUiAlive() override {return flagUiAlive;}

        void addButton(const std::shared_ptr<Button>& button);

        void handleSdlEvent(const SDL_Event *event) override;

        SelectionUI(SDL_Renderer* renderer, std::shared_ptr<core::Director> director) : renderer(renderer), director(std::move(director)) {};
        ~SelectionUI();
    };

    // for #sel command
    std::unique_ptr<SelectionUI> createSelectionUiFromSel(SDL_Renderer* renderer, const std::shared_ptr<core::Director>& director, TTF_Font *font, const std::vector<std::string>& selections);

    // TODO: for mouse right_click menu
    // std::unique_ptr<SelectionUI> createMenuSelectionUi(SDL_Renderer* renderer, const std::shared_ptr<core::Director>& director, TTF_Font *font);

} // sdl

#endif //LIGHTSONG_SELECTIONUI_H
