//
// Created by KBZ on 2024/4/28.
//

#include "Parser.h"
#include "../utils.h"

namespace core {
    Parser::Parser(std::string source) : source(std::move(source)){
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
            // if (!line.empty() && line[0] == '#') {
            //     lines.push_back(line);
            // }

            lines.push_back(line);
        }

        // make labelMap
        /*
         * 逆天bug：原来的代码在普通编译时没问题，调试时就在“if (labelMap.find(cmd_label->label_name) != labelMap.end())”这句话segment fault，解决的方法是把原来做了两遍peek(i)换成一遍（存在变量cmd中），就nm解决了
         * 逆天bug成因：因为Command里面的字符串都是`字符串引用`，两次peek(i)创建的是不同的对象，但只有第一次peek(i)拿到了从parser.source来的那部分字符串切片的所有权，第二次peek(i)就拿不到了
         * （除非把第一次的peek(i)生成打那个unique_ptr<Command>销毁，这时这段字符串切片的所有权就会还回去，才能让第二次peek(i)拿到所有权）
         * 也可能是是第二次peek(i)的时候字符串已经被unique_ptr销毁掉了，得做实验看看
         */
        for(int i=0; i < lines.size(); i++){
            auto cmd = peek(i);
            if (cmd->type() == LABEL) {
                auto cmd_label = dynamic_cast<CommandLabel*>(cmd.get());
                if (labelMap.find(cmd_label->label_name) != labelMap.end()) {
                    std::cerr << "Label " << cmd_label->label_name << " has been defined multiple times." << std::endl;
                    // throw std::runtime_error("label has been defined multiple times.");
                }
                labelMap[cmd_label->label_name] = i;
            }
        }
        // 下面是有上述bug的版本
//        for(int i=0; i < lines.size(); i++){
//            if (peek(i)->type() == LABEL) {
//                auto cmd_label = dynamic_cast<CommandLabel*>(peek(i).get());
//                if (labelMap.find(cmd_label->label_name) != labelMap.end()) {
//                    throw std::runtime_error("label has been defined multiple times.");
//                }
//                labelMap[cmd_label->label_name] = i;
//            }
//        }


    }

    std::unique_ptr<Command> Parser::peek(unsigned int line_number) {
        std::string& line = lines[line_number];
        if (line.empty() || line[0] != '#') {
            // return BLANK if the line is empty or not a command
            return createCommand(PLAIN_TEXT, std::vector<std::string>({line}));
        }

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

    unsigned int Parser::getLineCount() {
        return lines.size();
    }

    unsigned int Parser::findLabel(const std::string &targetLabel) {
        if (labelMap.find(targetLabel) != labelMap.end()) {
            return labelMap[targetLabel];
        }
        throw std::runtime_error("Label not found");
    }



//    void Parser::setCurrLineNumber(unsigned int line_number) {
//        if(line_number > this->getLineCount()){
//            throw std::runtime_error("invalid line number");
//        }
//        this->currLineNumber = line_number;
//    }
//
//    std::unique_ptr<Command> Parser::next() {
//        if (currLineNumber >= lines.size()) {
//            raise(-1);
//            // reach to the end of file. the right response here is to panic, though program should exit when reach to EOF, but decide whenever to exit is the director's role.
//        }
//        this->currLineNumber++;
//        return peek(currLineNumber - 1);
//    }
//
//    bool Parser::isEnd() {
//        return currLineNumber >= lines.size();
//    }
//
//    unsigned int Parser::getCurrLineNumber() {
//        return currLineNumber;
//    }
//
//
//
//    void Parser::jumpToLabel(const std::string& targetLabel) {
//        // 跳转到当前脚本里指定的行标签
//        if (labelMap.find(targetLabel) != labelMap.end()) {
//            setCurrLineNumber(labelMap[targetLabel]);
//            return;
//        }
//        throw std::invalid_argument("goto a invalid label");
////        std::cout << "Jump to label: "<<targetLabel<<currLineNumber<<std::endl;
////        bool flagFoundLabel = false;
////        for (unsigned int i = 0; i < lines.size(); i++) {
////            if (lines[i].find("#label " + targetLabel) == 0) {
////                setCurrLineNumber(i);
////                flagFoundLabel = true;
////                break;
////            }
////        }
////        std::cout << "Jump to label: "<<targetLabel<<currLineNumber<<flagFoundLabel<<std::endl;
////        if (!flagFoundLabel){
////            throw std::invalid_argument("goto a invalid label");
////        }
//
////        bool flagFoundLabel = false;
////        for(int i=0; i < lines.size(); i++){
////            if (peek(i)->type() == LABEL) {
////                auto cmd_label = dynamic_cast<CommandLabel*>(peek(i).get());
////                if (cmd_label->label_name == targetLabel) {
////                    setCurrLineNumber(i);
////                    flagFoundLabel = true;
////                }
////            }
////        }
////        if (!flagFoundLabel){
////            throw std::invalid_argument("goto a invalid label");
////        }
//    }

    std::unique_ptr<Parser> loadScript(const std::string &script_path) {
        std::string source = readUtf8File(script_path);
        return std::make_unique<Parser>(std::move(source));
    }
} // core