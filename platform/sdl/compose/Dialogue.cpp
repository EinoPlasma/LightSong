//
// Created by EinoPlasma on 2024/5/8.
//

#include "Dialogue.h"
#include <SDL2/SDL_image.h>

#include <utility>
#include "../../../utils.h"
#include "../sdlUtils.h"

namespace sdl {
    void Dialogue::render() {
        if (flagHide) {
            return;
        }
        // set alpha
        SDL_SetTextureAlphaMod(renderableElements[static_cast<unsigned int>(DialogueRenderableElementIndex::MESSAGE_IMG)]->texture, config.imgAlpha);
        SDL_SetTextureAlphaMod(renderableElements[static_cast<unsigned int>(DialogueRenderableElementIndex::NAME_IMG)]->texture, config.imgAlpha);

        SDL_RenderCopy(renderer, renderableElements[(unsigned int)DialogueRenderableElementIndex::MESSAGE_IMG]->texture, &renderableElements[(unsigned int)DialogueRenderableElementIndex::MESSAGE_IMG]->sourceRect, &renderableElements[(unsigned int)DialogueRenderableElementIndex::MESSAGE_IMG]->targetRect);
        SDL_RenderCopy(renderer, renderableElements[(unsigned int)DialogueRenderableElementIndex::NAME_IMG]->texture, &renderableElements[(unsigned int)DialogueRenderableElementIndex::NAME_IMG]->sourceRect, &renderableElements[(unsigned int)DialogueRenderableElementIndex::MESSAGE_IMG]->targetRect);
    }

    void Dialogue::update(unsigned int dt) {

    }

    void Dialogue::changeImgPath(const std::string &messageImgPath, const std::string &nameImgPath) {
        this->messageImgPath = messageImgPath;
        this->nameImgPath = nameImgPath;

        //renderableElements[static_cast<unsigned int>(DialogueRenderableElementIndex::MESSAGE_IMG)] = std::make_shared<RenderableElement>(IMG_LoadTexture(renderer, this->messageImgPath.c_str()));
        //renderableElements[static_cast<unsigned int>(DialogueRenderableElementIndex::NAME_IMG)] =  std::make_shared<RenderableElement>(IMG_LoadTexture(renderer, this->nameImgPath.c_str()));
        renderableElements[static_cast<unsigned int>(DialogueRenderableElementIndex::MESSAGE_IMG)] = std::make_shared<RenderableElement>(autoLoadImg(this->messageImgPath, renderer));
        renderableElements[static_cast<unsigned int>(DialogueRenderableElementIndex::NAME_IMG)] =  std::make_shared<RenderableElement>(autoLoadImg(this->nameImgPath, renderer));

        typesetRenderableElements();
    }

    Dialogue::Dialogue(SDL_Renderer *renderer, std::string messageImgPath, std::string nameImgPath, DialogueConfig config): renderer(renderer), messageImgPath(std::move(messageImgPath)), nameImgPath(std::move(nameImgPath)),
                                                                                                                            config(config) {
        // TODO: 检测这样赋值能不能正常render，不能的话像Character一样用struct包起来
        SDL_Log("TODO: 检测这样赋值能不能正常render，不能的话像Character一样用struct包起来");

//        renderableElements[(unsigned int)DialogueRenderableElementIndex::MESSAGE_IMG] = std::make_shared<RenderableElement>(IMG_LoadTexture(renderer, this->messageImgPath.c_str()));
//        renderableElements[(unsigned int)DialogueRenderableElementIndex::NAME_IMG] = std::make_shared<RenderableElement>(IMG_LoadTexture(renderer, this->nameImgPath.c_str()));
        renderableElements[static_cast<unsigned int>(DialogueRenderableElementIndex::MESSAGE_IMG)] = std::make_shared<RenderableElement>(autoLoadImg(this->messageImgPath, renderer));
        renderableElements[static_cast<unsigned int>(DialogueRenderableElementIndex::NAME_IMG)] =  std::make_shared<RenderableElement>(autoLoadImg(this->nameImgPath, renderer));

        typesetRenderableElements();
    }

    Dialogue::~Dialogue() {
        SDL_DestroyTexture(renderableElements[(unsigned int)DialogueRenderableElementIndex::MESSAGE_IMG]->texture);
        SDL_DestroyTexture(renderableElements[(unsigned int)DialogueRenderableElementIndex::NAME_IMG]->texture);
    }

    void Dialogue::typesetRenderableElements() {

        // do scaling
        SDL_Rect viewport;
        SDL_RenderGetViewport(renderer, &viewport);
        float imgScale = (float)viewport.w / (float)renderableElements[static_cast<unsigned int>(DialogueRenderableElementIndex::MESSAGE_IMG)]->sourceRect.w;
        renderableElements[static_cast<unsigned int>(DialogueRenderableElementIndex::MESSAGE_IMG)]->targetRect.w = viewport.w;
        renderableElements[static_cast<unsigned int>(DialogueRenderableElementIndex::MESSAGE_IMG)]->targetRect.h = imgScale * (float)renderableElements[static_cast<unsigned int>(DialogueRenderableElementIndex::MESSAGE_IMG)]->targetRect.h;

        renderableElements[static_cast<unsigned int>(DialogueRenderableElementIndex::NAME_IMG)]->targetRect.w = imgScale * (float)renderableElements[static_cast<unsigned int>(DialogueRenderableElementIndex::NAME_IMG)]->targetRect.w;
        renderableElements[static_cast<unsigned int>(DialogueRenderableElementIndex::NAME_IMG)]->targetRect.h = imgScale * (float)renderableElements[static_cast<unsigned int>(DialogueRenderableElementIndex::NAME_IMG)]->targetRect.h;
        // change position
        renderableElements[static_cast<unsigned int>(DialogueRenderableElementIndex::MESSAGE_IMG)]->targetRect.y = viewport.h - renderableElements[static_cast<unsigned int>(DialogueRenderableElementIndex::MESSAGE_IMG)]->targetRect.h;
        renderableElements[static_cast<unsigned int>(DialogueRenderableElementIndex::NAME_IMG)]->targetRect.y = renderableElements[static_cast<unsigned int>(DialogueRenderableElementIndex::MESSAGE_IMG)]->targetRect.y - config.nameboxorig_y;

        // typeset
    }
} // sdl