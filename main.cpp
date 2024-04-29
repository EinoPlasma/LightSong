#include <iostream>
#include <memory>
#include "core/Director.h"
#include "core/GameConfig.h"
#include "utils.h"
/*
 *
    __    _       __    __  _____
   / /   (_)___ _/ /_  / /_/ ___/____  ____  ____ _
  / /   / / __ `/ __ \/ __/\__ \/ __ \/ __ \/ __ `/
 / /___/ / /_/ / / / / /_ ___/ / /_/ / / / / /_/ /
/_____/_/\__, /_/ /_/\__//____/\____/_/ /_/\__, /
        /____/                            /____/
 */

int main() {
    core::Director director = core::Director(R"(C:\Sync\CS\Projects\CLionProjects\LightSong\reference\games\Ever17\s60v5\Ever17)");

    // std::string source = readUtf8File(R"(C:\Sync\CS\Projects\CLionProjects\LightSong\reference\games\Ever17\s60v5\Ever17\gameconfig.txt)");

    // std::cout<<source;

    //std::unique_ptr<core::GameConfig> config = core::loadGameConfig(R"(C:\Sync\CS\Projects\CLionProjects\LightSong\reference\games\Ever17\s60v5\Ever17\gameconfig.txt)");

    //core::printGameConfig(*config);

    for(int i=0;i<200;i++){
        director.next();
    }

    return 0;
}
