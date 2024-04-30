//
// Created by KBZ on 2024/4/29.
//

#ifndef LIGHTSONG_UTILS_H
#define LIGHTSONG_UTILS_H

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

std::string readUtf8File(const std::string& file_path);

bool isIdentifier(const std::string& str);

#endif // LIGHTSONG_UTILS_H
