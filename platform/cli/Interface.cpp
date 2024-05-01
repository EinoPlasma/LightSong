//
// Created by KBZ on 2024/4/29.
//

#include "Interface.h"
#include "iostream"
#include "memory"

namespace cli {
    void Interface::echo(std::string &str) {
        std::cout << str << std::endl;
    }

    std::string Interface::input(std::string &prompt) {
        std::cout << prompt;
        std::string intput_str;
        std::cin >> intput_str;
        return intput_str;
    }

    Interface::Interface(const char *root_path) {
        director = std::make_unique<core::Director>(root_path);
    }

    void Interface::tick(double dt) {
        std::unique_ptr<CliCommand> cli_command = director->nextCliCommand();
        CliCommandType type = cli_command->type();

        // std::cout << type << std::endl;
        if (type == EXIT) {
            std::cout << "game end";
            exit(0);
        } else if (type == ECHO) {
            auto echo_cmd = dynamic_cast<CliCommandEcho*>(cli_command.get());
            echo(echo_cmd->str);
        } else if (type == INPUT) {
            auto input_cmd = dynamic_cast<CliCommandInput*>(cli_command.get());
            std::string input_res = input(input_cmd->prompt);
            std::cout << "inputted: " << input_res << std::endl;
        } else if (type == SEL) {
            auto targetCmd = dynamic_cast<CliCommandSel*>(cli_command.get());
            std::string prompt = "select: ";
            // add selections to prompt
            for (int i = 0; i < targetCmd->options.size(); ++i) {
                prompt += std::to_string(i) + ":" + targetCmd->options[i] + " ";
            }
            std::string input_res = input(prompt);
            std::cout << "inputted: " << input_res << std::endl;
            director->setFSEL(std::stoi(input_res));
        }
    }


} // cli