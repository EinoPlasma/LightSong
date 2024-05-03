////
//// Created by EinoPlasma on 2024/5/1.
////
//
//#include <iostream>
//#include "SDL2/SDL.h"
//#include "SDL2/SDL_image.h"
//#include "core/GameConfig.h"
//
//#include "core/Director.h"
//#include "platform/sdl/Interface.h"
//
//
//int main(int argc, char **argv) {
//
//    system("chcp 65001");
//
//    std::unique_ptr<core::Director> director = std::make_unique<core::Director>(R"(C:\LightSong\reference\games\Ever17\s60v5\Ever17)");
//
//    // sdl::Interface sdlInterface(std::move(director));
//
////    SDL_Window *window = SDL_CreateWindow(sdlInterface.winTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, sdlInterface.screenWidth, sdlInterface.screenHeight, SDL_WINDOW_SHOWN);
////
////    SDL_Renderer *render = SDL_CreateRenderer(window, -1, 0);
////
////    SDL_Texture *helloTex = SDL_CreateTextureFromSurface(render, IMG_Load(R"(C:\LightSong\reference\games\Ever17\s60v5\Ever17\chara\sa04awl.png)"));
////
////    SDL_RenderClear(render);
////
////    SDL_RenderCopy(render, helloTex, nullptr, nullptr);
////
////    SDL_RenderPresent(render);
////
////    std::cout << "Echo test" << std::endl;
////
////    SDL_Delay(10000);
////
////    SDL_DestroyTexture(helloTex);
////
////    SDL_DestroyRenderer(render);
////
////    SDL_DestroyWindow(window);
////
////    SDL_Quit();
//
//
//    return 0;
//}



//#include <stdio.h>
//#include <stdbool.h>
//#include <SDL2/SDL.h>
//#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_ttf.h>
//#include <SDL2/SDL_mixer.h>
//#include <memory>
//#include "core/Director.h"
//#include "platform/sdl/Interface.h"
//
//// 屏幕宽度和高度
//const int SCREEN_WIDTH = 800;
//const int SCREEN_HEIGHT = 600;
//
//// 图片路径
//const char* BACKGROUND_IMAGE_PATH = "background1.png";
//const char* CHARACTER_IMAGE_PATH = "character1.png";
//const char* FONT_PATH = "font.ttf";
//
//// 文字参数
//const int FONT_SIZE = 24;
//const SDL_Color TEXT_COLOR = {255, 255, 255, 255};
//
//// 音频路径
//const char* BACKGROUND_MUSIC_PATH = "bgm01.mp3";
//const char* SOUND_EFFECT_PATH = "se04.mp3";
//const char* VOICE_PATH = "mik0005.mp3";
//
//// SDL 相关变量
//SDL_Window* gWindow = NULL;
//SDL_Renderer* gRenderer = NULL;
//SDL_Texture* gBackgroundTexture = NULL;
//SDL_Texture* gCharacterTexture = NULL;
//TTF_Font* gFont = NULL;
//Mix_Music* gBackgroundMusic = NULL;
//Mix_Chunk* gSoundEffect = NULL;
//Mix_Chunk* gVoice = NULL;
//
//// 初始化SDL
//bool initSDL() {
//    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
//        printf("SDL初始化失败: %s\n", SDL_GetError());
//        return false;
//    }
//
//    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
//        printf("线性纹理过滤未启用！");
//    }
//
//    gWindow = SDL_CreateWindow("AVG程序", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
//    if (gWindow == NULL) {
//        printf("创建窗口失败: %s\n", SDL_GetError());
//        return false;
//    }
//
//    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
//    if (gRenderer == NULL) {
//        printf("创建渲染器失败: %s\n", SDL_GetError());
//        return false;
//    }
//
//    int imgFlags = IMG_INIT_PNG;
//    if (!(IMG_Init(imgFlags) & imgFlags)) {
//        printf("SDL_image初始化失败: %s\n", IMG_GetError());
//        return false;
//    }
//
//    if (TTF_Init() == -1) {
//        printf("SDL_ttf初始化失败: %s\n", TTF_GetError());
//        return false;
//    }
//
//    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
//        printf("SDL_mixer初始化失败: %s\n", Mix_GetError());
//        return false;
//    }
//
//    return true;
//}
//
//SDL_Texture* loadTexture(const char* path);
//
//// 加载媒体文件
//bool loadMedia() {
//    gBackgroundTexture = loadTexture(BACKGROUND_IMAGE_PATH);
//    if (gBackgroundTexture == NULL) {
//        printf("加载背景图像失败！\n");
//        return false;
//    }
//
//    gCharacterTexture = loadTexture(CHARACTER_IMAGE_PATH);
//    if (gCharacterTexture == NULL) {
//        printf("加载立绘图像失败！\n");
//        return false;
//    }
//
//    gFont = TTF_OpenFont(FONT_PATH, FONT_SIZE);
//    if (gFont == NULL) {
//        printf("加载字体失败！\n");
//        return false;
//    }
//
//    gBackgroundMusic = Mix_LoadMUS(BACKGROUND_MUSIC_PATH);
//    if (gBackgroundMusic == NULL) {
//        printf("加载背景音乐失败！\n");
//        return false;
//    }
//
//    gSoundEffect = Mix_LoadWAV(SOUND_EFFECT_PATH);
//    if (gSoundEffect == NULL) {
//        printf("加载音效失败！\n");
//        return false;
//    }
//
//    gVoice = Mix_LoadWAV(VOICE_PATH);
//    if (gVoice == NULL) {
//        printf("加载语音失败！\n");
//        return false;
//    }
//
//    return true;
//}
//
//// 释放资源并关闭SDL
//    void closeSDL() {
//        SDL_DestroyTexture(gBackgroundTexture);
//        SDL_DestroyTexture(gCharacterTexture);
//        TTF_CloseFont(gFont);
//        Mix_FreeMusic(gBackgroundMusic);
//        Mix_FreeChunk(gSoundEffect);
//        Mix_FreeChunk(gVoice);
//
//        gBackgroundTexture = NULL;
//        gCharacterTexture = NULL;
//        gFont = NULL;
//        gBackgroundMusic = NULL;
//        gSoundEffect = NULL;
//        gVoice = NULL;
//
//        SDL_DestroyRenderer(gRenderer);
//        SDL_DestroyWindow(gWindow);
//        gRenderer = NULL;
//        gWindow = NULL;
//
//        Mix_Quit();
//        TTF_Quit();
//        IMG_Quit();
//        SDL_Quit();
//    }
//
//// 加载纹理
//    SDL_Texture* loadTexture(const char* path) {
//        SDL_Texture* newTexture = NULL;
//        SDL_Surface* loadedSurface = IMG_Load(path);
//        if (loadedSurface == NULL) {
//            printf("无法加载图像 %s！SDL_image 错误: %s\n", path, IMG_GetError());
//        } else {
//            newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
//            if (newTexture == NULL) {
//                printf("无法创建纹理 %s！SDL 错误: %s\n", path, SDL_GetError());
//            }
//
//            SDL_FreeSurface(loadedSurface);
//        }
//
//        return newTexture;
//    }
//
//// 渲染纹理到屏幕
//    void renderTexture(SDL_Texture* texture, int x, int y) {
//        SDL_Rect renderQuad = { x, y, 0, 0 };
//        SDL_QueryTexture(texture, NULL, NULL, &renderQuad.w, &renderQuad.h);
//        SDL_RenderCopy(gRenderer, texture, NULL, &renderQuad);
//    }
//
//// 渲染文字到屏幕
//    void renderText(const char* text, int x, int y) {
//        SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, text, TEXT_COLOR);
//        if (textSurface == NULL) {
//            printf("无法渲染文字！SDL_ttf 错误: %s\n", TTF_GetError());
//        } else {
//            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
//            if (textTexture == NULL) {
//                printf("无法创建文字纹理！SDL 错误: %s\n", SDL_GetError());
//            } else {
//                renderTexture(textTexture, x, y);
//                SDL_DestroyTexture(textTexture);
//            }
//
//            SDL_FreeSurface(textSurface);
//        }
//    }
//
//// 主循环
//    void runAVG() {
//        bool quit = false;
//        SDL_Event e;
//
//        // 当前的背景、立绘和文字索引
//        int currentBackground = 0;
//        int currentCharacter = 0;
//        int currentText = 0;
//
//        // 背景、立绘和文字的路径
//        const char* backgroundPaths[] = { "background1.png", "background2.png", "background3.png" };
//        const char* characterPaths[] = { "character1.png", "character2.png", "character3.png" };
//        const char* texts[] = { "This is the first line.", "这是第二条文字。", "This is the third line." };
//
//        // 播放背景音乐
//        Mix_PlayMusic(gBackgroundMusic, -1);
//
//        while (!quit) {
//            while (SDL_PollEvent(&e) != 0) {
//                if (e.type == SDL_QUIT) {
//                    quit = true;
//                } else if (e.type == SDL_KEYDOWN) {
//                    // 按下键盘时切换背景、立绘和文字
//                    if (e.key.keysym.sym == SDLK_SPACE) {
//                        currentBackground = (currentBackground + 1) % (sizeof(backgroundPaths) / sizeof(backgroundPaths[0]));
//                        currentCharacter = (currentCharacter + 1) % (sizeof(characterPaths) / sizeof(characterPaths[0]));
//                        currentText = (currentText + 1) % (sizeof(texts) / sizeof(texts[0]));
//                        SDL_Log("key down: SDLK_SPACE");
//                        // 播放音效和语音
////                        Mix_PlayChannel(-1, gSoundEffect, 0);
////                        Mix_PlayChannel(-1, gVoice, 0);
//                    }
//                }
//            }
//
//            // 清空屏幕
//            SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
//            SDL_RenderClear(gRenderer);
//
//            // 渲染背景、立绘和文字
//            renderTexture(gCharacterTexture, 0, 0);
//            renderText(texts[currentText], 10, 10);
//            // renderText(texts[currentText], 10, SCREEN_HEIGHT - 50);
//
//            // 更新屏幕
//            SDL_RenderPresent(gRenderer);
//
//            SDL_Delay(5);
//        }
//    }
//
//    int main(int argc, char **argv) {
//        system("chcp 65001"); // 设置编码为UTF-8
//
//        sdl::Interface sdlInterface(R"(C:\LightSong\reference\games\Ever17\s60v5\Ever17)");
//
//
//
//        if (!initSDL()) {
//            printf("SDL初始化失败！\n");
//            return 1;
//        }
//
//        if (!loadMedia()) {
//            printf("加载媒体文件失败！\n");
//            return 1;
//        }
//
//        runAVG();
//
//        closeSDL();
//
//        return 0;
//    }

#include "core/Director.h"
#include "core/EnginePath.h"

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

// AVG游戏类
class Interface {
public:
    Interface(SDL_Window* window_, std::string root_path);
    ~Interface();
    void run();

private:
    bool initialize();
    void loadMedia();
    void close();
    void handleEvents();
    void update();
    void render();

    std::string root_path_;
    std::unique_ptr<core::Director> director_ = nullptr;

    SDL_Window* window_;
    SDL_Renderer* renderer_ = nullptr;
    SDL_Texture* backgroundTexture_ = nullptr;

    std::string font_path;
    unsigned int font_size;
    TTF_Font* font_ = nullptr;
    std::string currentText_;
    SDL_Texture* textTexture_ = nullptr;

    Mix_Music* backgroundMusic_ = nullptr;

    SDL_Rect backgroundRect_;
    SDL_Rect textRect_;
};

Interface::Interface(SDL_Window* window_, std::string root_path) : window_(window_), root_path_(root_path) {
    initialize();
}

Interface::~Interface()
{
    close();
}

bool Interface::initialize()
{

    this->director_ = std::make_unique<core::Director>(root_path_);

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
    }

    if (window_ == nullptr) {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    SDL_SetWindowTitle(window_, director_->getConfig().gametitle.c_str());
    SDL_SetWindowSize(window_, director_->getConfig().imagesize_width, director_->getConfig().imagesize_height);

    // 强制销毁与窗口关联的渲染器（renderer）并设置新的渲染器
    SDL_Renderer* foo_renderer_to_destroy = SDL_GetRenderer(window_);
    if (foo_renderer_to_destroy != nullptr) {
        SDL_DestroyRenderer(foo_renderer_to_destroy);
    }
    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
    if (renderer_ == nullptr) {
        std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF | IMG_INIT_WEBP | IMG_INIT_AVIF | IMG_INIT_JXL;
    // TODO: 发布时修改此项支持更多格式
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        return 1;
    }

    if (TTF_Init() == -1) {
        std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return false;
    }

    if (Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }

    return true;
}

void Interface::loadMedia()
{
    // 加载背景纹理
    SDL_Surface* backgroundSurface = IMG_Load((root_path_ + core::PATH_DIR_BG + core::PATH_FILE_BG_LOGO1 + director_->getConfig().bgformat).c_str());
    backgroundTexture_ = SDL_CreateTextureFromSurface(renderer_, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);

//    // 加载立绘纹理
//    SDL_Surface* characterSurface = IMG_Load((RESOURCE_PATH + CHARACTER_FILE).c_str());
//    characterTexture_ = SDL_CreateTextureFromSurface(renderer_, characterSurface);
//    SDL_FreeSurface(characterSurface);

    // 加载字体
    font_ = TTF_OpenFont("font.ttf", 28);
    if (font_ == nullptr) {
        std::cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
    }

    // 创建文字纹理
    SDL_Color textColor = { 255, 255, 255 };
    SDL_Surface* textSurface = TTF_RenderText_Solid(font_, "TEXT_CONTENT 测试文字", textColor);
    textTexture_ = SDL_CreateTextureFromSurface(renderer_, textSurface);
    SDL_FreeSurface(textSurface);

//    // 加载背景音乐
//    backgroundMusic_ = Mix_LoadMUS((RESOURCE_PATH + BACKGROUND_MUSIC_FILE).c_str());
//    if (backgroundMusic_ == nullptr) {
//        std::cout << "Failed to load background music! SDL_mixer Error: " << Mix_GetError() << std::endl;
//    }
//    // 加载音效
//    soundEffect_ = Mix_LoadWAV((RESOURCE_PATH + SOUND_EFFECT_FILE).c_str());
//    if (soundEffect_ == nullptr) {
//        std::cout << "Failed to load sound effect! SDL_mixer Error: " << Mix_GetError() << std::endl;
//    }
}

void Interface::close()
{
    SDL_DestroyTexture(backgroundTexture_);
    SDL_DestroyTexture(textTexture_);
    Mix_FreeMusic(backgroundMusic_);
    TTF_CloseFont(font_);

    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Interface::handleEvents()
{
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            close();
            exit(0);
        }
        else if (e.type == SDL_KEYDOWN) {
            if (e.key.keysym.sym == SDLK_SPACE) {
                // 执行下一条指令
                update();
            }
        }
    }
}

void Interface::update()
{
    // 切换背景、立绘、文字等逻辑处理
    // ...

//    SDL_Surface* backgroundSurface = IMG_Load((RESOURCE_PATH + "background2.png").c_str());
//    backgroundTexture_ = SDL_CreateTextureFromSurface(renderer_, backgroundSurface);
//    SDL_FreeSurface(backgroundSurface);
//
//    backgroundRect_.x += 10;
//
//    SDL_SetTextureAlphaMod(characterTexture_, 100);
//
//    // 播放音效
//    if (soundEffect_ != nullptr) {
//        Mix_PlayChannel(-1, soundEffect_, 0);
//    }

    std::unique_ptr<sdl::SdlCommand> cmd = director_->nextSdlCommand();
    sdl::SdlCommandType type = cmd->type();
    if (type == sdl::SDL_SAY) {
    } else if (type == sdl::SDL_TEXT) {
    } else if (type == sdl::SDL_TEXT_OFF) {
        // TEXT_OFF case
    } else if (type == sdl::SDL_WAITKEY) {
        // WAITKEY case
    } else if (type == sdl::SDL_TITLE) {
    } else if (type == sdl::SDL_TITLE_DSP) {
        // TITLE_DSP case
    } else if (type == sdl::SDL_CHARA) {
        // CHARA case
    } else if (type == sdl::SDL_CHARA_CLS) {
        // CHARA_CLS case
    } else if (type == sdl::SDL_CHARA_POS) {
        // CHARA_POS case
    } else if (type == sdl::SDL_BG) {
        // BG case
        auto targetCmd = dynamic_cast<sdl::SdlCommandBg*>(cmd.get());
        SDL_Log("bg cmd: %s", targetCmd->filename.c_str());
        backgroundTexture_ = IMG_LoadTexture(renderer_, (root_path_ + core::PATH_DIR_BG + targetCmd->filename + director_->getConfig().bgformat).c_str());
    } else if (type == sdl::SDL_FLASH) {
        // FLASH case
    } else if (type == sdl::SDL_QUAKE) {
        // QUAKE case
    } else if (type == sdl::SDL_FADE_OUT) {
        // FADE_OUT case
    } else if (type == sdl::SDL_FADE_IN) {
        // FADE_IN case
    } else if (type == sdl::SDL_MOVIE) {
        // MOVIE case
    } else if (type == sdl::SDL_TEXTBOX) {
        // TEXTBOX case
    } else if (type == sdl::SDL_CHARA_QUAKE) {
        // CHARA_QUAKE case
    } else if (type == sdl::SDL_CHARA_DOWN) {
        // CHARA_DOWN case
    } else if (type == sdl::SDL_CHARA_UP) {
        // CHARA_UP case
    } else if (type == sdl::SDL_SCROLL) {
        // SCROLL case
    } else if (type == sdl::SDL_CHARA_Y) {
        // CHARA_Y case
    } else if (type == sdl::SDL_CHARA_SCROLL) {
        // CHARA_SCROLL case
    } else if (type == sdl::SDL_ANIME_ON) {
        // ANIME_ON case
    } else if (type == sdl::SDL_ANIME_OFF) {
        // ANIME_OFF case
    } else if (type == sdl::SDL_CHARA_ANIME) {
        // CHARA_ANIME case
    } else if (type == sdl::SDL_SEL) {
        auto targetCmd = dynamic_cast<sdl::SdlCommandSel*>(cmd.get());
    } else if (type == sdl::SDL_SELECT_TEXT) {
        // SELECT_TEXT case
    } else if (type == sdl::SDL_SELECT_VAR) {
        // SELECT_VAR case
    } else if (type == sdl::SDL_SELECT_IMG) {
        // SELECT_IMG case
    } else if (type == sdl::SDL_SELECT_IMGS) {
        // SELECT_IMGS case
    } else if (type == sdl::SDL_WAIT) {
        // WAIT case
    } else if (type == sdl::SDL_WAIT_SE) {
        // WAIT_SE case
    } else if (type == sdl::SDL_BGM) {
        // BGM case
    } else if (type == sdl::SDL_BGM_STOP) {
        // BGM_STOP case
    } else if (type == sdl::SDL_SE) {
        // SE case
    } else if (type == sdl::SDL_SE_STOP) {
        // SE_STOP case
    } else if (type == sdl::SDL_VO) {
        // VO case
    } else if (type == sdl::SDL_LOAD) {
        // LOAD case
    } else if (type == sdl::SDL_ALBUM) {
        // ALBUM case
    } else if (type == sdl::SDL_MUSIC) {
        // MUSIC case
    } else if (type == sdl::SDL_DATE) {
        // DATE case
    } else if (type == sdl::SDL_CONFIG) {
        // CONFIG case
    } else {
        // Default case
        throw std::runtime_error("Unknown command type: " + std::to_string(type));
        // std::cerr << "Unknown command type: " << type << std::endl;
    }



}

void Interface::render()
{
    // 清空渲染器
    SDL_RenderClear(renderer_);

    // 渲染背景
    SDL_RenderCopy(renderer_, backgroundTexture_, nullptr, &backgroundRect_);


//    // 渲染立绘
//    SDL_Rect characterRect_;
//    characterRect_.x = 100;
//    characterRect_.y = 100;
//    characterRect_.w = 100;
//    characterRect_.h = 300;
//
//    SDL_RenderCopy(renderer_, characterTexture_, nullptr, &characterRect_);


    // 渲染文字层
    SDL_RenderCopy(renderer_, textTexture_, nullptr, &textRect_);

    // 更新屏幕显示
    SDL_RenderPresent(renderer_);
}


void Interface::run()
{
    if (!initialize()) {
        std::cout << "Failed to initialize!" << std::endl;
        return;
    }

    loadMedia();

    backgroundRect_.x = 0;
    backgroundRect_.y = 0;
    backgroundRect_.w = director_->getConfig().imagesize_width;
    backgroundRect_.h = director_->getConfig().imagesize_height;



    textRect_.x = 20;
    textRect_.y = 20;
    textRect_.w = 400;
    textRect_.h = 100;

    currentText_ = "TEXT_CONTENT currentText_测试文字";


    if (backgroundMusic_ != nullptr) {
        Mix_PlayMusic(backgroundMusic_, -1);
    }

    bool quit = false;
    while (!quit) {
        handleEvents();
        render();
    }
}



int main(int argc, char* argv[])
{
    system("chcp 65001");

    SDL_Window* window_ = SDL_CreateWindow("Hello, World!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 320, 240, SDL_WINDOW_SHOWN);

    Interface game(window_, R"(C:\LightSong\reference\games\Ever17\s60v5\Ever17)");
    game.run();

    return 0;
}


//
////
//// Created by EinoPlasma on 2024/5/1.
////
//
//#include <iostream>
//#include "SDL2/SDL.h"
//#include "SDL2/SDL_image.h"
//#include "core/GameConfig.h"
//
//#include "core/Director.h"
//#include "platform/sdl/Interface.h"
//
//
//int main(int argc, char **argv) {
//
//    system("chcp 65001");
//
//    std::unique_ptr<core::Director> director = std::make_unique<core::Director>(R"(C:\LightSong\reference\games\Ever17\s60v5\Ever17)");
//
//
//
//    std::string winTitle = director->getConfig().gametitle;
//    int screenWidth = director->getConfig().imagesize_width;
//    int screenHeight = director->getConfig().imagesize_height;
//
//    // init a window, then display R"(C:\LightSong\reference\games\Ever17\s60v5\Ever17\chara\sa04awl.bmp)"
//
//    SDL_Window *window = SDL_CreateWindow(winTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
//
//    SDL_Renderer *render = SDL_CreateRenderer(window, -1, 0);
//
//    SDL_Texture *helloTex = SDL_CreateTextureFromSurface(render, IMG_Load(R"(C:\LightSong\reference\games\Ever17\s60v5\Ever17\chara\sa04awl.png)"));
//
//    SDL_RenderClear(render);
//
//    SDL_RenderCopy(render, helloTex, nullptr, nullptr);
//
//    SDL_RenderPresent(render);
//
//    std::cout << "Echo test" << std::endl;
//
//    SDL_Delay(10000);
//
//    SDL_DestroyTexture(helloTex);
//
//    SDL_DestroyRenderer(render);
//
//    SDL_DestroyWindow(window);
//
//    SDL_Quit();
//
//
//    return 0;
//}