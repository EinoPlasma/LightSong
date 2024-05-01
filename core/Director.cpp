//
// Created by KBZ on 2024/4/28.
//
#include "iostream"
#include "Director.h"
#include "GameConfig.h"
#include "EnginePath.h"
#include "Command.h"

#include "../platform/cli/CliCommand.h"
#include "../utils.h"

namespace core {
    Director::Director(std::basic_string<char> root_path): root_path(root_path) {
        config = loadGameConfig(root_path + PATH_FILE_GAMECONFIG);
        parser = loadScript(root_path + PATH_DIR_SCRIPT + SCRIPT_NAME_START + CONFIG_SCRITP_SUFFIX);

        environment = std::make_unique<Environment>();
        environment->curr_script_name = SCRIPT_NAME_START;
        environment->curr_script_line_number = 0;
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


} // core