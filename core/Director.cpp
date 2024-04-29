//
// Created by KBZ on 2024/4/28.
//
#include "iostream"
#include "Director.h"
#include "GameConfig.h"
#include "EnginePath.h"
#include "Command.h"

namespace core {
    Director::Director(const char *root_path):root_path(root_path) {
        config = loadGameConfig(root_path + PATH_FILE_GAMECONFIG);
        parser = loadScript(root_path + PATH_DIR_SCRIPT + PATH_FILE_SCRIPT_START);
    }

    void Director::next() {
        std::unique_ptr<Command> cmd = parser->next();
        std::cout<<cmd->type()<<std::endl;
    }
} // core