//
// Created by KBZ on 2024/4/29.
//

#ifndef LIGHTSONG_GAMECONFIG_H
#define LIGHTSONG_GAMECONFIG_H

#include <string>
#include <fstream>
#include <sstream>
#include <memory>
#include <locale>
#include <codecvt>

namespace core {

    class GameConfig;

    std::unique_ptr<GameConfig> loadGameConfig(const std::string& file_path);

    class GameConfig {
    public:
        std::string source;
        std::string gametitle;
        std::string platform;
        float engineversion;
        std::string scripttype;
        std::string bgformat;
        std::string charaformat;
        std::string charamaskformat;
        std::string bgmformat;
        std::string seformat;
        std::string voiceformat;
        int font;
        int fontsize;
        bool fontaa;
        bool hint;
        bool prefetching;
        bool grayselected;
        bool playvideo;
        int textspeed;
        int bgmvolume;
        int vovolume;
        int imagesize_width;
        int imagesize_height;
        std::string startscript;
        int nameboxorig_x;
        int nameboxorig_y;
        std::string cgprefix;
        std::string textcolor;
        int msgtb_top;
        int msgtb_bottom;
        int msglr_left;
        int msglr_right;
        std::string namealign;
        bool anime;

        GameConfig(std::string& source): source(source) {
            parseConfig();
        }



        friend void printGameConfig(const GameConfig& config);

    private:
        void parseConfig() {
            size_t pos = 0;
            std::string delimiter = "\n";
            std::string token;
            while ((pos = source.find(delimiter)) != std::string::npos) {
                token = source.substr(0, pos);
                parseLine(token);
                source.erase(0, pos + delimiter.length());
            }
            parseLine(source);
        }

        void parseLine(const std::string& line) {
            size_t pos = line.find(",");
            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 1);
            trim(key);
            trim(value);

            if (key == "gametitle") {
                gametitle = value;
            } else if (key == "platform") {
                platform = value;
            } else if (key == "engineversion") {
                engineversion = std::stof(value);
            } else if (key == "scripttype") {
                scripttype = value;
            } else if (key == "bgformat") {
                bgformat = value;
            } else if (key == "charaformat") {
                charaformat = value;
            } else if (key == "charamaskformat") {
                charamaskformat = value;
            } else if (key == "bgmformat") {
                bgmformat = value;
            } else if (key == "seformat") {
                seformat = value;
            } else if (key == "voiceformat") {
                voiceformat = value;
            } else if (key == "font") {
                font = std::stoi(value);
            } else if (key == "fontsize") {
                fontsize = std::stoi(value);
            } else if (key == "fontaa") {
                fontaa = (value == "1");
            } else if (key == "hint") {
                hint = (value == "1");
            } else if (key == "prefetching") {
                prefetching = (value == "1");
            } else if (key == "grayselected") {
                grayselected = (value == "1");
            } else if (key == "playvideo") {
                playvideo = (value == "1");
            } else if (key == "textspeed") {
                textspeed = std::stoi(value);
            } else if (key == "bgmvolume") {
                bgmvolume = std::stoi(value);
            } else if (key == "vovolume") {
                vovolume = std::stoi(value);
            } else if (key == "imagesize") {
                size_t pos2 = value.find(",");
                imagesize_width = std::stoi(value.substr(0, pos2));
                imagesize_height = std::stoi(value.substr(pos2 + 1));
            } else if (key == "startscript") {
                startscript = value;
            } else if (key == "nameboxorig") {
                size_t pos2 = value.find(",");
                nameboxorig_x = std::stoi(value.substr(0, pos2));
                nameboxorig_y = std::stoi(value.substr(pos2 + 1));
            } else if (key == "cgprefix") {
                cgprefix = value;
            } else if (key == "textcolor") {
                textcolor = value;
            } else if (key == "msgtb") {
                size_t pos2 = value.find(",");
                msgtb_top = std::stoi(value.substr(0, pos2));
                msgtb_bottom = std::stoi(value.substr(pos2 + 1));
            } else if (key == "msglr") {
                size_t pos2 = value.find(",");
                msglr_left = std::stoi(value.substr(0, pos2));
                msglr_right = std::stoi(value.substr(pos2 + 1));
            } else if (key == "namealign") {
                namealign = value;
            } else if (key == "anime") {
                anime = (value == "1");
            }
        }

        void trim(std::string& str) {
            str.erase(0, str.find_first_not_of(" \t\n\r\f\v"));
            str.erase(str.find_last_not_of(" \t\n\r\f\v") + 1);
        }
    };

    void printGameConfig(const GameConfig& config);
}

#endif //LIGHTSONG_GAMECONFIG_H