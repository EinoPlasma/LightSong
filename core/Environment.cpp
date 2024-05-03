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


} // core