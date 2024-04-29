cmake_minimum_required(VERSION 3.27)
project(LightSong)

set(CMAKE_CXX_STANDARD 14)

add_executable(LightSong main.cpp
        core/Command.cpp
        core/Parser.cpp
        core/Command.h
        compose/Sound.h
        compose/Sound.cpp
        core/Director.cpp
        core/Director.h
        core/GameConfig.h
        utils.h
        core/EnginePath.h
        utils.cpp
        core/GameConfig.cpp)
