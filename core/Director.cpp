//
// Created by KBZ on 2024/4/28.
//
#include "iostream"
#include "Director.h"

#include <memory>
#include <unordered_set>
#include "GameConfig.h"
#include "EnginePath.h"
#include "Command.h"

#include "../platform/cli/CliCommand.h"
#include "../utils.h"
#include "../platform/sdl/SdlCommand.h"

namespace core {
    Director::Director(std::basic_string<char> root_path): root_path(root_path) {
        environment = std::make_unique<Environment>(root_path + PATH_FILE_GAMECONFIG);
        std::string start_script = environment->getConfig().startscript;
        environment->curr_script_name = start_script;
        environment->curr_script_line_number = 0;

        parser = loadScript(root_path + PATH_DIR_SCRIPT + start_script + CONFIG_SCRITP_SUFFIX);
    }

    std::unique_ptr<cli::CliCommand> Director::nextCliCommand() {
        // 返回一个cli绘图指令（待定义）。cli每次做的事情就是问director要一个绘图指令，再执行它。director负责goto、if、change、select等流程控制
        while (environment->curr_script_line_number < parser->getLineCount()) {
            std::unique_ptr<Command> cmd = parser->peek(environment->curr_script_line_number++);
            CommandType type = cmd->type();

            if (type == PLAIN_TEXT) {
                // BLANK case
            } else if (type == UNKNOWN) {
                // UNKNOWN case
            } else if (type == BROKEN) {
                // BROKEN case
            } else if (type == SAY) {
                auto targetCmd = dynamic_cast<CommandSay*>(cmd.get()); // 因为cmd(Command对象)没有name、content等成员，所以我们需要用动态类型转换，转成CommandSay对象
                return std::make_unique<cli::CliCommandEcho>(targetCmd->name + targetCmd->content);
                /*
                 * 问题：我用cmd.get()把std::unique_ptr<Command>的裸指针取出来用，不用担心内存泄露吗？
                 *
                 * 在使用智能指针的情况下，不需要手动释放内存，因为智能指针会在其生命周期结束时自动释放关联的内存。
                 * 在你的代码中，cmd是一个std::unique_ptr<Command>类型的智能指针，它拥有对Command对象的所有权。当cmd超出其作用域时（在函数结束时），std::unique_ptr将自动释放关联的内存，确保没有内存泄漏。
                 * 同样地，cmdSay是一个指向CommandSay对象的裸指针，在你的代码中并没有手动释放关联的内存。由于cmdSay只是一个指针，并没有所有权，因此它不负责释放内存。实际上，cmdSay指针的生命周期与cmd指针相同，当cmd超出作用域时，cmdSay指针也会失效，不会导致内存泄漏。
                 * 因此，使用智能指针std::unique_ptr可以确保在适当的时候自动释放内存，避免了内存泄漏的问题。
                 * */
            } else if (type == TEXT) {
                auto targetCmd = dynamic_cast<CommandText*>(cmd.get()); // 因为cmd(Command对象)没有name、content等成员，所以我们需要用动态类型转换，转成CommandSay对象
                return std::make_unique<cli::CliCommandEcho>(std::string(targetCmd->content));
            } else if (type == TEXT_OFF) {
                // TEXT_OFF case
            } else if (type == WAITKEY) {
                // WAITKEY case
            } else if (type == TITLE) {
                auto targetCmd = dynamic_cast<CommandTitle*>(cmd.get()); // 因为cmd(Command对象)没有name、content等成员，所以我们需要用动态类型转换，转成CommandSay对象
                return std::make_unique<cli::CliCommandEcho>(std::string(targetCmd->content));
            } else if (type == TITLE_DSP) {
                // TITLE_DSP case
            } else if (type == CHARA) {
                // CHARA case
            } else if (type == CHARA_CLS) {
                // CHARA_CLS case
            } else if (type == CHARA_POS) {
                // CHARA_POS case
            } else if (type == BG) {
                // BG case
            } else if (type == FLASH) {
                // FLASH case
            } else if (type == QUAKE) {
                // QUAKE case
            } else if (type == FADE_OUT) {
                // FADE_OUT case
            } else if (type == FADE_IN) {
                // FADE_IN case
            } else if (type == MOVIE) {
                // MOVIE case
            } else if (type == TEXTBOX) {
                // TEXTBOX case
            } else if (type == CHARA_QUAKE) {
                // CHARA_QUAKE case
            } else if (type == CHARA_DOWN) {
                // CHARA_DOWN case
            } else if (type == CHARA_UP) {
                // CHARA_UP case
            } else if (type == SCROLL) {
                // SCROLL case
            } else if (type == CHARA_Y) {
                // CHARA_Y case
            } else if (type == CHARA_SCROLL) {
                // CHARA_SCROLL case
            } else if (type == ANIME_ON) {
                // ANIME_ON case
            } else if (type == ANIME_OFF) {
                // ANIME_OFF case
            } else if (type == CHARA_ANIME) {
                // CHARA_ANIME case
            } else if (type == SET) {
                auto targetCmd = dynamic_cast<CommandSet*>(cmd.get());
                environment->set(targetCmd->var_name, targetCmd->var_value);
            } else if (type == ADD) {
                auto targetCmd = dynamic_cast<CommandAdd*>(cmd.get());
                environment->add(targetCmd->var_name, targetCmd->add_value, false);
            } else if (type == SUB) {
                auto targetCmd = dynamic_cast<CommandAdd*>(cmd.get());
                environment->sub(targetCmd->var_name, targetCmd->add_value);
            } else if (type == LABEL) {
                // LABEL case
            } else if (type == GOTO) {
                // 跳转到当前脚本里指定的行标签
                auto targetCmd = dynamic_cast<CommandGoto*>(cmd.get());
                environment->curr_script_line_number = parser->findLabel(targetCmd->label_name);
            } else if (type == IF_GOTO) {
                bool flagIgnoreThisCommand = false; // 如果右操作数为变量且变量未被赋值过，系统会忽略这条 if 语句。

                auto targetCmd = dynamic_cast<CommandIfGoto*>(cmd.get());

                std::string left_operand = targetCmd->left_operand;
                CommandIfGoto::ComparisonType comparison_type = targetCmd->comparison_type;
                std::string right_operand = targetCmd->right_operand;

                // 检查左操作数是否存在，如果不存在，系统将其看作0来比较
                int left_value = 0;
                bool left_exists = environment->varExists(left_operand);
                if (left_exists) {
                   left_value = environment->getVar(left_operand);
                }

                int right_value = 0;
                // 如果右操作数是变量，则检查其是否存在
                if (isIdentifier(right_operand)) {
                    if (environment->varExists(right_operand)) {
                        right_value = environment->getVar(right_operand);
                    } else {
                        flagIgnoreThisCommand = true;
                    }
                } else {
                    right_value = std::stoi(right_operand);
                }

                if (!flagIgnoreThisCommand) {
                    // 根据比较类型执行相应的操作
                    bool condition_met = false;
                    switch (comparison_type) {
                        case CommandIfGoto::EQUAL:
                            condition_met = (left_value == right_value);
                            break;
                        case CommandIfGoto::GREATER_THAN:
                            condition_met = (left_value > right_value);
                            break;
                        case CommandIfGoto::LESS_THAN:
                            condition_met = (left_value < right_value);
                            break;
                        case CommandIfGoto::GREATER_THAN_OR_EQUAL:
                            condition_met = (left_value >= right_value);
                            break;
                        case CommandIfGoto::LESS_THAN_OR_EQUAL:
                            condition_met = (left_value <= right_value);
                            break;
                        case CommandIfGoto::NOT_EQUAL:
                            condition_met = (left_value != right_value);
                            break;
                        default:
                            // 处理未知的比较类型
                            break;
                    }

                    if (condition_met) {
                        // 跳转到指定的行（标签）
                        environment->curr_script_line_number = parser->findLabel(targetCmd->label_name);
                    }
                }

            } else if (type == CHANGE) {
                // 不带返回的脚本文件跳转。直接更换脚本文件
                auto targetCmd = dynamic_cast<CommandChange*>(cmd.get());
                environment->curr_script_name = targetCmd->filename;
                environment->curr_script_line_number = 0;
                parser = std::move(loadScript(root_path + PATH_DIR_SCRIPT + targetCmd->filename + CONFIG_SCRITP_SUFFIX));
            } else if (type == CALL) {
                // CALL case
                auto targetCmd = dynamic_cast<CommandCall*>(cmd.get());
                CallStackItem stackItem = CallStackItem{environment->curr_script_name, environment->curr_script_line_number};
                environment->pushCallStack(stackItem);
                environment->curr_script_name = targetCmd->filename;
                environment->curr_script_line_number = 0;
                parser = std::move(loadScript(root_path + PATH_DIR_SCRIPT + targetCmd->filename + CONFIG_SCRITP_SUFFIX));
            } else if (type == RET) {
                // RET case
                CallStackItem stackItem = environment->popCallStack();
                environment->curr_script_name = stackItem.script_name;
                environment->curr_script_line_number = stackItem.line_number;
                parser = std::move(loadScript(root_path + PATH_DIR_SCRIPT + environment->curr_script_name + CONFIG_SCRITP_SUFFIX));
            } else if (type == SEL) {
                // SEL case
//                #sel 2
//                我是选项一
//                我是选项二
//                #if FSEL=0, goto TEST_SELECTION_01
//                #if FSEL=1, goto TEST_SELECTION_02
//                #label TEST_SELECTION_01
//                #say 你选了选项一
//                #goto TEST_SELECTION_END
//                #label TEST_SELECTION_02
//                #say 你选了选项二
//                #goto TEST_SELECTION_END
//                #label TEST_SELECTION_END
//                #say 选择支结束，重回共通部分

                auto targetCmd = dynamic_cast<CommandSel*>(cmd.get());
                unsigned int choice_num = targetCmd->choiceNum;
                std::vector<std::string> choices;
                for (unsigned int i = 0; i < choice_num; i++) {
                    auto choice_line = parser->peek(environment->curr_script_line_number++);
                    if (choice_line->type() != PLAIN_TEXT) {
                        throw std::runtime_error("Expected PLAIN_TEXT line after #sel command");
                    }
                    std::string choice_text = dynamic_cast<CommandPlainText*>(choice_line.get())->command_literal;
                    choices.push_back(choice_text);
                }
                /*
                 * 根据绘图指令队列模型，platform读取绘图指令时读到 #sel 指令就会停下，待获得用户选择的结果后会调用 Director::setFSEL() 把结果交给Director后，才继续向Director要绘图指令
                 */
                return std::make_unique<cli::CliCommandSel>(choices);
            } else if (type == SELECT_TEXT) {
                // SELECT_TEXT case
            } else if (type == SELECT_VAR) {
                // SELECT_VAR case
            } else if (type == SELECT_IMG) {
                // SELECT_IMG case
            } else if (type == SELECT_IMGS) {
                // SELECT_IMGS case
            } else if (type == WAIT) {
                // WAIT case
            } else if (type == WAIT_SE) {
                // WAIT_SE case
            } else if (type == RAND) {
                // RAND case
            } else if (type == BGM) {
                // BGM case
            } else if (type == BGM_STOP) {
                // BGM_STOP case
            } else if (type == SE) {
                // SE case
            } else if (type == SE_STOP) {
                // SE_STOP case
            } else if (type == VO) {
                // VO case
            } else if (type == LOAD) {
                // LOAD case
            } else if (type == ALBUM) {
                // ALBUM case
            } else if (type == MUSIC) {
                // MUSIC case
            } else if (type == DATE) {
                // DATE case
            } else if (type == CONFIG) {
                // CONFIG case
            } else {
                // Default case
                throw std::runtime_error("Unknown command type: " + std::to_string(type));
                // std::cerr << "Unknown command type: " << type << std::endl;
            }
        }

        // std::cout<<cmd->type()<<std::endl;
        return std::make_unique<cli::CliCommandExit>();
    }

    void Director::setFSEL(unsigned int choice) {
        environment->set(RESERVED_VAR_FSEL, std::to_string(choice));
    }

    const GameConfig &Director::getConfig() const {
        return environment->getConfig();
    }

    std::unique_ptr<sdl::SdlCommand> Director::nextSdlCommand() {
        // 返回一个cli绘图指令（待定义）。cli每次做的事情就是问director要一个绘图指令，再执行它。director负责goto、if、change、select等流程控制
        while (environment->curr_script_line_number < parser->getLineCount()) {
            std::unique_ptr<Command> cmd = parser->peek(environment->curr_script_line_number++);
            CommandType type = cmd->type();

            const std::unordered_set<CommandType> DIRECT_FORWARD_COMMANDS = {
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
                    // SEL, // sel的参数不完整，所以要交由Drector处理
                    SELECT_TEXT,
                    SELECT_VAR,
                    SELECT_IMG,
                    SELECT_IMGS,
                    WAIT,
                    WAIT_SE,
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

            if (DIRECT_FORWARD_COMMANDS.find(type) != DIRECT_FORWARD_COMMANDS.end()) {
                return createSdlCommand(cmd);
            }



            // 注意不是所有的分支都会被执行，在DIRECT_FORWARD_COMMANDS中的case是直接由createSdlCommand()处理的，下面对应的分支就不会执行了
            if (type == PLAIN_TEXT) {
                // BLANK case
            } else if (type == UNKNOWN) {
                // UNKNOWN case
            } else if (type == BROKEN) {
                // BROKEN case
            } else if (type == SAY) {
            } else if (type == TEXT) {
            } else if (type == TEXT_OFF) {
                // TEXT_OFF case
            } else if (type == WAITKEY) {
                // WAITKEY case
            } else if (type == TITLE) {
            } else if (type == TITLE_DSP) {
                // TITLE_DSP case
            } else if (type == CHARA) {
                // CHARA case
            } else if (type == CHARA_CLS) {
                // CHARA_CLS case
            } else if (type == CHARA_POS) {
                // CHARA_POS case
            } else if (type == BG) {
                // BG case
            } else if (type == FLASH) {
                // FLASH case
            } else if (type == QUAKE) {
                // QUAKE case
            } else if (type == FADE_OUT) {
                // FADE_OUT case
            } else if (type == FADE_IN) {
                // FADE_IN case
            } else if (type == MOVIE) {
                // MOVIE case
            } else if (type == TEXTBOX) {
                // TEXTBOX case
            } else if (type == CHARA_QUAKE) {
                // CHARA_QUAKE case
            } else if (type == CHARA_DOWN) {
                // CHARA_DOWN case
            } else if (type == CHARA_UP) {
                // CHARA_UP case
            } else if (type == SCROLL) {
                // SCROLL case
            } else if (type == CHARA_Y) {
                // CHARA_Y case
            } else if (type == CHARA_SCROLL) {
                // CHARA_SCROLL case
            } else if (type == ANIME_ON) {
                // ANIME_ON case
            } else if (type == ANIME_OFF) {
                // ANIME_OFF case
            } else if (type == CHARA_ANIME) {
                // CHARA_ANIME case
            } else if (type == SET) {
                auto targetCmd = dynamic_cast<CommandSet*>(cmd.get());
                environment->set(targetCmd->var_name, targetCmd->var_value);
            } else if (type == ADD) {
                auto targetCmd = dynamic_cast<CommandAdd*>(cmd.get());
                environment->add(targetCmd->var_name, targetCmd->add_value, false);
            } else if (type == SUB) {
                auto targetCmd = dynamic_cast<CommandAdd*>(cmd.get());
                environment->sub(targetCmd->var_name, targetCmd->add_value);
            } else if (type == LABEL) {
                // LABEL case
            } else if (type == GOTO) {
                // 跳转到当前脚本里指定的行标签
                auto targetCmd = dynamic_cast<CommandGoto*>(cmd.get());
                environment->curr_script_line_number = parser->findLabel(targetCmd->label_name);
            } else if (type == IF_GOTO) {
                bool flagIgnoreThisCommand = false; // 如果右操作数为变量且变量未被赋值过，系统会忽略这条 if 语句。

                auto targetCmd = dynamic_cast<CommandIfGoto*>(cmd.get());

                std::string left_operand = targetCmd->left_operand;
                CommandIfGoto::ComparisonType comparison_type = targetCmd->comparison_type;
                std::string right_operand = targetCmd->right_operand;

                // 检查左操作数是否存在，如果不存在，系统将其看作0来比较
                int left_value = 0;
                bool left_exists = environment->varExists(left_operand);
                if (left_exists) {
                    left_value = environment->getVar(left_operand);
                }

                int right_value = 0;
                // 如果右操作数是变量，则检查其是否存在
                if (isIdentifier(right_operand)) {
                    if (environment->varExists(right_operand)) {
                        right_value = environment->getVar(right_operand);
                    } else {
                        flagIgnoreThisCommand = true;
                    }
                } else {
                    right_value = std::stoi(right_operand);
                }

                if (!flagIgnoreThisCommand) {
                    // 根据比较类型执行相应的操作
                    bool condition_met = false;
                    switch (comparison_type) {
                        case CommandIfGoto::EQUAL:
                            condition_met = (left_value == right_value);
                            break;
                        case CommandIfGoto::GREATER_THAN:
                            condition_met = (left_value > right_value);
                            break;
                        case CommandIfGoto::LESS_THAN:
                            condition_met = (left_value < right_value);
                            break;
                        case CommandIfGoto::GREATER_THAN_OR_EQUAL:
                            condition_met = (left_value >= right_value);
                            break;
                        case CommandIfGoto::LESS_THAN_OR_EQUAL:
                            condition_met = (left_value <= right_value);
                            break;
                        case CommandIfGoto::NOT_EQUAL:
                            condition_met = (left_value != right_value);
                            break;
                        default:
                            // 处理未知的比较类型
                            break;
                    }

                    if (condition_met) {
                        // 跳转到指定的行（标签）
                        environment->curr_script_line_number = parser->findLabel(targetCmd->label_name);
                    }
                }

            } else if (type == CHANGE) {
                // 不带返回的脚本文件跳转。直接更换脚本文件
                auto targetCmd = dynamic_cast<CommandChange*>(cmd.get());
                environment->curr_script_name = targetCmd->filename;
                environment->curr_script_line_number = 0;
                parser = std::move(loadScript(root_path + PATH_DIR_SCRIPT + targetCmd->filename + CONFIG_SCRITP_SUFFIX));
            } else if (type == CALL) {
                // CALL case
                auto targetCmd = dynamic_cast<CommandCall*>(cmd.get());
                CallStackItem stackItem = CallStackItem{environment->curr_script_name, environment->curr_script_line_number};
                environment->pushCallStack(stackItem);
                environment->curr_script_name = targetCmd->filename;
                environment->curr_script_line_number = 0;
                parser = std::move(loadScript(root_path + PATH_DIR_SCRIPT + targetCmd->filename + CONFIG_SCRITP_SUFFIX));
            } else if (type == RET) {
                // RET case
                CallStackItem stackItem = environment->popCallStack();
                environment->curr_script_name = stackItem.script_name;
                environment->curr_script_line_number = stackItem.line_number;
                parser = std::move(loadScript(root_path + PATH_DIR_SCRIPT + environment->curr_script_name + CONFIG_SCRITP_SUFFIX));
            } else if (type == SEL) {
                // SEL case
//                #sel 2
//                我是选项一
//                我是选项二
//                #if FSEL=0, goto TEST_SELECTION_01
//                #if FSEL=1, goto TEST_SELECTION_02
//                #label TEST_SELECTION_01
//                #say 你选了选项一
//                #goto TEST_SELECTION_END
//                #label TEST_SELECTION_02
//                #say 你选了选项二
//                #goto TEST_SELECTION_END
//                #label TEST_SELECTION_END
//                #say 选择支结束，重回共通部分

                auto targetCmd = dynamic_cast<CommandSel*>(cmd.get());
                unsigned int choice_num = targetCmd->choiceNum;
                std::vector<std::string> choices;
                for (unsigned int i = 0; i < choice_num; i++) {
                    auto choice_line = parser->peek(environment->curr_script_line_number++);
                    if (choice_line->type() != PLAIN_TEXT) {
                        throw std::runtime_error("Expected PLAIN_TEXT line after #sel command");
                    }
                    std::string choice_text = dynamic_cast<CommandPlainText*>(choice_line.get())->command_literal;
                    choices.push_back(choice_text);
                }
                /*
                 * 根据绘图指令队列模型，platform读取绘图指令时读到 #sel 指令就会停下，待获得用户选择的结果后会调用 Director::setFSEL() 把结果交给Director后，才继续向Director要绘图指令
                 */
                auto res = std::make_unique<sdl::SdlCommandSel>();
                res->choiceTexts = choices;
                res->choiceNum = choice_num;
                res->hintPic = targetCmd->hintPic;
                return res;
            } else if (type == SELECT_TEXT) {
                // SELECT_TEXT case
            } else if (type == SELECT_VAR) {
                // SELECT_VAR case
            } else if (type == SELECT_IMG) {
                // SELECT_IMG case
            } else if (type == SELECT_IMGS) {
                // SELECT_IMGS case
            } else if (type == WAIT) {
                // WAIT case
            } else if (type == WAIT_SE) {
                // WAIT_SE case
            } else if (type == RAND) {
                // RAND case
            } else if (type == BGM) {
                // BGM case
            } else if (type == BGM_STOP) {
                // BGM_STOP case
            } else if (type == SE) {
                // SE case
            } else if (type == SE_STOP) {
                // SE_STOP case
            } else if (type == VO) {
                // VO case
            } else if (type == LOAD) {
                // LOAD case
            } else if (type == ALBUM) {
                // ALBUM case
            } else if (type == MUSIC) {
                // MUSIC case
            } else if (type == DATE) {
                // DATE case
            } else if (type == CONFIG) {
                // CONFIG case
            } else {
                // Default case
                throw std::runtime_error("Unknown command type: " + std::to_string(type));
                // std::cerr << "Unknown command type: " << type << std::endl;
            }
        }

        // std::cout<<cmd->type()<<std::endl;
        return std::make_unique<sdl::SdlCommandExit>();
    }


    std::unique_ptr<sdl::SdlCommand> createSdlCommand(std::unique_ptr<core::Command>& command) {
        switch (command->type()) {
            case core::SAY: {
                auto sayCommand = std::make_unique<sdl::SdlCommandSay>();
                auto coreSayCommand = dynamic_cast<core::CommandSay*>(command.get());
                sayCommand->name = coreSayCommand->name;
                sayCommand->flag_contains_name = coreSayCommand->flag_contains_name;
                sayCommand->content = coreSayCommand->content;
                return std::move(sayCommand);
            }
            case core::TEXT: {
                auto textCommand = std::make_unique<sdl::SdlCommandText>();
                auto coreTextCommand = dynamic_cast<core::CommandText*>(command.get());
                textCommand->content = coreTextCommand->content;
                textCommand->x1 = coreTextCommand->x1;
                textCommand->y1 = coreTextCommand->y1;
                textCommand->x2 = coreTextCommand->x2;
                textCommand->y2 = coreTextCommand->y2;
                textCommand->color = coreTextCommand->color;
                textCommand->size = coreTextCommand->size;
                textCommand->showImmediately = coreTextCommand->showImmediately;
                return std::move(textCommand);
            }
            case core::TEXT_OFF: {
                return std::make_unique<sdl::SdlCommandTextOff>();
            }
            case core::WAITKEY: {
                return std::make_unique<sdl::SdlCommandWaitKey>();
            }
            case core::TITLE: {
                auto titleCommand = std::make_unique<sdl::SdlCommandTitle>();
                auto coreTitleCommand = dynamic_cast<core::CommandTitle*>(command.get());
                titleCommand->content = coreTitleCommand->content;
                return std::move(titleCommand);
            }
            case core::TITLE_DSP: {
                return std::make_unique<sdl::SdlCommandTitleDsp>();
            }
            case core::CHARA: {
                auto charaCommand = std::make_unique<sdl::SdlCommandChara>();
                auto coreCharaCommand = dynamic_cast<core::CommandChara*>(command.get());

                for (const auto& coreCharaInfo : coreCharaCommand->charaInfos) {
                    // copy one by one
                    sdl::SdlCommandChara::CharaInfo sdlCharaInfo = {coreCharaInfo.charaID, coreCharaInfo.filename, coreCharaInfo.position, coreCharaInfo.layer};
                    charaCommand->charaInfos.push_back(sdlCharaInfo);
                }
                charaCommand->time = coreCharaCommand->time;

                return std::move(charaCommand);
            }
            case core::CHARA_CLS: {
                auto charaClsCommand = std::make_unique<sdl::SdlCommandCharaCls>();
                auto coreCharaClsCommand = dynamic_cast<core::CommandCharaCls*>(command.get());
                charaClsCommand->charaID = coreCharaClsCommand->charaID;
                charaClsCommand->time = coreCharaClsCommand->time;
                return std::move(charaClsCommand);
            }
            case core::CHARA_POS: {
                auto charaPosCommand = std::make_unique<sdl::SdlCommandCharaPos>();
                auto coreCharaPosCommand = dynamic_cast<core::CommandCharaPos*>(command.get());
                charaPosCommand->charaID = coreCharaPosCommand->charaID;
                charaPosCommand->new_x = coreCharaPosCommand->new_x;
                charaPosCommand->new_y = coreCharaPosCommand->new_y;
                charaPosCommand->coord_mode = coreCharaPosCommand->coord_mode;
                return std::move(charaPosCommand);
            }
            case core::BG: {
                auto bgCommand = std::make_unique<sdl::SdlCommandBg>();
                auto coreBgCommand = dynamic_cast<core::CommandBg*>(command.get());
                bgCommand->filename = coreBgCommand->filename;
                bgCommand->transition = coreBgCommand->transition;
                bgCommand->time = coreBgCommand->time;
                bgCommand->x = coreBgCommand->x;
                bgCommand->y = coreBgCommand->y;
                return std::move(bgCommand);
            }
            case core::FLASH: {
                auto flashCommand = std::make_unique<sdl::SdlCommandFlash>();
                auto coreFlashCommand = dynamic_cast<core::CommandFlash*>(command.get());
                flashCommand->color = coreFlashCommand->color;
                flashCommand->time = coreFlashCommand->time;
                return std::move(flashCommand);
            }
            case core::QUAKE: {
                return std::make_unique<sdl::SdlCommandQuake>();
            }
            case core::FADE_OUT: {
                auto fadeOutCommand = std::make_unique<sdl::SdlCommandFadeOut>();
                auto coreFadeOutCommand = dynamic_cast<core::CommandFadeOut*>(command.get());
                fadeOutCommand->color = coreFadeOutCommand->color;
                fadeOutCommand->time = coreFadeOutCommand->time;
                return std::move(fadeOutCommand);
            }
            case core::FADE_IN: {
                auto fadeInCommand = std::make_unique<sdl::SdlCommandFadeIn>();
                auto coreFadeInCommand = dynamic_cast<core::CommandFadeIn*>(command.get());
                fadeInCommand->time = coreFadeInCommand->time;
                return std::move(fadeInCommand);
            }
            case core::MOVIE: {
                auto movieCommand = std::make_unique<sdl::SdlCommandMovie>();
                auto coreMovieCommand = dynamic_cast<core::CommandMovie*>(command.get());
                movieCommand->filename = coreMovieCommand->filename;
                return std::move(movieCommand);
            }
            case core::TEXTBOX: {
                auto textBoxCommand = std::make_unique<sdl::SdlCommandTextBox>();
                auto coreTextBoxCommand = dynamic_cast<core::CommandTextBox*>(command.get());
                textBoxCommand->messageFilename = coreTextBoxCommand->messageFilename;
                textBoxCommand->nameFilename = coreTextBoxCommand->nameFilename;
                return std::move(textBoxCommand);
            }
            case core::CHARA_QUAKE: {
                auto charaQuakeCommand = std::make_unique<sdl::SdlCommandCharaQuake>();
                auto coreCharaQuakeCommand = dynamic_cast<core::CommandCharaQuake*>(command.get());
                charaQuakeCommand->charaIDs = coreCharaQuakeCommand->charaIDs;
                return std::move(charaQuakeCommand);
            }
            case core::CHARA_DOWN: {
                auto charaDownCommand = std::make_unique<sdl::SdlCommandCharaDown>();
                auto coreCharaDownCommand = dynamic_cast<core::CommandCharaDown*>(command.get());
                charaDownCommand->charaIDs = coreCharaDownCommand->charaIDs;
                return std::move(charaDownCommand);
            }
            case core::CHARA_UP: {
                auto charaUpCommand = std::make_unique<sdl::SdlCommandCharaUp>();
                auto coreCharaUpCommand = dynamic_cast<core::CommandCharaUp*>(command.get());
                charaUpCommand->charaIDs = coreCharaUpCommand->charaIDs;
                return std::move(charaUpCommand);
            }
            case core::SCROLL: {
                auto scrollCommand = std::make_unique<sdl::SdlCommandScroll>();
                auto coreScrollCommand = dynamic_cast<core::CommandScroll*>(command.get());
                scrollCommand->startx = coreScrollCommand->startx;
                scrollCommand->starty = coreScrollCommand->starty;
                scrollCommand->endx = coreScrollCommand->endx;
                scrollCommand->endy = coreScrollCommand->endy;
                scrollCommand->time = coreScrollCommand->time;
                return std::move(scrollCommand);
            }
            case core::CHARA_Y: {
                auto charaYCommand = std::make_unique<sdl::SdlCommandCharaY>();
                auto coreCharaYCommand = dynamic_cast<core::CommandCharaY*>(command.get());
                charaYCommand->coordMode = coreCharaYCommand->coordMode;
                charaYCommand->charaList = coreCharaYCommand->charaList;
                charaYCommand->time = coreCharaYCommand->time;
                return charaYCommand;
            }
            case core::CHARA_SCROLL: {
                auto charaScrollCommand = std::make_unique<sdl::SdlCommandCharaScroll>();
                auto coreCharaScrollCommand = dynamic_cast<core::CommandCharaScroll*>(command.get());
                charaScrollCommand->coordMode = coreCharaScrollCommand->coordMode;
                charaScrollCommand->charaID = coreCharaScrollCommand->charaID;
                charaScrollCommand->filename = coreCharaScrollCommand->filename;
                charaScrollCommand->startx = coreCharaScrollCommand->startx;
                charaScrollCommand->starty = coreCharaScrollCommand->starty;
                charaScrollCommand->endx = coreCharaScrollCommand->endx;
                charaScrollCommand->endy = coreCharaScrollCommand->endy;
                charaScrollCommand->beginalpha = coreCharaScrollCommand->beginalpha;
                charaScrollCommand->layer = coreCharaScrollCommand->layer;
                charaScrollCommand->time = coreCharaScrollCommand->time;
                return charaScrollCommand;
            }
            case core::ANIME_ON: {
                auto animeOnCommand = std::make_unique<sdl::SdlCommandAnimeOn>();
                auto coreAnimeOnCommand = dynamic_cast<core::CommandAnimeOn*>(command.get());
                animeOnCommand->num = coreAnimeOnCommand->num;
                animeOnCommand->filename = coreAnimeOnCommand->filename;
                animeOnCommand->x = coreAnimeOnCommand->x;
                animeOnCommand->y = coreAnimeOnCommand->y;
                animeOnCommand->interval = coreAnimeOnCommand->interval;
                animeOnCommand->isloop = coreAnimeOnCommand->isloop;
                return animeOnCommand;
            }
            case core::ANIME_OFF: {
                auto animeOffCommand = std::make_unique<sdl::SdlCommandAnimeOff>();
                auto coreAnimeOffCommand = dynamic_cast<core::CommandAnimeOff*>(command.get());
                animeOffCommand->filename = coreAnimeOffCommand->filename;
                return animeOffCommand;
            }
            case core::CHARA_ANIME: {
                auto charaAnimeCommand = std::make_unique<sdl::SdlCommandCharaAnime>();
                auto coreCharaAnimeCommand = dynamic_cast<core::CommandCharaAnime*>(command.get());
                charaAnimeCommand->charaID = coreCharaAnimeCommand->charaID;
                charaAnimeCommand->period = coreCharaAnimeCommand->period;
                charaAnimeCommand->loop_num = coreCharaAnimeCommand->loop_num;
                charaAnimeCommand->offsets = coreCharaAnimeCommand->offsets;
                return charaAnimeCommand;
            }
            case core::SELECT_TEXT: {
                auto selectTextCommand = std::make_unique<sdl::SdlCommandSelectText>();
                auto coreSelectTextCommand = dynamic_cast<core::CommandSelectText*>(command.get());
                selectTextCommand->choiceNum = coreSelectTextCommand->choiceNum;
                selectTextCommand->choiceTexts = coreSelectTextCommand->choiceTexts;
                selectTextCommand->x1 = coreSelectTextCommand->x1;
                selectTextCommand->y1 = coreSelectTextCommand->y1;
                selectTextCommand->x2 = coreSelectTextCommand->x2;
                selectTextCommand->y2 = coreSelectTextCommand->y2;
                selectTextCommand->color = coreSelectTextCommand->color;
                selectTextCommand->initPosition = coreSelectTextCommand->initPosition;
                return selectTextCommand;
            }
            case core::SELECT_VAR: {
                auto selectVarCommand = std::make_unique<sdl::SdlCommandSelectVar>();
                auto coreSelectVarCommand = dynamic_cast<core::CommandSelectVar*>(command.get());
                selectVarCommand->choiceNum = coreSelectVarCommand->choiceNum;
                selectVarCommand->choices = coreSelectVarCommand->choices;
                selectVarCommand->vars = coreSelectVarCommand->vars;
                selectVarCommand->x1 = coreSelectVarCommand->x1;
                selectVarCommand->y1 = coreSelectVarCommand->y1;
                selectVarCommand->x2 = coreSelectVarCommand->x2;
                selectVarCommand->y2 = coreSelectVarCommand->y2;
                selectVarCommand->color = coreSelectVarCommand->color;
                selectVarCommand->initPosition = coreSelectVarCommand->initPosition;
                return std::move(selectVarCommand);
            }
            case core::SELECT_IMG: {
                auto selectImgCommand = std::make_unique<sdl::SdlCommandSelectImg>();
                auto coreSelectImgCommand = dynamic_cast<core::CommandSelectImg*>(command.get());
                selectImgCommand->choiceNum = coreSelectImgCommand->choiceNum;
                selectImgCommand->filename = coreSelectImgCommand->filename;
                selectImgCommand->xCoordinates = coreSelectImgCommand->xCoordinates;
                selectImgCommand->yCoordinates = coreSelectImgCommand->yCoordinates;
                selectImgCommand->variables = coreSelectImgCommand->variables;
                selectImgCommand->initPosition = coreSelectImgCommand->initPosition;
                return std::move(selectImgCommand);
            }
            case core::SELECT_IMGS: {
                auto selectImgsCommand = std::make_unique<sdl::SdlCommandSelectImgs>();
                auto coreSelectImgsCommand = dynamic_cast<core::CommandSelectImgs*>(command.get());
                selectImgsCommand->choiceNum = coreSelectImgsCommand->choiceNum;
                selectImgsCommand->filenames = coreSelectImgsCommand->filenames;
                selectImgsCommand->xCoords = coreSelectImgsCommand->xCoords;
                selectImgsCommand->yCoords = coreSelectImgsCommand->yCoords;
                selectImgsCommand->vars = coreSelectImgsCommand->vars;
                selectImgsCommand->initPosition = coreSelectImgsCommand->initPosition;
                return std::move(selectImgsCommand);
            }
            case core::WAIT: {
                auto waitCommand = std::make_unique<sdl::SdlCommandWait>();
                auto coreWaitCommand = dynamic_cast<core::CommandWait*>(command.get());
                waitCommand->time = coreWaitCommand->time;
                return std::move(waitCommand);
            }
            case core::WAIT_SE: {
                auto waitSeCommand = std::make_unique<sdl::SdlCommandWaitSe>();
                return std::move(waitSeCommand);
            }
            case core::BGM: {
                auto bgmCommand = std::make_unique<sdl::SdlCommandBgm>();
                auto coreBgmCommand = dynamic_cast<core::CommandBgm*>(command.get());
                bgmCommand->filename = coreBgmCommand->filename;
                bgmCommand->isLoop = coreBgmCommand->isLoop;
                return std::move(bgmCommand);
            }
            case core::BGM_STOP: {
                auto bgmStopCommand = std::make_unique<sdl::SdlCommandBgmStop>();
                return std::move(bgmStopCommand);
            }
            case core::SE: {
                auto seCommand = std::make_unique<sdl::SdlCommandSe>();
                auto coreSeCommand = dynamic_cast<core::CommandSe*>(command.get());
                seCommand->filename = coreSeCommand->filename;
                seCommand->isLoop = coreSeCommand->isLoop;
                return std::move(seCommand);
            }
            case core::SE_STOP: {
                auto seStopCommand = std::make_unique<sdl::SdlCommandSeStop>();
                return std::move(seStopCommand);
            }
            case core::VO: {
                auto voCommand = std::make_unique<sdl::SdlCommandVo>();
                auto coreVoCommand = dynamic_cast<core::CommandVo*>(command.get());
                voCommand->filename = coreVoCommand->filename;
                return std::move(voCommand);
            }
            case core::LOAD: {
                auto loadCommand = std::make_unique<sdl::SdlCommandLoad>();
                auto coreLoadCommand = dynamic_cast<core::CommandLoad*>(command.get());
                loadCommand->saveNum = coreLoadCommand->saveNum;
                return std::move(loadCommand);
            }
            case core::ALBUM: {
                auto albumCommand = std::make_unique<sdl::SdlCommandAlbum>();
                auto coreAlbumCommand = dynamic_cast<core::CommandAlbum*>(command.get());
                albumCommand->albumListFilename = coreAlbumCommand->albumListFilename;
                return std::move(albumCommand);
            }
            case core::MUSIC: {
                auto musicCommand = std::make_unique<sdl::SdlCommandMusic>();
                return std::move(musicCommand);
            }
            case core::DATE: {
                auto dateCommand = std::make_unique<sdl::SdlCommandDate>();
                auto coreDateCommand = dynamic_cast<core::CommandDate*>(command.get());
                dateCommand->dateBg = coreDateCommand->dateBg;
                dateCommand->x = coreDateCommand->x;
                dateCommand->y = coreDateCommand->y;
                dateCommand->color = coreDateCommand->color;
                return std::move(dateCommand);
            }
            case core::CONFIG: {
                auto configCommand = std::make_unique<sdl::SdlCommandConfig>();
                return std::move(configCommand);
            }
            default:
                throw std::runtime_error("Unrecognized command type: " + std::to_string(command->type()));
        }
    }

} // core