//
// Created by EinoPlasma on 2024/4/30.
//

#include "Environment.h"
#include <string>
#include <random>
#include "../utils.h"
#include "iostream"

#include "../include/nlohmann/json.hpp"
using json = nlohmann::json;

namespace core {
    void Environment::set(const std::string &var_name, const std::string &var_value) {
        if (!isIdentifier(var_value)) {
            variables[var_name] = std::stoi(var_value);
        }else{
            if (variables.find(var_value) != variables.end()){
                variables[var_name] = variables[var_value];
            } else {
                variables[var_name] = 0;
                throw std::runtime_error("Set a invalid var");
            }
        }
    }

    void Environment::add(const std::string& var_name, const std::string& value, bool flagSub) {
        int multiplier = 1;
        if (flagSub) {
            multiplier = -1;
        }

        if (variables.find(var_name) != variables.end()){
            // 如果加上的变量之前从未被赋值，系统会不执行加法。
            if (!isIdentifier(var_name)) {
                variables[var_name] += multiplier * std::stoi(value);
            }else{
                if (variables.find(value) != variables.end()){
                    variables[var_name] += multiplier * variables[value];
                } else {
                    throw std::runtime_error("Add a invalid var");
                }
            }
        } else {
            throw std::runtime_error("Add a invalid var");
        }
    }

    void Environment::sub(const std::string& var_name, const std::string& value) {
        add(var_name, value, true);
    }

    void Environment::rand(const std::string &var_name, unsigned int min_value, unsigned int max_value) {
        if (min_value > max_value) {
            throw std::runtime_error("Invalid rand range");
        }
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<unsigned int> dist(min_value, max_value);
        unsigned int rand_var = dist(gen);
        variables[var_name] = rand_var;
    }

    int Environment::getVar(const std::string &var_name) {
        return variables[var_name];
    }

    void Environment::pushCallStack(CallStackItem item) {
        call_stack.push(std::move(item));
    }

    CallStackItem Environment::popCallStack() {
        if (call_stack.empty()) {
            throw std::runtime_error("Pop a empty CallStack");
        }
        CallStackItem res = call_stack.top();
        call_stack.pop();
        return res;
    }


    bool Environment::varExists(const std::string &var_name) {
        if (variables.find(var_name) != variables.end()) {
            return true;
        }
        return false;
    }

    const GameConfig &Environment::getConfig() const {
        return *config;
    }

    Environment::Environment(const std::string &config_path) {
        config = loadGameConfig(config_path);
    }


//    void Environment::loadSave(const std::string& savePath) {
//    }
//
//    void Environment::writeSave(const std::string &savePath) {
//        //        std::unordered_map<std::string, int> variables;
//        //        std::stack<CallStackItem> call_stack;
//        //        std::string  curr_script_name;
//        //        unsigned int curr_script_line_number;
//        //struct CallStackItem {
//        //        std::string script_name; // 脚本文件名，**不加扩展名，不带前面的路径**， 例如“script_01”
//        //        unsigned int line_number; // This line_number is the `currLineNumber` defined in Parser, not the number of lines in the script source file.
//        //    };
//        // serialize
//
//        std::ofstream saveFile(savePath, std::ios::binary);
//        if (saveFile.is_open()) {
//            // 序列化 curr_script_name 和 curr_script_line_number
//            int currScriptNameLength = curr_script_name.size() + 1; // 包括空字符
//            saveFile.write(reinterpret_cast<const char*>(&currScriptNameLength), sizeof(int)); // 写入脚本名长度
//            saveFile.write(curr_script_name.c_str(), currScriptNameLength); // 写入脚本名
//            saveFile.write(reinterpret_cast<const char*>(&curr_script_line_number), sizeof(unsigned int)); // 写入行号
//
//            // 序列化 variables
//            int numVariables = variables.size();
//            saveFile.write(reinterpret_cast<const char*>(&numVariables), sizeof(int));
//            for (const auto& variable : variables) {
//                saveFile.write(variable.first.c_str(), variable.first.size() + 1); // 写入变量名
//                saveFile.write(reinterpret_cast<const char*>(&variable.second), sizeof(int)); // 写入变量值
//            }
//
//            // 序列化 call_stack
//            int numCallStackItems = call_stack.size();
//            saveFile.write(reinterpret_cast<const char*>(&numCallStackItems), sizeof(int));
//            std::stack<CallStackItem> call_stack_copy = call_stack; // 创建临时副本
//            while (!call_stack_copy.empty()) {
//                CallStackItem item = call_stack_copy.top();
//                // 写入 CallStackItem 的数据到文件
//                int scriptNameLength = item.script_name.size() + 1; // 包括空字符
//                saveFile.write(reinterpret_cast<const char*>(&scriptNameLength), sizeof(int)); // 写入脚本名长度
//                saveFile.write(item.script_name.c_str(), scriptNameLength); // 写入脚本名
//                saveFile.write(reinterpret_cast<const char*>(&item.line_number), sizeof(unsigned int)); // 写入行号
//
//                call_stack_copy.pop();
//            }
//
//            saveFile.close();
//            std::cout << "Save file created successfully.\n";
//        } else {
//            std::cout << "Failed to create save file.\n";
//        }
//    }


    void Environment::loadSave(const std::string& savePath) {
        std::ifstream file(savePath);
        if (file.is_open()) {
            json data;
            file >> data;
            file.close();

            // Deserialize data
            variables = data["variables"].get<std::unordered_map<std::string, int>>();
            curr_script_name = data["curr_script_name"].get<std::string>();
            curr_script_line_number = data["curr_script_line_number"].get<unsigned int>();

            // Deserialize call stack
            call_stack = std::stack<CallStackItem>();
            for (const auto& item : data["call_stack"]) {
                CallStackItem callItem;
                callItem.script_name = item["script_name"].get<std::string>();
                callItem.line_number = item["line_number"].get<unsigned int>();
                call_stack.push(callItem);
            }

            std::cout << "Save loaded successfully." << std::endl;
        } else {
            std::cout << "Failed to load save." << std::endl;
        }
    }

    void Environment::writeSave(const std::string& savePath) {
        json data;

        // Serialize data
        data["variables"] = variables;
        data["curr_script_name"] = curr_script_name;
        data["curr_script_line_number"] = curr_script_line_number;

        // Serialize call stack
        json callStackData;
        while (!call_stack.empty()) {
            CallStackItem callItem = call_stack.top();
            call_stack.pop();
            json item;
            item["script_name"] = callItem.script_name;
            item["line_number"] = callItem.line_number;
            callStackData.push_back(item);
        }
        data["call_stack"] = callStackData;

        std::ofstream file(savePath);
        if (file.is_open()) {
            file << data;
            file.close();
            std::cout << "Save written successfully." << std::endl;
        } else {
            std::cout << "Failed to write save." << std::endl;
        }
    }


} // core