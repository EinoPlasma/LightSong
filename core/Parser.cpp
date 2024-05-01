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
        std::string& line = lines[line_number];
        std::stringstream ss(line);
        std::string type_literal;
        std::string params_literal;

        ss >> type_literal;
        std::getline(ss, params_literal);
        if (params_literal.find_first_not_of(' ') != -1){
            // 如果有空格就把空格跳掉
            params_literal = params_literal.substr(params_literal.find_first_not_of(' '));
        }

        CommandType type = UNKNOWN;
        auto it = command_type_map.find(type_literal);
        if (it != command_type_map.end()) {
            type = it->second;
        }

        std::vector<std::string> params;
        std::stringstream ss_params(params_literal);
        std::string param;
        while (std::getline(ss_params, param, ',')) {
            params.push_back(param);
        }

        std::unique_ptr<Command> res;
        try {
            res = createCommand(type, params);
        } catch (const std::invalid_argument& e) {
            // TODO: 错误处理
            std::cerr << "Exception occurred: BROKEN Command: " << e.what() << std::endl;
            res = createCommand(BROKEN, std::vector<std::string>());
        }
        return res;
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