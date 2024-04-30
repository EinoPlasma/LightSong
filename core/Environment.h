//
// Created by EinoPlasma on 2024/4/30.
//

#ifndef LIGHTSONG_ENVIRONMENT_H
#define LIGHTSONG_ENVIRONMENT_H

#include "unordered_map"
#include "string"
#include "stack"

namespace core {

    enum VariableKeyword {
        FSEL,  // 存储#sel 和#select_text 的选择结果
        FMNOTH,// 游戏中的月份，可以使用#date 显示在屏幕上，也会显示在存档中。
        FDATE, // 游戏中的日期，可以使用#date 显示在屏幕上，也会显示在存档中。
    };

    const std::unordered_map<std::string, VariableKeyword> variable_keywords = {
            {"FSEL", FSEL},
            {"FMONTH", FMNOTH},
            {"FDATE", FDATE},
    };

    struct CallStackItem {
        std::string script_path;
        std::string line_number; // This line_number is the `currLineNumber` defined in Parser, not the number of lines in the script source file.
    };

    class Environment {
    private:
        std::unordered_map<std::string, int> variables;
        std::stack<CallStackItem> call_stack;
    public:
        Environment(const CallStackItem& initial_call_stack_item);
        void set(const std::string &var_name, const std::string &var_value);
        void rand(const std::string &var_name, unsigned int min_value, unsigned int max_value);
        void add(const std::string &var_name, const std::string &value, bool flagSub);
        void sub(const std::string &var_name, const std::string &value);

        int getVar(const std::string &var_name);
        bool varExists(const std::string &var_name);
        void pushCallStack(const CallStackItem& item);
        CallStackItem popCallStack();
    };

} // core

#endif //LIGHTSONG_ENVIRONMENT_H
