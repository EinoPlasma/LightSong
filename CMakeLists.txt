cmake_minimum_required(VERSION 3.25)
project(LightSong)

set(CMAKE_CXX_STANDARD 14)

include(sdl2-config.cmake)
#include(sdl2_image-config.cmake)

add_executable(LightSong sdlInit.cpp
        core/Command.cpp
        core/Parser.cpp
        core/Command.h
        core/Director.cpp
        core/Director.h
        core/GameConfig.h
        utils.h
        core/EnginePath.h
        utils.cpp
        core/GameConfig.cpp
        platform/cli/Interface.cpp
        platform/cli/Interface.h
        platform/cli/CliCommand.cpp
        platform/cli/CliCommand.h
        core/Environment.cpp
        core/Environment.h
        platform/sdl/SdlCommand.cpp
        platform/sdl/SdlCommand.h
        platform/sdl/Interface.cpp
        platform/sdl/Interface.h
        sdlInit.cpp
        platform/sdl/compose/Character.cpp
        platform/sdl/compose/Character.h
        platform/sdl/compose/ui/UI.cpp
        platform/sdl/compose/ui/UI.h
        platform/sdl/compose/Composer.cpp
        platform/sdl/compose/Composer.h
        platform/sdl/compose/ui/SelectionUI.cpp
        platform/sdl/compose/ui/SelectionUI.h
        platform/sdl/sdlUtils.cpp
        platform/sdl/sdlUtils.h
        platform/sdl/compose/ui/BlankUI.cpp
        platform/sdl/compose/ui/BlankUI.h
        platform/sdl/compose/ui/UiEvent.cpp
        platform/sdl/compose/ui/UiEvent.h
        platform/sdl/compose/ui/LabelSetUI.cpp
        platform/sdl/compose/ui/LabelSetUI.h
        include/nlohmann/json_fwd.hpp
        include/nlohmann/json.hpp platform/sdl/compose/ui/uiEventHandler/SaveAndLoadUiEventHandler.cpp platform/sdl/compose/ui/uiEventHandler/SaveAndLoadUiEventHandler.h platform/sdl/compose/ui/uiEventHandler/UiEventHandler.cpp platform/sdl/compose/ui/uiEventHandler/UiEventHandler.h platform/sdl/compose/ui/uiEventHandler/SelectionUiEventHandler.h platform/sdl/compose/ui/uiEventHandler/SelectionUiEventHandler.cpp platform/sdl/Mixer.cpp platform/sdl/Mixer.h)

target_link_libraries(LightSong PRIVATE SDL2::SDL2main SDL2::SDL2 SDL2::SDL2_image SDL2::SDL2_ttf SDL2::SDL2_mixer)