//
// Created by EinoPlasma on 2024/5/8.
//

#ifndef LIGHTSONG_DIALOGUE_H
#define LIGHTSONG_DIALOGUE_H

#include <string>
#include <utility>
#include <memory>
#include <vector>
#include <map>
#include "Composer.h"

namespace sdl {

    enum class DialogueAlignmentType {
        LEFT,
        RIGHT,
        MIDDLE,
    };

    struct DialogueConfig {
        int nameboxorig_x;
        int nameboxorig_y;
        SDL_Color textcolor;
        int msgpos_top;
        int msgpos_bottom;
        int msgpos_left;
        int msgpos_right;
        DialogueAlignmentType nameAlignment;
        unsigned char imgAlpha;
    };

    class Dialogue : public Composer {
    private:
        struct RenderableElement {
            SDL_Texture* texture;
            SDL_Rect sourceRect;
            SDL_Rect targetRect;

            RenderableElement(SDL_Texture* texture, SDL_Rect sourceRect, SDL_Rect targetRect) : texture(texture), sourceRect(sourceRect), targetRect(targetRect) {};
            RenderableElement(SDL_Texture* texture) : texture(texture) {
                sourceRect.x = 0;
                sourceRect.y = 0;
                SDL_QueryTexture(texture, nullptr, nullptr, &sourceRect.w, &sourceRect.h);
                targetRect = sourceRect;
            };
        };
        enum class DialogueRenderableElementIndex {
            MESSAGE_IMG,
            NAME_IMG,
            MESSAGE_TEXT,
            NAME_TEXT,
        };


        bool flagHide = false; // 游戏里面的”隐藏文本框“功能
        SDL_Renderer* renderer = nullptr;
        std::string messageImgPath;
        std::string nameImgPath;
//        std::shared_ptr<ComposerTexture> messageTexture = nullptr; // 因为SDL2的bug，这么写会导致只在第一帧的时候SDL_RenderCopy能在屏幕上渲染出texture，之后texture就会在屏幕上消失，得像下面那样用vector或map包起来才不会消失
//        std::shared_ptr<ComposerTexture> nameTexture = nullptr;
        // std::vector<std::shared_ptr<ComposerTexture>> composerTextures;
        std::map<unsigned int, std::shared_ptr<RenderableElement>> renderableElements;
        void typesetRenderableElements();

        DialogueConfig config;

    public:
        void update(unsigned int dt) override;
        void render() override;
        Dialogue(SDL_Renderer* renderer, std::string  messageImgPath, std::string nameImgPath, DialogueConfig config);
        ~Dialogue();
        void changeImgPath(const std::string& messageImgPath, const std::string& nameImgPath);

        void hide() { flagHide = true; };
        void show() { flagHide = false; };

        void say(std::string message, std::string name, bool containsName);

    };

} // sdl

#endif //LIGHTSONG_DIALOGUE_H
