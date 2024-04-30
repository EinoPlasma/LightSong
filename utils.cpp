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

bool isIdentifier(const std::string& str) {
    // Check if string is empty
    if (str.empty()) {
        return false;
    }

    // Check if the first character is a letter or underscore
    char firstChar = str[0];
    if (!std::isalpha(firstChar) && firstChar != '_') {
        return false;
    }

    // Check whether the remaining characters are letters, numbers, or underscores
    for (size_t i = 1; i < str.length(); i++) {
        char currentChar = str[i];
        if (!std::isalnum(currentChar) && currentChar != '_') {
            return false;
        }
    }

    // String passes all checks and is a valid identifier
    return true;
}