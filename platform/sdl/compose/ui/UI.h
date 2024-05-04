//
// Created by EinoPlasma on 2024/5/4.
//

#ifndef LIGHTSONG_UI_H
#define LIGHTSONG_UI_H


#include <string>
#include <utility>
#include <vector>
#include <memory>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "../Composer.h"
#include "../../../../core/Director.h"

namespace sdl {

//    我们需要的是UI的派生类（指存档、设置等页面）都有各自定义的ButtonType
//    enum class ButtonType{
//        SELECTION,
//        ADD,
//        SUB,
//        DEFAULT,
//    };

    struct Button {
        SDL_Rect textureRectNotHover;
        SDL_Rect textureRectHover;
        bool flagDisable = false;
        bool flagHover = false;
        SDL_Texture* texture;
        SDL_Rect targetRenderRect;
        std::string data;

        explicit Button(SDL_Texture* texture) : texture(texture) {};
        Button(SDL_Rect textureRectNotActive, SDL_Rect textureRectActive, SDL_Texture* texture, SDL_Rect targetRenderRect, std::string data) : textureRectNotHover(textureRectNotActive), textureRectHover(textureRectActive), texture(texture), targetRenderRect(targetRenderRect), data(std::move(data)) {};
    };

    class UI : public Composer{
    private:
        SDL_Renderer* renderer;
        std::vector<std::shared_ptr<Button>> buttons;
        std::shared_ptr<core::Director> director = nullptr;
    public:
        virtual void render() = 0;
        virtual void update(unsigned int dt) = 0;
        virtual void handleSdlEvent(const SDL_Event* event) = 0;
        virtual bool isUiAlive() = 0;

        // UI(SDL_Renderer* renderer) : renderer(renderer) {};
    };

} // sdl

#endif //LIGHTSONG_UI_H
