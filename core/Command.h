//
// Created by KBZ on 2024/4/28.
//

#ifndef LIGHTSONG_COMMAND_H
#define LIGHTSONG_COMMAND_H

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <sstream>
#include <cassert>
#include <iostream>

namespace core {

    enum CommandType {
        // ENDOFFILE, /* 读到文件末尾直接返回一个ENDOFFILE给上级处理，或者是让上级自己检查有没有EOF，哪一种更好呢？
        PLAIN_TEXT, // It was deleted and now added back, because the #sel command is multi-line, so we can't delete all lines that don't start with # during preprocessing, so we need to mark these lines with PLAIN_TEXT
        BROKEN, // command name is valid but params are invalid
        UNKNOWN,
        // 1. dialogue / text
        SAY,
        TEXT,
        TEXT_OFF,
        WAITKEY,
        TITLE,
        TITLE_DSP,
        // 2. graph
        CHARA,
        CHARA_CLS,
        CHARA_POS,
        BG,
        FLASH,
        QUAKE,
        FADE_OUT,
        FADE_IN,
        MOVIE,
        TEXTBOX,
        CHARA_QUAKE,
        CHARA_DOWN,
        CHARA_UP,
        SCROLL,
        CHARA_Y,
        CHARA_SCROLL,
        ANIME_ON,
        ANIME_OFF,
        CHARA_ANIME,
        // 3. variable / selection / jump
        SET,
        ADD,
        SUB,
        LABEL,
        GOTO,
        IF_GOTO, // #if...goto
        CHANGE,
        CALL,
        RET,
        SEL, // this is the only one multi lines Command in pymo
        SELECT_TEXT,
        SELECT_VAR,
        SELECT_IMG,
        SELECT_IMGS,
        WAIT,
        WAIT_SE,
        RAND,
        // 4. Sound
        BGM,
        BGM_STOP,
        SE,
        SE_STOP,
        VO,
        // 5. system
        LOAD,
        ALBUM,
        MUSIC,
        DATE,
        CONFIG,
    };

    const std::unordered_map<std::string, CommandType> command_type_map ({
         {"#say", SAY},
         {"#text", TEXT},
         {"#text_off", TEXT_OFF},
         {"#waitkey", WAITKEY},
         {"#title", TITLE},
         {"#title_dsp", TITLE_DSP},
         {"#chara", CHARA},
         {"#chara_cls", CHARA_CLS},
         {"#chara_pos", CHARA_POS},
         {"#bg", BG},
         {"#flash", FLASH},
         {"#quake", QUAKE},
         {"#fade_out", FADE_OUT},
         {"#fade_in", FADE_IN},
         {"#movie", MOVIE},
         {"#textbox", TEXTBOX},
         {"#chara_quake", CHARA_QUAKE},
         {"#chara_down", CHARA_DOWN},
         {"#chara_up", CHARA_UP},
         {"#scroll", SCROLL},
         {"#chara_y", CHARA_Y},
         {"#chara_scroll", CHARA_SCROLL},
         {"#anime_on", ANIME_ON},
         {"#anime_off", ANIME_OFF},
         {"#chara_anime", CHARA_ANIME},
         {"#set", SET},
         {"#add", ADD},
         {"#sub", SUB},
         {"#label", LABEL},
         {"#goto", GOTO},
         {"#if", IF_GOTO},
         {"#change", CHANGE},
         {"#call", CALL},
         {"#ret", RET},
         {"#sel", SEL},
         {"#select_text", SELECT_TEXT},
         {"#select_var", SELECT_VAR},
         {"#select_img", SELECT_IMG},
         {"#select_imgs", SELECT_IMGS},
         {"#wait", WAIT},
         {"#wait_se", WAIT_SE},
         {"#rand", RAND},
         {"#bgm", BGM},
         {"#bgm_stop", BGM_STOP},
         {"#se", SE},
         {"#se_stop", SE_STOP},
         {"#vo", VO},
         {"#load", LOAD},
         {"#album", ALBUM},
         {"#music", MUSIC},
         {"#date", DATE},
         {"#config", CONFIG},
    });

    class Command {
    public:
        virtual CommandType type() = 0;
    };

    class CommandPlainText : public Command {
    public:
        std::string command_literal;

        CommandType type() override { return PLAIN_TEXT; }

        explicit CommandPlainText(const std::vector<std::string>& params) {
            // It takes only one parameter for record the command_literal
            if (params.size() != 1) {
                throw std::invalid_argument("Invalid parameter size. Expected 1 parameter.");
            }
            this->command_literal = params[0];
        }
    };

    class CommandBroken : public Command {
    public:
        CommandType type() override { return BROKEN; }
    };

    class CommandUnknown : public Command {
    public:
        CommandType type() override { return UNKNOWN; }
    };

    class CommandSay : public Command {
    public:
        std::string name;
        bool flag_contains_name;
        std::string content;

        CommandType type() override { return SAY; }

        explicit CommandSay(const std::vector<std::string>& params) {
            if (params.size() != 2 && params.size() != 1) {
                throw std::invalid_argument("Invalid parameter size. Expected 2 or 1 parameters.");
            }
            if (params.size() == 2) {
                name = params[0];
                content = params[1];
                flag_contains_name = true;
            } else {
                content = params[0];
                flag_contains_name = false;
            }
        }
    };

    class CommandText : public Command {
    public:
        std::string content;
        int x1, y1, x2, y2;
        std::string color;
        int size;
        bool showImmediately;

        CommandType type() override { return TEXT; }

        explicit CommandText(const std::vector<std::string>& params) {
            if (params.size() != 7 && params.size() != 8) {
                throw std::invalid_argument("Invalid parameter size. Expected 7 or 8 parameters.");
            }
            if (params.size() >= 7) {
                content = params[0];
                x1 = std::stoi(params[1]);
                y1 = std::stoi(params[2]);
                x2 = std::stoi(params[3]);
                y2 = std::stoi(params[4]);
                color = params[5];
                size = std::stoi(params[6]);
                showImmediately = (params.size() >= 8 && params[7] == "true");
            }
        }
    };

    class CommandTextOff : public Command {
    public:
        CommandType type() override { return TEXT_OFF; }

        explicit CommandTextOff() = default;
    };

    class CommandWaitKey : public Command {
    public:
        CommandType type() override { return WAITKEY; }

        explicit CommandWaitKey() = default;
    };

    class CommandTitle : public Command {
    public:
        std::string content;

        CommandType type() override { return TITLE; }

        explicit CommandTitle(const std::vector<std::string>& params) {
            if (params.size() != 1) {
                throw std::invalid_argument("Invalid parameter size. Expected 1 parameter.");
            }
            content = params[0];
        }
    };

    class CommandTitleDsp : public Command {
    public:
        CommandType type() override { return TITLE_DSP; }

        explicit CommandTitleDsp() = default;
    };

    class CommandChara : public Command {
    public:
        struct CharaInfo {
            int charaID{};
            std::string filename;
            int position{};
            int layer{};
        };

        std::vector<CharaInfo> charaInfos;
        int time;

        CommandType type() override { return CHARA; }

        explicit CommandChara(const std::vector<std::string>& params) {
            if ((params.size() - 1) % 4 == 0) {
                throw std::invalid_argument("Invalid parameter size. Expected (params.size() - 1) % 4 == 0 parameters.");
            }
            // Parse the parameters and populate the charaInfos vector
            for (size_t i = 0; i < params.size() - 1; i += 4) {
                CharaInfo charaInfo;
                charaInfo.charaID = std::stoi(params[i]);
                charaInfo.filename = params[i + 1];
                charaInfo.position = std::stoi(params[i + 2]);
                charaInfo.layer = std::stoi(params[i + 3]);
                charaInfos.push_back(charaInfo);
            }
            time = std::stoi(params.back());
        }
    };

    class CommandCharaCls : public Command {
    public:
        int charaID;
        int time;

        CommandType type() override { return CHARA_CLS; }

        explicit CommandCharaCls(const std::vector<std::string>& params) {
            if (params.size() != 1 && params.size() != 2) {
                throw std::invalid_argument("Invalid parameter size. Expected 1 or 2 parameters.");
            }
            charaID = (params[0] == "a") ? -1 : std::stoi(params[0]);
            time = (params.size() > 1) ? std::stoi(params[1]) : 300;
        }
    };

    class CommandCharaPos : public Command {
    public:
        int charaID;
        int new_x;
        int new_y;
        int coord_mode;

        CommandType type() override { return CHARA_POS; }

        explicit CommandCharaPos(const std::vector<std::string>& params) {
            if (params.size() != 4) {
                throw std::invalid_argument("Invalid parameter size. Expected 4 parameters.");
            }
            charaID = std::stoi(params[0]);
            new_x = std::stoi(params[1]);
            new_y = std::stoi(params[2]);
            coord_mode = std::stoi(params[3]);
        }
    };

    class CommandBg : public Command {
    public:
        std::string filename;
        std::string transition;
        int time;
        int x;
        int y;

        CommandType type() override { return BG; }

        explicit CommandBg(const std::vector<std::string>& params) {
            if (params.size() != 1 && params.size() != 3 && params.size() != 5) {
                throw std::invalid_argument("Invalid parameter size. Expected 1 or 3 or 5 parameters.");
            }
            filename = params[0];

            x = 0; // Default x
            y = 0; // Default y
            transition = "BG_ALPHA"; // Default transition
            time = 300; // Default time

            if (params.size() == 3) {
                transition = params[1];
                time = std::stoi(params[2]);
            }
            if (params.size() == 5) {
                transition = params[1];
                time = std::stoi(params[2]);
                x = std::stoi(params[3]);
                y = std::stoi(params[4]);
            }
        }
    };

    class CommandFlash : public Command {
    public:
        std::string color;
        int time;

        CommandType type() override { return FLASH; }

        explicit CommandFlash(const std::vector<std::string>& params) {
            if (params.size() != 2) {
                throw std::invalid_argument("Invalid parameter size. Expected 2 parameters.");
            }
            color = params[0];
            time = std::stoi(params[1]);
        }
    };

    class CommandQuake : public Command {
    public:
        CommandType type() override { return QUAKE; }
    };

    class CommandFadeOut : public Command {
    public:
        std::string color;
        int time;

        CommandType type() override { return FADE_OUT; }

        explicit CommandFadeOut(const std::vector<std::string>& params) {
            if (params.size() != 2) {
                throw std::invalid_argument("Invalid parameter size. Expected 2 parameters.");
            }
            color = params[0];
            time = std::stoi(params[1]);
        }
    };

    class CommandFadeIn : public Command {
    public:
        int time;

        CommandType type() override { return FADE_IN; }

        explicit CommandFadeIn(const std::vector<std::string>& params) {
            if (params.size() != 1) {
                throw std::invalid_argument("Invalid parameter size. Expected 1 parameter.");
            }
            time = std::stoi(params[0]);
        }
    };

    class CommandMovie : public Command {
    public:
        std::string filename;

        CommandType type() override { return MOVIE; }

        explicit CommandMovie(const std::vector<std::string>& params) {
            if (params.size() != 1) {
                throw std::invalid_argument("Invalid parameter size. Expected 1 parameter.");
            }
            filename = params[0];
        }
    };

    class CommandTextBox : public Command {
    public:
        std::string messageFilename;
        std::string nameFilename;

        CommandType type() override { return TEXTBOX; }

        explicit CommandTextBox(const std::vector<std::string>& params) {
            if (params.size() != 2) {
                throw std::invalid_argument("Invalid parameter size. Expected 2 parameters.");
            }
            messageFilename = params[0];
            nameFilename = params[1];
        }
    };

    class CommandCharaQuake : public Command {
    public:
        std::vector<int> charaIDs;

        CommandType type() override { return CHARA_QUAKE; }

        explicit CommandCharaQuake(const std::vector<std::string>& params) {
            for (const std::string& param : params) {
                charaIDs.push_back(std::stoi(param));
            }
        }
    };

    class CommandCharaDown : public Command {
    public:
        std::vector<int> charaIDs;

        CommandType type() override { return CHARA_DOWN; }

        explicit CommandCharaDown(const std::vector<std::string>& params) {
            for (const std::string& param : params) {
                charaIDs.push_back(std::stoi(param));
            }
        }
    };

    class CommandCharaUp : public Command {
    public:
        std::vector<int> charaIDs;

        CommandType type() override { return CHARA_UP; }

        explicit CommandCharaUp(const std::vector<std::string>& params) {
            for (const std::string& param : params) {
                charaIDs.push_back(std::stoi(param));
            }
        }
    };

    class CommandScroll : public Command {
    public:
        std::string filename;
        double startx;
        double starty;
        double endx;
        double endy;
        int time;

        CommandType type() override { return SCROLL; }

        explicit CommandScroll(const std::vector<std::string>& params) {
            if (params.size() != 6) {
                throw std::invalid_argument("Invalid parameter size. Expected 6 parameters.");
            }
            filename = params[0];
            startx = std::stod(params[1]);
            starty = std::stod(params[2]);
            endx = std::stod(params[3]);
            endy = std::stod(params[4]);
            time = std::stoi(params[5]);
        }
    };


    class CommandCharaY : public Command {
    public:
        int coordMode;
        std::vector<std::tuple<int, std::string, int, int, int>> charaList;
        int time;

        CommandType type() override { return CHARA_Y; }

        explicit CommandCharaY(const std::vector<std::string>& params) {
            if ((params.size() - 2) % 5 == 0) {
                throw std::invalid_argument("Invalid parameter size. Expected (params.size() - 2) % 5 == 0 parameters.");
            }

            coordMode = std::stoi(params[0]);

            int paramCount = params.size();
            int charaCount = (paramCount - 2) / 5;
            for (int i = 0; i < charaCount; ++i) {
                int startIndex = 1 + i * 5;
                int charaID = std::stoi(params[startIndex]);
                std::string filename = params[startIndex + 1];
                int x = std::stoi(params[startIndex + 2]);
                int y = std::stoi(params[startIndex + 3]);
                int layer = std::stoi(params[startIndex + 4]);
                charaList.emplace_back(charaID, filename, x, y, layer);
            }

            time = std::stoi(params[paramCount - 1]);
        }
    };

    class CommandCharaScroll : public Command {
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

        CommandType type() override { return CHARA_SCROLL; }

        explicit CommandCharaScroll(const std::vector<std::string>& params) {
            if (params.size() != 6 && params.size() != 10) {
                throw std::invalid_argument("Invalid parameter size. Expected 6 or 10 parameters.");
            }
            coordMode = std::stoi(params[0]);
            charaID = std::stoi(params[1]);
            int paramCount = params.size();

            if (paramCount == 6) {
                endx = std::stod(params[2]);
                endy = std::stod(params[3]);
                time = std::stoi(params[4]);
            } else if (paramCount == 10) {
                filename = params[2];
                startx = std::stod(params[3]);
                starty = std::stod(params[4]);
                endx = std::stod(params[5]);
                endy = std::stod(params[6]);
                beginalpha = std::stoi(params[7]);
                layer = std::stoi(params[8]);
                time = std::stoi(params[9]);
            }
        }
    };

    class CommandAnimeOn : public Command {
    public:
        int num;
        std::string filename;
        int x;
        int y;
        int interval;
        int isloop;

        CommandType type() override { return ANIME_ON; }

        explicit CommandAnimeOn(const std::vector<std::string>& params) {
            if (params.size() != 6) {
                throw std::invalid_argument("Invalid parameter size. Expected 6parameters.");
            }
            num = std::stoi(params[0]);
            filename = params[1];
            x = std::stoi(params[2]);
            y = std::stoi(params[3]);
            interval = std::stoi(params[4]);
            isloop = std::stoi(params[5]);
        }
    };

    class CommandAnimeOff : public Command {
    public:
        std::string filename;

        CommandType type() override { return ANIME_OFF; }

        explicit CommandAnimeOff(const std::vector<std::string>& params) {
            if (params.size() != 1) {
                throw std::invalid_argument("Invalid parameter size. Expected 1 parameters.");
            }
            filename = params[0];
        }
    };

    class CommandCharaAnime : public Command {
    public:
        int charaID;
        int period;
        int loop_num;
        std::vector<std::pair<int, int>> offsets;

        CommandType type() override { return CHARA_ANIME; }

        explicit CommandCharaAnime(const std::vector<std::string>& params) {
            if (params.size() < 3) {
                throw std::invalid_argument("Invalid parameter size. Expected at least 3 parameters.");
            }

            charaID = std::stoi(params[0]);
            period = std::stoi(params[1]);
            loop_num = std::stoi(params[2]);

            for (int i = 3; i < params.size(); i += 2) {
                int offset_x = std::stoi(params[i]);
                int offset_y = std::stoi(params[i + 1]);
                offsets.emplace_back(offset_x, offset_y);
            }
        }
    };


    class CommandSet : public Command {
    public:
        std::string var_name;
        std::string var_value;

        CommandType type() override { return SET; }

        explicit CommandSet(const std::vector<std::string>& params) {
            if (params.size() != 2) {
                throw std::invalid_argument("Invalid parameter size. Expected 2 parameters.");
            }
            var_name = params[0];
            var_value = params[1];
        }
    };

    class CommandAdd : public Command {
    public:
        std::string var_name;
        std::string add_value;

        CommandType type() override { return ADD; }

        explicit CommandAdd(const std::vector<std::string>& params) {
            if (params.size() != 2) {
                throw std::invalid_argument("Invalid parameter size. Expected 2 parameters.");
            }
            var_name = params[0];
            add_value = params[1];
        }
    };

    class CommandSub : public Command {
    public:
        std::string var_name;
        std::string sub_value;

        CommandType type() override { return SUB; }

        explicit CommandSub(const std::vector<std::string>& params) {
            if (params.size() != 2) {
                throw std::invalid_argument("Invalid parameter size. Expected 2 parameters.");
            }
            var_name = params[0];
            sub_value = params[1];

        }
    };

    class CommandLabel : public Command {
    public:
        std::string label_name;

        CommandType type() override { return LABEL; }

        explicit CommandLabel(const std::vector<std::string>& params) {
            if (params.size() != 1) {
                throw std::invalid_argument("Invalid parameter size. Expected 1 parameter.");
            }
            label_name = params[0];
        }
    };

    class CommandGoto : public Command {
    public:
        std::string label_name;

        CommandType type() override { return GOTO; }

        explicit CommandGoto(const std::vector<std::string>& params) {
            if (params.size() != 1) {
                throw std::invalid_argument("Invalid parameter size. Expected 1 parameter.");
            }
            label_name = params[0];

        }
    };

    class CommandIfGoto : public Command {
    public:
        enum ComparisonType {
            EQUAL,
            GREATER_THAN,
            LESS_THAN,
            GREATER_THAN_OR_EQUAL,
            LESS_THAN_OR_EQUAL,
            NOT_EQUAL
        };
        std::string condition_literal;
        std::string left_operand, right_operand;
        ComparisonType comparison_type;
        std::string label_name;

        CommandType type() override { return IF_GOTO; }

        explicit CommandIfGoto(const std::vector<std::string>& params) {
            if (params.size() != 2) {
                throw std::invalid_argument("Invalid parameter size. Expected 2 parameters.");
            }
            condition_literal = params[0];
            std::string condition_operator;
            if (condition_literal.find("!=") != std::string::npos) {
                comparison_type = NOT_EQUAL;
                condition_operator = "!=";
            } else if (condition_literal.find(">=") != std::string::npos) {
                comparison_type = GREATER_THAN_OR_EQUAL;
                condition_operator = ">=";
            } else if (condition_literal.find("<=") != std::string::npos) {
                comparison_type = LESS_THAN_OR_EQUAL;
                condition_operator = "<=";
            } else if (condition_literal.find('=') != std::string::npos) {
                comparison_type = EQUAL;
                condition_operator = "=";
            } else if (condition_literal.find('>') != std::string::npos) {
                comparison_type = GREATER_THAN;
                condition_operator = ">";
            } else if (condition_literal.find('<') != std::string::npos) {
                comparison_type = LESS_THAN;
                condition_operator = "<";
            }

            size_t operator_pos = condition_literal.find(condition_operator);
            left_operand = condition_literal.substr(0, operator_pos);
            right_operand = condition_literal.substr(operator_pos + condition_operator.length());

            std::string goto_command_literal = params[1], foo;
            std::stringstream goto_command_stream;
            goto_command_stream << goto_command_literal;
            goto_command_stream >> foo; // eat "goto"
            goto_command_stream >> label_name;
        }
    };

    class CommandChange : public Command {
    public:
        std::string filename;

        CommandType type() override { return CHANGE; }

        explicit CommandChange(const std::vector<std::string>& params) {
            if (params.size() != 1) {
                throw std::invalid_argument("Invalid parameter size. Expected 1 parameter.");
            }
            filename = params[0]; // filename：脚本文件名，**不加扩展名**
        }
    };

    class CommandCall : public Command {
    public:
        std::string filename;

        CommandType type() override { return CALL; }

        explicit CommandCall(const std::vector<std::string>& params) {
            if (params.size() != 1) {
                throw std::invalid_argument("Invalid parameter size. Expected 1 parameter.");
            }
            filename = params[0]; // filename：脚本文件名，**不加扩展名**
        }
    };

    class CommandRet : public Command {
    public:
        CommandType type() override { return RET; }
    };

    class CommandSel : public Command {
    public:
        unsigned int choiceNum;
        std::string hintPic;
        std::vector<std::string> choiceTexts;

        CommandType type() override { return SEL; }

        explicit CommandSel(const std::vector<std::string>& params) {
            if (params.size() != 1 && params.size() != 2) {
                throw std::invalid_argument("Invalid parameter size. Expected 1 or 2 parameters.");
            }
            // TODO: CommandSel的跨行处理
            choiceNum = std::stoi(params[0]);
            if (params.size() > 1){
                hintPic = params[1];
            }
        }
    };

    class CommandSelectText : public Command {
    public:
        int choiceNum;
        std::vector<std::string> choiceTexts;
        double x1, y1, x2, y2;
        std::string color;
        int initPosition;

        CommandType type() override { return SELECT_TEXT; }

        explicit CommandSelectText(const std::vector<std::string>& params) {
            choiceNum = std::stoi(params[0]);
            if (params.size() != choiceNum + 6) {
                throw std::invalid_argument("Invalid parameter size. Expected `choiceNum + 6` parameters.");
            }
            for (int i = 1; i <= choiceNum; i++) {
                choiceTexts.push_back(params[i]);
            }
            x1 = std::stod(params[choiceNum + 1]);
            y1 = std::stod(params[choiceNum + 2]);
            x2 = std::stod(params[choiceNum + 3]);
            y2 = std::stod(params[choiceNum + 4]);
            color = params[choiceNum + 5];
            initPosition = std::stoi(params[choiceNum + 6]);
        }
    };


    class CommandSelectVar : public Command {
    public:
        int choiceNum;
        std::vector<std::string> choices;
        std::vector<std::string> vars;
        double x1, y1, x2, y2;
        std::string color;
        int initPosition;

        CommandType type() override { return SELECT_VAR; }

        explicit CommandSelectVar(const std::vector<std::string>& params) {
            choiceNum = std::stoi(params[0]);
            if (params.size() != 2 * choiceNum + 6) {
                throw std::invalid_argument("Invalid parameter size. Expected `2 * choiceNum + 6` parameters.");
            }
            for (int i = 1; i <= choiceNum; i++) {
                choices.push_back(params[i]);
                vars.push_back(params[i + choiceNum]);
            }
            x1 = std::stod(params[2 * choiceNum + 1]);
            y1 = std::stod(params[2 * choiceNum + 2]);
            x2 = std::stod(params[2 * choiceNum + 3]);
            y2 = std::stod(params[2 * choiceNum + 4]);
            color = params[2 * choiceNum + 5];
            initPosition = std::stoi(params[2 * choiceNum + 6]);
        }
    };

    class CommandSelectImg : public Command {
    public:
        int choiceNum;
        std::string filename;
        std::vector<double> xCoordinates;
        std::vector<double> yCoordinates;
        std::vector<std::string> variables;
        int initPosition;

        CommandType type() override { return SELECT_IMG; }

        explicit CommandSelectImg(const std::vector<std::string>& params) {
            if (params.size() < 4) {
                throw std::invalid_argument("Invalid parameter size. Expected `see document` parameters.");
            }
            if (params.size() >= 4) {
                choiceNum = std::stoi(params[0]);
                filename = params[1];
                initPosition = std::stoi(params.back());

                // Parse x, y coordinates and variables
                for (int i = 2; i < params.size() - 1; i += 3) {
                    xCoordinates.push_back(std::stod(params[i]));
                    yCoordinates.push_back(std::stod(params[i + 1]));
                    variables.push_back(params[i + 2]);
                }
            }
        }
    };


    class CommandSelectImgs : public Command {
    public:
        int choiceNum;
        std::vector<std::string> filenames;
        std::vector<double> xCoords;
        std::vector<double> yCoords;
        std::vector<std::string> vars;
        int initPosition;

        CommandType type() override { return SELECT_IMGS; }

        explicit CommandSelectImgs(const std::vector<std::string>& params) {
            choiceNum = std::stoi(params[0]);
            if (params.size() != choiceNum * 4 + 1) {
                throw std::invalid_argument("Invalid parameter size. Expected `choiceNum * 4 + 1` parameters.");
            }
            for (int i = 0; i < choiceNum; i++) {
                filenames.push_back(params[i * 4 + 1]);
                xCoords.push_back(std::stod(params[i * 4 + 2]));
                yCoords.push_back(std::stod(params[i * 4 + 3]));
                vars.push_back(params[i * 4 + 4]);
            }
            initPosition = std::stoi(params[choiceNum * 4 + 1]);
        }
    };

    class CommandWait : public Command {
    public:
        int time;

        CommandType type() override { return WAIT; }

        explicit CommandWait(const std::vector<std::string>& params) {
            if (params.size() != 1) {
                throw std::invalid_argument("Invalid parameter size. Expected 1 parameter.");
            }
            time = std::stoi(params[0]);
        }
    };

    class CommandWaitSe : public Command {
    public:
        CommandType type() override { return WAIT_SE; }
    };

    class CommandRand : public Command {
    public:
        std::string varName;
        int minValue;
        int maxValue;

        CommandType type() override { return RAND; }

        explicit CommandRand(const std::vector<std::string>& params) {
            if (params.size() != 3) {
                throw std::invalid_argument("Invalid parameter size. Expected 3 parameters.");
            }
            varName = params[0];
            minValue = std::stoi(params[1]);
            maxValue = std::stoi(params[2]);
        }
    };

    class CommandBgm : public Command {
    public:
        std::string filename;
        bool isLoop;

        CommandType type() override { return BGM; }

        explicit CommandBgm(const std::vector<std::string>& params) {
            if (params.size() != 2 && params.size() != 1) {
                throw std::invalid_argument("Invalid parameter size. Expected 2 or 1 parameters.");
            }
            filename = params[0];
            if (params.size() > 1) {
                isLoop = (params[1] == "1");
            } else {
                isLoop = true;  // Default is loop
            }
        }
    };

    class CommandBgmStop : public Command {
    public:
        CommandType type() override { return BGM_STOP; }
    };

    class CommandSe : public Command {
    public:
        std::string filename;
        bool isLoop;

        CommandType type() override { return SE; }

        explicit CommandSe(const std::vector<std::string>& params) {
            if (params.size() != 2 && params.size() != 1) {
                throw std::invalid_argument("Invalid parameter size. Expected 2 or 1 parameters.");
            }
            filename = params[0];
            if (params.size() > 1) {
                isLoop = (params[1] == "1");
            } else {
                isLoop = false;  // Default is not loop
            }
        }
    };

    class CommandSeStop : public Command {
    public:
        CommandType type() override { return SE_STOP; }
    };

    class CommandVo : public Command {
    public:
        std::string filename;

        CommandType type() override { return VO; }

        explicit CommandVo(const std::vector<std::string>& params) {
            if (params.size() != 1) {
                throw std::invalid_argument("Invalid parameter size. Expected 1 parameter.");
            }
            filename = params[0]; // 音频文件名，不加扩展名
        }
    };

    class CommandLoad : public Command {
    public:
        int saveNum;

        CommandType type() override { return LOAD; }

        explicit CommandLoad(const std::vector<std::string>& params) {
            if (!params.empty() && params.size() != 1) {
                throw std::invalid_argument("Invalid parameter size. Expected 0 or 1 parameters.");
            }
            if (params.empty()) {
                saveNum = -1;  // Load save screen
            } else {
                saveNum = std::stoi(params[0]);
            }
        }
    };

    class CommandAlbum : public Command {
    public:
        std::string albumListFilename;

        CommandType type() override { return ALBUM; }

        explicit CommandAlbum(const std::vector<std::string>& params) {
            if (!params.empty() && params.size() != 1) {
                throw std::invalid_argument("Invalid parameter size. Expected 0 or 1 parameters.");
            }
            if (params.empty()) {
                albumListFilename = "album_list.txt";  // Default album list filename
            } else {
                albumListFilename = params[0];
            }
        }
    };

    class CommandMusic : public Command {
    public:
        CommandType type() override { return MUSIC; }
    };

    class CommandDate : public Command {
    public:
        std::string dateBg;
        int x;
        int y;
        std::string color;

        CommandType type() override { return DATE; }

        explicit CommandDate(const std::vector<std::string>& params) {
            if (params.size() != 3 && params.size() != 4) {
                throw std::invalid_argument("Invalid parameter size. Expected 3 or 4 parameters.");
            }
            // TODO: 和文档与原版实现对比确认此处实现无误
            if (params.size() == 3) {
                x = std::stoi(params[0]);
                y = std::stoi(params[1]);
                color = params[2];
            } else {
                dateBg = params[0];
                x = std::stoi(params[1]);
                y = std::stoi(params[2]);
                color = params[3];
            }
        }
    };

    class CommandConfig : public Command {
    public:
        CommandType type() override { return CONFIG; }
    };

    // Factory function to create a Command object based on the provided Command type and parameters
    std::unique_ptr<Command> createCommand(CommandType type,const std::vector<std::string>& params);

} // core

#endif //LIGHTSONG_COMMAND_H