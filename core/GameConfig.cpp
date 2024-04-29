//
// Created by KBZ on 2024/4/29.
//

#include "GameConfig.h"
#include "iostream"
namespace core {
    std::unique_ptr<GameConfig> loadGameConfig(const std::string& file_path) {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        std::wifstream file(file_path, std::ios::in);

        if (file.is_open()) {
            std::wstringstream buffer;
            buffer << file.rdbuf();
            std::wstring source = buffer.str();
            file.close();

            std::string narrow_source = converter.to_bytes(source);
            return std::make_unique<GameConfig>(narrow_source);
        }

        return nullptr;
    }

    void printGameConfig(const GameConfig& config) {
        std::cout << "Game Config:\n";
        std::cout << "  gametitle: " << config.gametitle << "\n";
        std::cout << "  platform: " << config.platform << "\n";
        std::cout << "  engineversion: " << config.engineversion << "\n";
        std::cout << "  scripttype: " << config.scripttype << "\n";
        std::cout << "  bgformat: " << config.bgformat << "\n";
        std::cout << "  charaformat: " << config.charaformat << "\n";
        std::cout << "  charamaskformat: " << config.charamaskformat << "\n";
        std::cout << "  bgmformat: " << config.bgmformat << "\n";
        std::cout << "  seformat: " << config.seformat << "\n";
        std::cout << "  voiceformat: " << config.voiceformat << "\n";
        std::cout << "  font: " << config.font << "\n";
        std::cout << "  fontsize: " << config.fontsize << "\n";
        std::cout << "  fontaa: " << (config.fontaa ? "true" : "false") << "\n";
        std::cout << "  hint: " << (config.hint ? "true" : "false") << "\n";
        std::cout << "  prefetching: " << (config.prefetching ? "true" : "false") << "\n";
        std::cout << "  grayselected: " << (config.grayselected ? "true" : "false") << "\n";
        std::cout << "  playvideo: " << (config.playvideo ? "true" : "false") << "\n";
        std::cout << "  textspeed: " << config.textspeed << "\n";
        std::cout << "  bgmvolume: " << config.bgmvolume << "\n";
        std::cout << "  vovolume: " << config.vovolume << "\n";
        std::cout << "  imagesize_width: " << config.imagesize_width << "\n";
        std::cout << "  imagesize_height: " << config.imagesize_height << "\n";
        std::cout << "  startscript: " << config.startscript << "\n";
        std::cout << "  nameboxorig_x: " << config.nameboxorig_x << "\n";
        std::cout << "  nameboxorig_y: " << config.nameboxorig_y << "\n";
        std::cout << "  cgprefix: " << config.cgprefix << "\n";
        std::cout << "  textcolor: " << config.textcolor << "\n";
        std::cout << "  msgtb_top: " << config.msgtb_top << "\n";
        std::cout << "  msgtb_bottom: " << config.msgtb_bottom << "\n";
        std::cout << "  msglr_left: " << config.msglr_left << "\n";
        std::cout << "  msglr_right: " << config.msglr_right << "\n";
        std::cout << "  namealign: " << config.namealign << "\n";
        std::cout << "  anime: " << (config.anime ? "true" : "false") << "\n";
    }
}
