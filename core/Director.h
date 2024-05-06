//
// Created by KBZ on 2024/4/28.
//

#ifndef LIGHTSONG_DIRECTOR_H
#define LIGHTSONG_DIRECTOR_H

#include <string>
#include "GameConfig.h"
#include "Parser.h"
#include "Environment.h"
#include "../platform/cli/CliCommand.h"
#include "../platform/sdl/SdlCommand.h"

namespace core {

    class Director {
    private:
        std::string root_path;

        std::unique_ptr<core::Parser> parser = nullptr;
        std::unique_ptr<core::Environment> environment = nullptr;
    public:
        explicit Director(std::basic_string<char> root_path);
        void setFSEL(unsigned int choice);
        const GameConfig& getConfig() const;

        void loadSave(unsigned char saveIndex);
        void writeSave(unsigned char saveIndex);

        std::unique_ptr<cli::CliCommand> nextCliCommand();
        std::unique_ptr<sdl::SdlCommand> nextSdlCommand();
    };

    std::unique_ptr<sdl::SdlCommand> createSdlCommand(std::unique_ptr<core::Command>& command);

} // core

#endif //LIGHTSONG_DIRECTOR_H
