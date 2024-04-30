//
// Created by EinoPlasma on 2024/4/30.
//

#include "Environment.h"
#include <string>
#include <random>
#include "../utils.h"
#include "iostream"

namespace core {
    void Environment::set(const std::string &var_name, const std::string &var_value) {
        if (!isIdentifier(var_name)) {
            variables[var_name] = std::stoi(var_value);
        }else{
            if (variables.find(var_value) != variables.end()){
                variables[var_name] = variables[var_value];
            } else {
                variables[var_name] = 0;
                raise(-1);
                std::cerr<<"Warning: set a invalid var"<<std::endl;
                // TODO: 错误处理
            }
        }
    }

    void Environment::add(const std::string& var_name, const std::string& value, bool flagSub) {
        int multi = 1;
        if (flagSub) {
            multi = -1;
        }

        if (variables.find(var_name) != variables.end()){
            // 如果加上的变量之前从未被赋值，系统会不执行加法。
            if (!isIdentifier(var_name)) {
                variables[var_name] += multi * std::stoi(value);
            }else{
                if (variables.find(value) != variables.end()){
                    variables[var_name] += multi * variables[value];
                } else {
                    raise(-1);
                    std::cerr<<"Add a invalid var"<<std::endl;
                    // TODO: 错误处理
                }
            }
        } else {
            raise(-1);
            std::cerr<<"Add a invalid var"<<std::endl;
            // TODO: 错误处理
        }
    }

    void Environment::sub(const std::string& var_name, const std::string& value) {
        add(var_name, value, true);
    }

    void Environment::rand(const std::string &var_name, unsigned int min_value, unsigned int max_value) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<unsigned int> dist(min_value, max_value);
        unsigned int rand_var = dist(gen);
        variables[var_name] = rand_var;
    }

    int Environment::getVar(const std::string &var_name) {
        return variables[var_name];
    }

    void Environment::pushCallStack(const CallStackItem& item) {
        call_stack.push(item);
    }

    CallStackItem Environment::popCallStack() {
        CallStackItem res = call_stack.top();
        call_stack.pop();
        return res;
    }

    Environment::Environment(const CallStackItem& initial_call_stack_item) {
        pushCallStack(initial_call_stack_item);
    }


    bool Environment::varExists(const std::string &var_name) {
        if (variables.find(var_name) != variables.end()) {
            return true;
        }
        return false;
    }


} // core