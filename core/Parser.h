//
// Created by KBZ on 2024/4/28.
//

#include <string>
#include <vector>
#include <sstream>
#include "Command.h"

#ifndef LIGHTSONG_PARSER_H
#define LIGHTSONG_PARSER_H

#include "memory"

namespace core {

    class Parser;

    std::unique_ptr<Parser> loadScript(const std::string& script_path);

    class Parser {
    private:
        std::string source;
        std::vector<std::string> lines;
        unsigned int currLineNumber;
    public:
        explicit Parser(std::string source);
        std::unique_ptr<Command> peek(unsigned int line_number);
        std::unique_ptr<Command> next();
        bool setCurrLineNumber(unsigned int line_number);
        unsigned int getCurrLineNumber();
        unsigned int getLineCount();
        bool isEnd();
        /*
        // bool jump(std::string& label);
         不要在这里定义一个jump函数。interpreter在读到jump指令的时候再一行一行地用peek，找到行号后用setLineNumber就可以啦。
         优化的时候可以加个哈希表
         */

    };

} // core

#endif //LIGHTSONG_PARSER_H
