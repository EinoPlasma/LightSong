//
// Created by KBZ on 2024/4/28.
//

#ifndef LIGHTSONG_DIRECTOR_H
#define LIGHTSONG_DIRECTOR_H

#include <string>
#include "GameConfig.h"
#include "Parser.h"
#include "../platform/cli/CliCommand.h"

namespace core {

    class Director {
    private:
        std::string root_path;
        std::unique_ptr<core::GameConfig> config = nullptr;
        std::unique_ptr<core::Parser> parser = nullptr;
    public:
        explicit Director(std::basic_string<char> root_path);
        void next();
        std::unique_ptr<cli::CliCommand> nextCliCommand();
    };

} // core

#endif //LIGHTSONG_DIRECTOR_H
