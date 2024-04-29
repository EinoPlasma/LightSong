//
// Created by KBZ on 2024/4/29.
//


#include "utils.h"

std::string readUtf8File(const std::string& file_path) {
    std::ifstream file(file_path, std::ios::in | std::ios::binary);
    if (file.is_open()) {
        std::stringstream buffer;
        buffer << file.rdbuf();
        file.close();
        return buffer.str();
    }
    raise(-1);
    // failed to read
    // return "";
}