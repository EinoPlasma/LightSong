//
// Created by KBZ on 2024/4/28.
//

#include "Parser.h"
#include "../utils.h"

namespace core {
    Parser::Parser(std::string source) : source(std::move(source)), currLineNumber(0){
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
        // TODO: 在遇到语句"#if F58=2, goto TEST_LABEL_002"的时候分割错误，没有把正确的params传给上级。在其他那种不只有一个空格的语句也会有这个问题。
        std::string& line = lines[line_number];
        std::stringstream ss, ss_params;
        ss << line;
        std::string type_literal;
        std::string params_literal;
        ss >> type_literal;
        ss >> params_literal;
//
//        // Read the remaining contents of ss into params_literal
//        std::getline(ss, params_literal);
//        params_literal = params_literal.substr(params_literal.find_first_not_of(' '));

        ss_params << params_literal;

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
        while (std::getline(ss_params, param, ',')) {
            params.push_back(param);
        }
        return createCommand(type, params);
    }



    bool Parser::setCurrLineNumber(unsigned int line_number) {
        if(line_number > this->currLineNumber){
            return false;
        }
        this->currLineNumber = line_number;
        return true;
    }

    std::unique_ptr<Command> Parser::next() {
        if (currLineNumber >= lines.size()) {
            raise(-1);
            // reach to the end of file. the right response here is to panic, though program should exit when reach to EOF, but decide whenever to exit is the director's role.
        }
        this->currLineNumber++;
        return peek(currLineNumber - 1);
    }

    bool Parser::isEnd() {
        return currLineNumber >= lines.size();
    }

    unsigned int Parser::getCurrLineNumber() {
        return currLineNumber;
    }

    unsigned int Parser::getLineCount() {
        return lines.size();
    }

    std::unique_ptr<Parser> loadScript(const std::string &script_path) {
        std::string source = readUtf8File(script_path);
        return std::make_unique<Parser>(std::move(source));
    }
} // core