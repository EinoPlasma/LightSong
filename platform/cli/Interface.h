//
// Created by KBZ on 2024/4/29.
//

#ifndef LIGHTSONG_INTERFACE_H
#define LIGHTSONG_INTERFACE_H

#include "string"
#include "../../core/Director.h"

namespace cli {

    class Interface {
    private:
        // game states
        std::unique_ptr<core::Director> director = nullptr;
    public:
        Interface(const char *root_path);
        void tick(double dt);
        void echo(std::string& str);
        std::string input(std::string& prompt);
    };

} // cli

#endif //LIGHTSONG_INTERFACE_H
