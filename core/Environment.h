//
// Created by EinoPlasma on 2024/4/30.
//

#ifndef LIGHTSONG_ENVIRONMENT_H
#define LIGHTSONG_ENVIRONMENT_H

#include "unordered_map"
#include "string"
#include "stack"
#include "GameConfig.h"

namespace core {

//    enum VariableKeyword {
//        FSEL,  // 存储#sel 和#select_text 的选择结果
//        FMNOTH,// 游戏中的月份，可以使用#date 显示在屏幕上，也会显示在存档中。
//        FDATE, // 游戏中的日期，可以使用#date 显示在屏幕上，也会显示在存档中。
//    };
//
//    const std::unordered_map<std::string, VariableKeyword> variable_keywords = {
//            {"FSEL", FSEL},
//            {"FMONTH", FMNOTH},
//            {"FDATE", FDATE},
//    };

    std::string const RESERVED_VAR_FSEL = "FSEL";
    std::string const RESERVED_VAR_FMNOTH = "FMNOTH";
    std::string const RESERVED_VAR_FDATE = "FDATE";

    struct CallStackItem {
        std::string script_name; // 脚本文件名，**不加扩展名，不带前面的路径**， 例如“script_01”
        unsigned int line_number; // This line_number is the `currLineNumber` defined in Parser, not the number of lines in the script source file.
    };

    class Environment {
    private:
        // TODO: add global variables support
        std::unordered_map<std::string, int> variables;
        std::stack<CallStackItem> call_stack;
        std::unique_ptr<core::GameConfig> config = nullptr;
    public:
        std::string  curr_script_name;
        unsigned int curr_script_line_number;

        explicit Environment(const std::string &config_path);

        void set(const std::string &var_name, const std::string &var_value);
        void rand(const std::string &var_name, unsigned int min_value, unsigned int max_value);
        void add(const std::string &var_name, const std::string &value, bool flagSub);
        void sub(const std::string &var_name, const std::string &value);

        int getVar(const std::string &var_name);
        bool varExists(const std::string &var_name);
        void pushCallStack(CallStackItem item);
        CallStackItem popCallStack();

        const GameConfig& getConfig() const;
    };

} // core

#endif //LIGHTSONG_ENVIRONMENT_H
