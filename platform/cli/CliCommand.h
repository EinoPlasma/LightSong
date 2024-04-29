//
// Created by KBZ on 2024/4/29.
//

#ifndef LIGHTSONG_CLICOMMAND_H
#define LIGHTSONG_CLICOMMAND_H

#include <string>
#include <utility>

namespace cli {

    enum CliCommandType {
        EXIT, // 结束整个程序
        ECHO,
        INPUT,
    };

    class CliCommand {
    public:
        virtual CliCommandType type() = 0;
    };

    class CliCommandExit : public CliCommand {
    public:
        CliCommandType type() override { return EXIT; }
    };

    class CliCommandEcho : public CliCommand {
    public:
        CliCommandType type() override { return ECHO; }
        std::string str;
        explicit CliCommandEcho(std::string str): str(std::move(str)) { }; // 这里应该设计为传入一个string，而不是string的引用。因为上级会用到这个command，所以我们设计的command结构体应该确保所需的string存在。
    };

    class CliCommandInput : public CliCommand {
    public:
        CliCommandType type() override { return INPUT; }
        std::string prompt;
        explicit CliCommandInput(std::string prompt): prompt(std::move(prompt)) { };
    };

} // cli

#endif //LIGHTSONG_CLICOMMAND_H
