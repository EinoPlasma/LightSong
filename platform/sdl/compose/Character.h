//
// Created by EinoPlasma on 2024/5/4.
//

#ifndef LIGHTSONG_CHARACTER_H
#define LIGHTSONG_CHARACTER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <utility>
#include <vector>
#include <unordered_map>
#include "memory"

namespace sdl {

    /*
     * 1. coord_mode：坐标模式，共有 7 种：
coord_mode x 坐标表示的含义 y 坐标表示的含义
0 立绘左沿距屏幕左沿的距离 立绘上沿距屏幕上沿的距离
1 立绘中点距屏幕左沿的距离 立绘上沿距屏幕上沿的距离
2 立绘右沿距屏幕右沿的距离 立绘上沿距屏幕上沿的距离
3 立绘中点距屏幕左沿的距离 立绘中点距屏幕上沿的距离
4 立绘左沿距屏幕左沿的距离 立绘下沿距屏幕下沿的距离
5 立绘中点距屏幕左沿的距离 立绘下沿距屏幕下沿的距离
6 立绘右沿距屏幕右沿的距离 立绘下沿距屏幕下沿的距离
     */

    enum class CoordinateMode {
        LEFT = 0,
        CENTER = 1,
        RIGHT = 2,
        LEFT_CENTER = 3,
        LEFT_TOP = 4,
        LEFT_BOTTOM = 5,
        RIGHT_BOTTOM = 6
    };

    const std::unordered_map<int, CoordinateMode> coordinateModeMap = {
            {0, CoordinateMode::LEFT},
            {1, CoordinateMode::CENTER},
            {2, CoordinateMode::RIGHT},
            {3, CoordinateMode::LEFT_CENTER},
            {4, CoordinateMode::LEFT_TOP},
            {5, CoordinateMode::LEFT_BOTTOM},
            {6, CoordinateMode::RIGHT_BOTTOM}
    };

    // Animation
    enum class AnimationMode {
        FADE_IN = 0,
        FADE_OUT = 1,
        QUAKE = 2,
        DOWN = 3,
        UP = 4,
        IMMEDIATELY_DISPLAY = 5,
        NONE = 6,
    };



    const unsigned int CHARACTER_ANIMATION_DEFAULT_FADE_TIME = 300;
    const unsigned int CHARACTER_ANIMATION_DEFAULT_QUAKE_TIME = 300;
    const unsigned int CHARACTER_ANIMATION_DEFAULT_UP_TIME = 300;
    const unsigned int CHARACTER_ANIMATION_DEFAULT_DOWN_TIME = 300;

    const unsigned int CHARACTER_ANIMATION_DEFAULT_QUAKE_AMPLITUDE = 10;


    class Character {
    private:
        struct CharaAnimation {
            AnimationMode mode;
            unsigned int time;
            unsigned int timeElapsed;
            unsigned char restoreX{}; // 仅在QUAKE模式下生效
            unsigned char restoreY{}; // 仅在UP/DOWN模式下生效
        };

        struct CharaInfo {
            bool isAlive{true};
            int charaID{};
            std::string filename;
            unsigned char x{}; // texture最左边在屏幕上x轴的百分比，0表示屏幕左边，100表示屏幕右边，范围0-100
            unsigned char y{}; // texture最上边在屏幕上y轴的百分比，0表示屏幕上边，100表示屏幕下边，范围0-100
            int layer{};
            CharaAnimation animation{AnimationMode::FADE_IN, CHARACTER_ANIMATION_DEFAULT_FADE_TIME, 0};
            // SDL_Texture* charaTexture{nullptr};
            SDL_Texture* charaTexture;
            unsigned int alpha{255};

            explicit CharaInfo(SDL_Texture* charaTexture) : charaTexture(charaTexture) {}; // SDL_Texture* charaTexture必须用参数列表初始化，否则texture无效！
        };
        std::vector<std::shared_ptr<CharaInfo>> characters{};
        SDL_Renderer* renderer = nullptr; // 注意在render()的时候要获取窗口的大小，在此类中是通过renderer获取的（SDL_GetRendererOutputSize(renderer, &rendererWidth, &rendererHeight);）请确保renderer绑定的是窗口而不是纹理
        std::string charaPath;
        std::string charaImgFormat;

        SDL_Texture* testTexture = IMG_LoadTexture(renderer, ("C:\\LightSong\\reference\\games\\frfr2\\android\\FreeFriends2\\chara\\smi0107.png"));

    public:
        void update(unsigned int dt);
        void render();

        Character(SDL_Renderer* renderer, std::string charaPath, std::string charaImgFormat) : renderer(renderer), charaPath(std::move(charaPath)), charaImgFormat(std::move(charaImgFormat)) {};

        void clearAllCharacters(unsigned int fadeTime=CHARACTER_ANIMATION_DEFAULT_FADE_TIME);

        void setCharacter(int charaID, const std::string& filename, unsigned char position, int layer,unsigned int fadeTime);
        void removeCharacter(int charaID, unsigned int fadeTime=CHARACTER_ANIMATION_DEFAULT_FADE_TIME);
        //void setCharacterPos(int charaID, int new_x, int new_y, int coord_mode);
        void charaQuake(std::vector<int> charaIDs);
        void charaDown(std::vector<int> charaIDs);
        void charaUp(std::vector<int> charaIDs);
        //void setCharaY(int charaID, std::string filename, int x, int y, int coord_mode, unsigned int fadeTime=DEFAULT_CHARACTER_FADE_TIME);
        //void charaScroll(int coord_mode, int charaID, std::string filename, int startx, int starty, int endx, int endy, int beginalpha, int layer, int time);
    };

} // sdl

#endif //LIGHTSONG_CHARACTER_H
