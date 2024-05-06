//
// Created by EinoPlasma on 2024/5/1.
//

#include "core/Director.h"
#include "core/EnginePath.h"

#include "platform/sdl/compose/Character.h"
#include "platform/sdl/compose/ui/UI.h"
#include "platform/sdl/compose/ui/SelectionUI.h"
#include "platform/sdl/compose/ui/BlankUI.h"
#include "platform/sdl/compose/ui/LabelSetUI.h"

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <unordered_set>
#include <chrono>

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
    void update(unsigned int dt);
    void render();

    void readAndExecuteCommands();

    std::string root_path_;
    std::shared_ptr<core::Director> director_ = nullptr;

    std::unique_ptr<sdl::Character> character_ = nullptr;
    std::unique_ptr<sdl::UI> ui_ = nullptr;

    SDL_Window* window_;
    SDL_Renderer* renderer_ = nullptr;
    SDL_Texture* backgroundTexture_ = nullptr;

    TTF_Font* font_ = nullptr;
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

    director_ = std::make_shared<core::Director>(root_path_);


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

    character_ = std::make_unique<sdl::Character>(renderer_, root_path_ + core::PATH_DIR_CHARA, director_->getConfig().charaformat);

    ui_ = std::make_unique<sdl::BlankUI>();

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

    // 注册一个全局回调函数，当音效播放完毕时自动释放。仅适用于通过Mix_PlayChannel函数播放的音效
    Mix_ChannelFinished([](int channel) {
        Mix_FreeChunk(Mix_GetChunk(channel));
    });

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
    SDL_Surface* textSurface = TTF_RenderUTF8_Solid(font_, "TEXT_CONTENT 测试文字", textColor);
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
                if (ui_ != nullptr && !ui_->isUiAlive()){
                    // 执行下一条指令，仅在ui_不开启时进行。有ui的话就显示ui，不在读新指令
                    readAndExecuteCommands();
                }
            }
            // quit if window is closed
            else if (e.key.keysym.sym == SDLK_q) {
                close();
                exit(0);
            }
        }
        else if (e.type == SDL_MOUSEBUTTONUP) {
            if (e.button.button == SDL_BUTTON_RIGHT) {
                ui_ = sdl::createTestLoadAndSaveUi(renderer_, director_, font_);
            }
        }



        if (ui_ != nullptr){
            ui_->handleSdlEvent(&e);
        } else {
            SDL_Log("Interface::handleEvents, ui_->handleSdlEvent(&e) failed. ui_ is null");
        }
    }
}

void Interface::update(unsigned int dt) {
    if (character_ != nullptr) {
        character_->update(dt);
    } else {
        SDL_Log("Interface::update, character_->update(dt) failed. Character is null");
    }
    if (ui_ != nullptr){
        ui_->update(dt);
    } else {
        SDL_Log("Interface::update, ui_->update(dt) failed. ui_ is null");
    }
}

void Interface::readAndExecuteCommands()
{
    // 切换背景、立绘、文字等逻辑处理


    // #waitkey指令没有加进去，它要求如果 5 秒后还没有按键，则继续执行下一条指令。
    // #sel #select_text #select_var #select_img #select_imgs 还有 五、 系统类指令 都未加入
    const std::unordered_set<sdl::SdlCommandType> waitKeyCommands = {sdl::SDL_SAY, sdl::SDL_TEXT, sdl::SDL_TITLE_DSP, sdl::SDL_SEL};

    bool flagWaitKey = false;
    // 没有遇到在waitKeyCommands中的指令就一直问Director问指令，直到问到了要停下来的指令（waitKeyCommands中的指令）为止
    while (!flagWaitKey) {
        std::unique_ptr<sdl::SdlCommand> cmd = director_->nextSdlCommand();
        sdl::SdlCommandType type = cmd->type();

        if (waitKeyCommands.find(type) != waitKeyCommands.end()) {
            flagWaitKey = true;
        }

        if (type == sdl::SDL_SAY) {
            auto targetCmd = dynamic_cast<sdl::SdlCommandSay*>(cmd.get());
            SDL_Log("say cmd: %s", targetCmd->content.c_str());
            // free previous text texture
            if (textTexture_ != nullptr) {
                SDL_DestroyTexture(textTexture_);
                textTexture_ = nullptr;
            }

            if (targetCmd->flag_contains_name) {
                // CONTAINS_NAME case
            }

            SDL_Color textColor = { 255, 255, 255 , 200};
            // SDL_Surface* textSurface = TTF_RenderUTF8_Blended(font_, targetCmd->content.c_str(), textColor);
            SDL_Surface* textSurface = TTF_RenderUTF8_Shaded_Wrapped(font_, ("[" + targetCmd->name + "] " + targetCmd->content).c_str(), textColor,  { 50, 50, 50 , 200}, 500);
            textTexture_ = SDL_CreateTextureFromSurface(renderer_, textSurface);
            SDL_FreeSurface(textSurface);
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
            auto targetCmd = dynamic_cast<sdl::SdlCommandChara*>(cmd.get());
            SDL_Log("chara cmd: %zu charaInfos", targetCmd->charaInfos.size());
            auto charaInfos = targetCmd->charaInfos;
            for (auto& charaInfo : charaInfos) {
                 SDL_Log("charaInfo: %s", charaInfo.filename.c_str());
                character_->setCharacter(charaInfo.charaID, charaInfo.filename, charaInfo.position, charaInfo.layer, targetCmd->time);
                SDL_Log("set chara: %s success", charaInfo.filename.c_str());
            }
        } else if (type == sdl::SDL_CHARA_CLS) {
            // CHARA_CLS case
            auto targetCmd = dynamic_cast<sdl::SdlCommandCharaCls*>(cmd.get());
            SDL_Log("chara cls cmd: ");
            SDL_Log("Warning: chara cls Not implemented yet");
            character_->clearAllCharacters(targetCmd->time);
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
            SDL_Log("sel cmd: %d", targetCmd->choiceNum);
            for(int i = 0; i < targetCmd->choiceNum; i++) {
                SDL_Log("choice %d: %s", i, targetCmd->choiceTexts[i].c_str());
            }
            // std::unique_ptr<SelectionUI> createSelectionUiFromSel(SDL_Renderer* renderer, const std::shared_ptr<core::Director>& director, TTF_Font *font, const std::vector<std::string>& selections)
            // SDL_Log("create selection ui from sel");
            ui_ = sdl::createSelectionUiFromSel(renderer_, director_, font_, targetCmd->choiceTexts);

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
            auto targetCmd = dynamic_cast<sdl::SdlCommandBgm*>(cmd.get());
            std::string filename = root_path_ + core::PATH_DIR_BGM + targetCmd->filename + director_->getConfig().bgmformat;
            // 每次更换BGM前记得把之前的BGM给free掉
            if (backgroundMusic_ != nullptr) {
                Mix_FreeMusic(backgroundMusic_);
                backgroundMusic_ = nullptr;
            }
            backgroundMusic_ = Mix_LoadMUS(filename.c_str());
            if (backgroundMusic_ == nullptr) {
                SDL_Log("SDL_Music: %s", Mix_GetError());
                throw std::runtime_error("SDL_Music: " + std::string(Mix_GetError()));
            }
            if (targetCmd->isLoop) {
                SDL_Log("bgm cmd: %s, Loop=true", filename.c_str());
                Mix_PlayMusic(backgroundMusic_, -1);
            } else {
                SDL_Log("bgm cmd: %s, Loop=false", filename.c_str());
                Mix_PlayMusic(backgroundMusic_, 0);
            }
        } else if (type == sdl::SDL_BGM_STOP) {
            // BGM_STOP case
            if (Mix_PlayingMusic() != 0) {
                // Returns non-zero if music is playing, zero otherwise.
                const int SDL_BGM_STOP_FADE_OUT_TIME = 500;
                Mix_FadeOutMusic(SDL_BGM_STOP_FADE_OUT_TIME);
            }
        } else if (type == sdl::SDL_SE) {
            // SE case
            auto targetCmd = dynamic_cast<sdl::SdlCommandSe*>(cmd.get());
            targetCmd->filename = root_path_ + core::PATH_DIR_SE + targetCmd->filename + director_->getConfig().seformat;
            // load se support .mp3 .ogg .wav formats
            Mix_Chunk* se = Mix_LoadWAV(targetCmd->filename.c_str());
            // play
            if(se == nullptr) {
                throw std::runtime_error("SDL_SE: " + std::string(Mix_GetError()));
            }
            if (targetCmd->isLoop) {
                SDL_Log("se cmd: %s, Loop=true", targetCmd->filename.c_str());
                // TODO: impl loop and stop
                SDL_Log("Warning: Loop is not implemented yet");
                // Mix_PlayChannel(-1, se, -1);
                Mix_PlayChannel(-1, se, 0);
            } else {
                SDL_Log("se cmd: %s, Loop=false", targetCmd->filename.c_str());
                Mix_PlayChannel(-1, se, 0);
            }
        } else if (type == sdl::SDL_SE_STOP) {
            // SE_STOP case
//            const int SDL_SE_STOP_FADE_OUT_TIME = 100;
//            Mix_FadeOutChannel(CHANNEL_SE, SDL_SE_STOP_FADE_OUT_TIME);
            SDL_Log("Unimpl: se stop cmd not implemented");
        } else if (type == sdl::SDL_VO) {
            // VO case
            auto targetCmd = dynamic_cast<sdl::SdlCommandVo*>(cmd.get());
            targetCmd->filename = root_path_ + core::PATH_DIR_VOICE + targetCmd->filename + director_->getConfig().voiceformat;
            // load se support .mp3 .ogg .wav formats
            Mix_Chunk* vo = Mix_LoadWAV(targetCmd->filename.c_str());
            // play
            if(vo == nullptr) {
                throw std::runtime_error("SDL_VO: " + std::string(Mix_GetError()));
            }
            SDL_Log("vo cmd: %s", targetCmd->filename.c_str());
            // halt if CHANNEL_VOICE is playing
//            if (Mix_Playing(-1)) {
//                Mix_HaltChannel(-1);
//            }
//            // Check if CHANNEL_VOICE is still playing after halting
//            if (Mix_Playing(CHANNEL_VOICE)) {
//                // Wait until CHANNEL_VOICE is not playing
//                while (Mix_Playing(CHANNEL_VOICE)) {
//                    SDL_Delay(100); // Wait for 100 milliseconds
//                }
//            }
            //TODO: bug, 一段vo没播放完就播下一个vo会崩溃。se可能也有这个bug
            Mix_PlayChannel(-1, vo, 0);
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


}

void Interface::render()
{
    // 清空渲染器
    SDL_RenderClear(renderer_);

    // 渲染背景
    SDL_RenderCopy(renderer_, backgroundTexture_, nullptr, &backgroundRect_);

    // 渲染立绘
    if (character_ != nullptr) {
        character_->render();
    } else {
        SDL_Log("Interface::render, character_->render() failed. Character is null");
    }

    // 渲染ui
    if (ui_ != nullptr) {
        ui_->render();
    } else {
        SDL_Log("Interface::render, ui_->render() failed. ui_ is null");
    }

//    SDL_Rect characterRect_;
//    characterRect_.x = 100;
//    characterRect_.y = 100;
//    characterRect_.w = 100;
//    characterRect_.h = 300;
//
//    SDL_RenderCopy(renderer_, characterTexture_, nullptr, &characterRect_);

    // 渲染文字层
    SDL_QueryTexture(textTexture_, NULL, NULL, &textRect_.w, &textRect_.h);
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


    textRect_.x = 0;
    textRect_.y = 0;
    textRect_.w = director_->getConfig().imagesize_width;
    textRect_.h = 100;

    if (backgroundMusic_ != nullptr) {
        Mix_PlayMusic(backgroundMusic_, -1);
    }

    // calculate dt
    auto last_time = std::chrono::steady_clock::now();


    bool quit = false;
    while (!quit) {
        // main loop
        const unsigned int DEFAULT_DT = 5;

        auto current_time = std::chrono::steady_clock::now();
        unsigned int dt = DEFAULT_DT; // TODO: use a real delay time
        // unsigned int dt = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - last_time).count() / 100;
        last_time = current_time;
        // SDL_Log("main loop update, dt: %d", dt);
        handleEvents();
        update(dt);
        render();
        SDL_Delay(DEFAULT_DT - 3); // TODO: set a const
    }
}



int main(int argc, char* argv[])
{
    system("chcp 65001");

    SDL_Window* window_ = SDL_CreateWindow("Hello, World!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 320, 240, SDL_WINDOW_SHOWN);

    //Interface game(window_, R"(C:\LightSong\reference\games\frfr2\android\FreeFriends2)");
    //Interface game(window_, R"(C:\LightSong\reference\games\whj1\android\desire mirror)");
    Interface game(window_, R"(C:\LightSong\reference\games\Ever17\s60v5\Ever17)");
    game.run();

    return 0;
}