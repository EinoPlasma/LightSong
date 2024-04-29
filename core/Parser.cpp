//
// Created by KBZ on 2024/4/28.
//

#include "Parser.h"
#include "../utils.h"

namespace core {
    Parser::Parser(std::string source) : source(std::move(source)), line_number(0){
        /*
         * @brief split source by line
         *
         * split source by line and discard non-Command lines then push them to lines.
         */
        std::istringstream iss(this->source);
        std::string line;
        while (std::getline(iss, line)) {
            // trim the very last char if it is '\r' or '\n'
            if (!line.empty() && (line[line.length() - 1] == '\r' || line[line.length() - 1] == '\n')) {
                line = line.substr(0, line.length() - 1);
            }

            // discard the lines that do not start with '#'
            if (!line.empty() && line[0] == '#') {
                lines.push_back(line);
            }
        }
    }

    std::unique_ptr<Command> Parser::peek(unsigned int line_number) {
        std::string& line = lines[line_number];
        std::stringstream ss;
        ss << line;
        std::string type_literal;
        ss >> type_literal;

        CommandType type = UNKNOWN;
        auto it = command_type_map.find(type_literal);
        if (it == command_type_map.end()) {
            return createCommand(type, std::vector<std::string>());
        }
        // type = it->second;
        // type = command_type_map[type_literal]; /* error: since command_type_map is a const unordered_map, it does not support [] operator.
        type = command_type_map.at(type_literal); /* it's okay to write like this*/

        std::vector<std::string> params;
        std::string param;
        while (std::getline(ss, param, ',')) {
            params.push_back(param);
        }
        return createCommand(type, params);
    }



    bool Parser::setLineNumber(unsigned int line_number) {
        if(line_number > this->line_number){
            return false;
        }
        this->line_number = line_number;
        return true;
    }

    std::unique_ptr<Command> Parser::next() {
        if (line_number >= lines.size()) {
            raise(-1);
            // reach to the end of file. the right response here is to panic, though program should exit when reach to EOF, but decide whenever to exit is the director's role.
        }
        this->line_number++;
        return peek(line_number - 1);
    }

    bool Parser::isEnd() {
        return line_number >= lines.size();
    }

    std::unique_ptr<Parser> loadScript(const std::string &script_path) {
        std::string source = readUtf8File(script_path);
        return std::make_unique<Parser>(std::move(source));
    }
} // core