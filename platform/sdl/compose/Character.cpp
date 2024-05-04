//
// Created by EinoPlasma on 2024/5/4.
//

#include <algorithm>
#include <iostream>
#include "cmath"
#include "Character.h"

namespace sdl {



    void Character::update(unsigned int dt) {
        SDL_Log("Character::update, dt: %d", dt);
        // fade in, fade out and free
        // free
        characters.erase(std::remove_if(characters.begin(), characters.end(), [](const std::shared_ptr<CharaInfo>& character) {
            if (!character->isAlive && character->animation.timeElapsed >= character->animation.time) {
                return true; // 删除满足条件的元素
            }
            return false;
        }), characters.end());
        // fade in, fade out
        for (auto it = characters.begin(); it != characters.end(); ++it) {
             std::shared_ptr<CharaInfo> character = *it;
            if (character->animation.timeElapsed < character->animation.time) {
                character->animation.timeElapsed += dt;
            }

            if (character->animation.mode == AnimationMode::FADE_IN || character->animation.mode == AnimationMode::FADE_OUT) {
                if (character->isAlive) {
                    if (character->animation.timeElapsed < character->animation.time) {
                        character->alpha = (int)((float)255 * (float)character->animation.timeElapsed / (float)character->animation.time);
                        // print all process of calculate
                        SDL_Log("character->animation.timeElapsed: %d, character->animation.time: %d", character->animation.timeElapsed, character->animation.time);
                        SDL_Log("character alpha: %d", character->alpha);
                    }
                } else {
                    if (character->animation.timeElapsed < character->animation.time) {
                        character->alpha = 255 - 255 * character->animation.timeElapsed / character->animation.time;
                    } else {
                        // no need to do anything
                        //it = characters.erase(it);
                    }
                }
            }
        }
        // up, down, quake animation
        for (auto it = characters.begin(); it != characters.end(); ++it) {
            std::shared_ptr<CharaInfo> character = *it;
            if (character->animation.timeElapsed >= character->animation.time) {
                continue;
            };

            // TODO: 检查动画效果
            if (character->animation.mode == AnimationMode::UP) {
                // std::cerr << "up character animation not implemented" << std::endl;
                // make a quadratic function to character->y
                character->y = character->animation.restoreY - (character->animation.restoreY - character->y) * character->animation.timeElapsed / character->animation.time * character->animation.time;
            } else if (character->animation.mode == AnimationMode::DOWN) {
                //std::cerr << "down character animation not implemented" << std::endl;
                // make a quadratic function to character->y
                character->y = character->animation.restoreY + (character->animation.restoreY - character->y) * character->animation.timeElapsed / character->animation.time * character->animation.time;
            } else if (character->animation.mode == AnimationMode::QUAKE) {
                // make a sig wave to character->x
                character->x = character->animation.restoreX + sin(character->animation.timeElapsed / character->animation.time * 2 * M_PI) * CHARACTER_ANIMATION_DEFAULT_QUAKE_AMPLITUDE;
            } else if (character->animation.mode == AnimationMode::IMMEDIATELY_DISPLAY) {
                character->alpha = 255;
            } else if (character->animation.mode == AnimationMode::NONE) {
                // do nothing
            }
        }


    }

    void Character::setCharacter(int charaID, const std::string &filename, unsigned char position, int layer, unsigned int fadeTime) {
        std::cout << "start set character" << std::endl;

        // 如果filename为 NULL的话，表示擦除对应的立绘 ID。
        if (filename == "NULL") {
            removeCharacter(charaID, fadeTime);
        }

        SDL_Texture* _characterTexture = IMG_LoadTexture(renderer, (charaPath + filename + charaImgFormat).c_str());
        if (SDL_QueryTexture(_characterTexture, NULL, NULL, NULL, NULL) != 0) {
            std::cout << "read character failed: " << SDL_GetError() << std::endl;
            throw std::runtime_error("read character failed");
        }


        std::shared_ptr<CharaInfo> characterInfo = std::make_shared<CharaInfo>(_characterTexture);

        characterInfo->isAlive = true;
        characterInfo->charaID = charaID;
        characterInfo->filename = filename;
        characterInfo->x = position;
        characterInfo->layer = layer;
        characterInfo->animation = CharaAnimation{AnimationMode::FADE_IN,fadeTime,0};


        // testTexture = IMG_LoadTexture(renderer, (charaPath + filename + charaImgFormat).c_str());

//        std::cout << charaPath + filename + charaImgFormat << std::endl;
//
        std::cout << characterInfo->charaTexture << std::endl;
        characterInfo->alpha = 0; // fade in from zero

        // print character info
        std::cout << "Character Info:" << std::endl;
        std::cout << "  charaID: " << characterInfo->charaID << std::endl;
        std::cout << "  filename: " << characterInfo->filename << std::endl;
        std::cout << "  x: " << characterInfo->x << std::endl;
        std::cout << "  layer: " << characterInfo->layer << std::endl;
        std::cout << "  alpha: " << characterInfo->alpha << std::endl;
        std::cout << "  isAlive: " << characterInfo->isAlive << std::endl;
        std::cout << "  animation: " << (int)characterInfo->animation.mode << std::endl;
        std::cout << "  animationTime: " << characterInfo->animation.time << std::endl;
        std::cout << "  animationTimeElapsed: " << characterInfo->animation.timeElapsed << std::endl;
        std::cout << "  animationRestoreX: " << characterInfo->animation.restoreX << std::endl;
        std::cout << "  animationRestoreY: " << characterInfo->animation.restoreY << std::endl;

        // find charaID, if found ,change it. if not found, push it to characters
        bool flagFoundCharaID = false;
        for(auto it = characters.begin(); it != characters.end(); it++) {
            std::shared_ptr<CharaInfo> character = *it;
            if (character->charaID == charaID) {
                characterInfo->alpha = 255; // 把0 alpha改成255
                characterInfo->animation = CharaAnimation{AnimationMode::NONE,0,0}; // 关闭动画
                *it = characterInfo;
                flagFoundCharaID = true;
            }
        } if (!flagFoundCharaID) {
            characters.emplace_back(characterInfo);
        }

        std::cout << "end set character" << std::endl;
    }

    void Character::removeCharacter(int charaID, unsigned int fadeTime) {
        auto it = std::find_if(characters.begin(), characters.end(), [charaID](const std::shared_ptr<CharaInfo>& info) {
            return info->charaID == charaID;
        });
        // 如果找到了角色信息
        if (it != characters.end()) {
            std::shared_ptr<CharaInfo> character = *it;
            character->isAlive = false;
        }
    }

    void Character::clearAllCharacters(unsigned int fadeTime) {
        for (auto it = characters.begin(); it != characters.end(); it++) {
            std::shared_ptr<CharaInfo> character = *it;
            character->animation = CharaAnimation{AnimationMode::FADE_OUT,fadeTime,0};
            character->isAlive = false;
        }
    }

    void Character::charaQuake(std::vector<int> charaIDs) {
        for (int charaID : charaIDs) {
            auto it = std::find_if(characters.begin(), characters.end(), [charaID](const std::shared_ptr<CharaInfo>& info) {
                return info->charaID == charaID;
            });
            // 如果找到了角色信息
            if (it != characters.end()) {
                std::shared_ptr<CharaInfo> character = *it;
                character->animation = CharaAnimation{AnimationMode::QUAKE,CHARACTER_ANIMATION_DEFAULT_QUAKE_TIME,0,character->x,character->y};
            }
        }
    }

    void Character::charaUp(std::vector<int> charaIDs) {
        for (int charaID : charaIDs) {
            auto it = std::find_if(characters.begin(), characters.end(), [charaID](const std::shared_ptr<CharaInfo>& info) {
                return info->charaID == charaID;
            });
            // 如果找到了角色信息
            if (it != characters.end()) {
                std::shared_ptr<CharaInfo> character = *it;
                character->animation = CharaAnimation{AnimationMode::UP,CHARACTER_ANIMATION_DEFAULT_UP_TIME,0,character->x,character->y};
            }
        }
    }

    void Character::charaDown(std::vector<int> charaIDs) {
        for (int charaID : charaIDs) {
            auto it = std::find_if(characters.begin(), characters.end(), [charaID](const std::shared_ptr<CharaInfo>& info) {
                return info->charaID == charaID;
            });
            // 如果找到了角色信息
            if (it != characters.end()) {
                std::shared_ptr<CharaInfo> character = *it;
                character->animation = CharaAnimation{AnimationMode::DOWN,CHARACTER_ANIMATION_DEFAULT_DOWN_TIME,0,character->x,character->y};
            }
        }
    }

    void Character::render() {
        std::cout << "render character 0" << std::endl;
        for (auto it = characters.begin(); it != characters.end(); ++it) {
            std::shared_ptr<CharaInfo> character = *it;

            // character->charaTexture = testTexture; // TODO: 我就这样把testTexture的指针拷贝一份，怎么到后面再用testTexture就怎么也画不出东西了

            int queryResult = SDL_QueryTexture(character->charaTexture, NULL, NULL, NULL, NULL);
            if (queryResult != 0) {
                std::cout << "SDL_QueryTexture failed: " << SDL_GetError() << std::endl;
                throw std::runtime_error("SDL_QueryTexture failed");
            }

            SDL_SetTextureAlphaMod(character->charaTexture, character->alpha);
            std::cout << "character->alpha" << character->alpha << std::endl;

            int rendererWidth, rendererHeight;
            SDL_GetRendererOutputSize(renderer, &rendererWidth, &rendererHeight);
            SDL_Rect targetrRect = {(int)(((float)character->x / 100) * rendererWidth), (int)(((float)character->y / 100) * rendererHeight), 100, 100};
            SDL_QueryTexture(character->charaTexture, NULL, NULL, &targetrRect.w, &targetrRect.h);

            // targetrRect = {0,0,250,400};

            std::cout << character->charaTexture << std::endl;

            SDL_RenderCopy(renderer, character->charaTexture, nullptr, &targetrRect);
            // SDL_RenderCopy(renderer, testTexture, nullptr, &targetrRect);

        }
    }

} // sdl