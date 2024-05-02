//
// Created by EinoPlasma on 2024/5/1.
//

#ifndef LIGHTSONG_SDLCOMMAND_H
#define LIGHTSONG_SDLCOMMAND_H

#include "../../core/Command.h"
#include "string"

namespace sdl {

    enum SdlCommandType {
        SDL_EXIT, // exit system
        // 1. dialogue / text
        SDL_SAY,
        SDL_TEXT,
        SDL_TEXT_OFF,
        SDL_WAITKEY,
        SDL_TITLE,
        SDL_TITLE_DSP,
        // 2. graph
        SDL_CHARA,
        SDL_CHARA_CLS,
        SDL_CHARA_POS,
        SDL_BG,
        SDL_FLASH,
        SDL_QUAKE,
        SDL_FADE_OUT,
        SDL_FADE_IN,
        SDL_MOVIE,
        SDL_TEXTBOX,
        SDL_CHARA_QUAKE,
        SDL_CHARA_DOWN,
        SDL_CHARA_UP,
        SDL_SCROLL,
        SDL_CHARA_Y,
        SDL_CHARA_SCROLL,
        SDL_ANIME_ON,
        SDL_ANIME_OFF,
        SDL_CHARA_ANIME,
        // 3. variable / selection / jump
        SDL_SEL, // this is the only one multi lines Command in pymo
        SDL_SELECT_TEXT,
        SDL_SELECT_VAR,
        SDL_SELECT_IMG,
        SDL_SELECT_IMGS,
        SDL_WAIT,
        SDL_WAIT_SE,
        // 4. Sound
        SDL_BGM,
        SDL_BGM_STOP,
        SDL_SE,
        SDL_SE_STOP,
        SDL_VO,
        // 5. system
        SDL_LOAD,
        SDL_ALBUM,
        SDL_MUSIC,
        SDL_DATE,
        SDL_CONFIG,
    };

    class SdlCommand{
    public:
        virtual SdlCommandType type() = 0;
    };

    class SdlCommandExit : public SdlCommand {
    public:
        SdlCommandType type() override {return SDL_EXIT;}
    };

    class SdlCommandSay : public SdlCommand {
    public:
        std::string name;
        bool flag_contains_name;
        std::string content;

        SdlCommandType type() override { return SDL_SAY; }
    };

    class SdlCommandText : public SdlCommand {
    public:
        std::string content;
        int x1, y1, x2, y2;
        std::string color;
        int size;
        bool showImmediately;

        SdlCommandType type() override { return SDL_TEXT; }
    };

    class SdlCommandTextOff : public SdlCommand {
    public:
        SdlCommandType type() override { return SDL_TEXT_OFF; }

        explicit SdlCommandTextOff() = default;
    };

    class SdlCommandWaitKey : public SdlCommand {
    public:
        SdlCommandType type() override { return SDL_WAITKEY; }

        explicit SdlCommandWaitKey() = default;
    };

    class SdlCommandTitle : public SdlCommand {
    public:
        std::string content;

        SdlCommandType type() override { return SDL_TITLE; }
    };

    class SdlCommandTitleDsp : public SdlCommand {
    public:
        SdlCommandType type() override { return SDL_TITLE_DSP; }

        explicit SdlCommandTitleDsp() = default;
    };

    class SdlCommandChara : public SdlCommand {
    public:
        struct CharaInfo {
            int charaID{};
            std::string filename;
            int position{};
            int layer{};
        };

        std::vector<CharaInfo> charaInfos;
        int time;

        SdlCommandType type() override { return SDL_CHARA; }
    };

    class SdlCommandCharaCls : public SdlCommand {
    public:
        int charaID;
        int time;

        SdlCommandType type() override { return SDL_CHARA_CLS; }
    };

    class SdlCommandCharaPos : public SdlCommand {
    public:
        int charaID;
        int new_x;
        int new_y;
        int coord_mode;

        SdlCommandType type() override { return SDL_CHARA_POS; }
    };

    class SdlCommandBg : public SdlCommand {
    public:
        std::string filename;
        std::string transition;
        int time;
        int x;
        int y;

        SdlCommandType type() override { return SDL_BG; }
    };

    class SdlCommandFlash : public SdlCommand {
    public:
        std::string color;
        int time;

        SdlCommandType type() override { return SDL_FLASH; }
    };

    class SdlCommandQuake : public SdlCommand {
    public:
        SdlCommandType type() override { return SDL_QUAKE; }
    };

    class SdlCommandFadeOut : public SdlCommand {
    public:
        std::string color;
        int time;

        SdlCommandType type() override { return SDL_FADE_OUT; }
    };

    class SdlCommandFadeIn : public SdlCommand {
    public:
        int time;

        SdlCommandType type() override { return SDL_FADE_IN; }
    };

    class SdlCommandMovie : public SdlCommand {
    public:
        std::string filename;

        SdlCommandType type() override { return SDL_MOVIE; }
    };

    class SdlCommandTextBox : public SdlCommand {
    public:
        std::string messageFilename;
        std::string nameFilename;

        SdlCommandType type() override { return SDL_TEXTBOX; }
    };

    class SdlCommandCharaQuake : public SdlCommand {
    public:
        std::vector<int> charaIDs;

        SdlCommandType type() override { return SDL_CHARA_QUAKE; }
    };

    class SdlCommandCharaDown : public SdlCommand {
    public:
        std::vector<int> charaIDs;

        SdlCommandType type() override { return SDL_CHARA_DOWN; }
    };

    class SdlCommandCharaUp : public SdlCommand {
    public:
        std::vector<int> charaIDs;

        SdlCommandType type() override { return SDL_CHARA_UP; }
    };

    class SdlCommandScroll : public SdlCommand {
    public:
        std::string filename;
        double startx;
        double starty;
        double endx;
        double endy;
        int time;

        SdlCommandType type() override { return SDL_SCROLL; }
    };


    class SdlCommandCharaY : public SdlCommand {
    public:
        int coordMode;
        std::vector<std::tuple<int, std::string, int, int, int>> charaList;
        int time;

        SdlCommandType type() override { return SDL_CHARA_Y; }
    };

    class SdlCommandCharaScroll : public SdlCommand {
    public:
        int coordMode;
        int charaID;
        std::string filename;
        double startx;
        double starty;
        double endx;
        double endy;
        int beginalpha;
        int layer;
        int time;

        SdlCommandType type() override { return SDL_CHARA_SCROLL; }
    };

    class SdlCommandAnimeOn : public SdlCommand {
    public:
        int num;
        std::string filename;
        int x;
        int y;
        int interval;
        int isloop;

        SdlCommandType type() override { return SDL_ANIME_ON; }
    };

    class SdlCommandAnimeOff : public SdlCommand {
    public:
        std::string filename;

        SdlCommandType type() override { return SDL_ANIME_OFF; }
    };

    class SdlCommandCharaAnime : public SdlCommand {
    public:
        int charaID;
        int period;
        int loop_num;
        std::vector<std::pair<int, int>> offsets;

        SdlCommandType type() override { return SDL_CHARA_ANIME; }
    };

    class SdlCommandSel : public SdlCommand {
    public:
        unsigned int choiceNum;
        std::string hintPic;
        std::vector<std::string> choiceTexts;

        SdlCommandType type() override { return SDL_SEL; }
    };

    class SdlCommandSelectText : public SdlCommand {
    public:
        int choiceNum;
        std::vector<std::string> choiceTexts;
        double x1, y1, x2, y2;
        std::string color;
        int initPosition;

        SdlCommandType type() override { return SDL_SELECT_TEXT; }
    };


    class SdlCommandSelectVar : public SdlCommand {
    public:
        int choiceNum;
        std::vector<std::string> choices;
        std::vector<std::string> vars;
        double x1, y1, x2, y2;
        std::string color;
        int initPosition;

        SdlCommandType type() override { return SDL_SELECT_VAR; }
    };

    class SdlCommandSelectImg : public SdlCommand {
    public:
        int choiceNum;
        std::string filename;
        std::vector<double> xCoordinates;
        std::vector<double> yCoordinates;
        std::vector<std::string> variables;
        int initPosition;

        SdlCommandType type() override { return SDL_SELECT_IMG; }
    };


    class SdlCommandSelectImgs : public SdlCommand {
    public:
        int choiceNum;
        std::vector<std::string> filenames;
        std::vector<double> xCoords;
        std::vector<double> yCoords;
        std::vector<std::string> vars;
        int initPosition;

        SdlCommandType type() override { return SDL_SELECT_IMGS; }
    };

    class SdlCommandWait : public SdlCommand {
    public:
        int time;

        SdlCommandType type() override { return SDL_WAIT; }
    };

    class SdlCommandWaitSe : public SdlCommand {
    public:
        SdlCommandType type() override { return SDL_WAIT_SE; }
    };

    class SdlCommandBgm : public SdlCommand {
    public:
        std::string filename;
        bool isLoop;

        SdlCommandType type() override { return SDL_BGM; }
    };

    class SdlCommandBgmStop : public SdlCommand {
    public:
        SdlCommandType type() override { return SDL_BGM_STOP; }
    };

    class SdlCommandSe : public SdlCommand {
    public:
        std::string filename;
        bool isLoop;

        SdlCommandType type() override { return SDL_SE; }
    };

    class SdlCommandSeStop : public SdlCommand {
    public:
        SdlCommandType type() override { return SDL_SE_STOP; }
    };

    class SdlCommandVo : public SdlCommand {
    public:
        std::string filename;

        SdlCommandType type() override { return SDL_VO; }
    };

    class SdlCommandLoad : public SdlCommand {
    public:
        int saveNum;

        SdlCommandType type() override { return SDL_LOAD; }
    };

    class SdlCommandAlbum : public SdlCommand {
    public:
        std::string albumListFilename;

        SdlCommandType type() override { return SDL_ALBUM; }
    };

    class SdlCommandMusic : public SdlCommand {
    public:
        SdlCommandType type() override { return SDL_MUSIC; }
    };

    class SdlCommandDate : public SdlCommand {
    public:
        std::string dateBg;
        int x;
        int y;
        std::string color;

        SdlCommandType type() override { return SDL_DATE; }
    };

    class SdlCommandConfig : public SdlCommand {
    public:
        SdlCommandType type() override { return SDL_CONFIG; }
    };


} // sdl

#endif //LIGHTSONG_SDLCOMMAND_H
