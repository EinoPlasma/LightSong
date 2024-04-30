//
// Created by KBZ on 2024/4/28.
//

#include "Command.h"

namespace core {

    // Factory function to create a Command object based on the provided Command type and parameters
    std::unique_ptr<Command> createCommand(CommandType type, const std::vector<std::string>& params) {
        switch (type) {
            case UNKNOWN:
                return std::make_unique<CommandUnknown>();
            case SAY:
                return std::make_unique<CommandSay>(params);
            case TEXT:
                return std::make_unique<CommandText>(params);
            case TEXT_OFF:
                return std::make_unique<CommandTextOff>();
            case WAITKEY:
                return std::make_unique<CommandWaitKey>();
            case TITLE:
                return std::make_unique<CommandTitle>(params);
            case TITLE_DSP:
                return std::make_unique<CommandTitleDsp>();
            case CHARA:
                return std::make_unique<CommandChara>(params);
            case CHARA_CLS:
                return std::make_unique<CommandCharaCls>(params);
            case CHARA_POS:
                return std::make_unique<CommandCharaPos>(params);
            case BG:
                return std::make_unique<CommandBg>(params);
            case FLASH:
                return std::make_unique<CommandFlash>(params);
            case QUAKE:
                return std::make_unique<CommandQuake>();
            case FADE_OUT:
                return std::make_unique<CommandFadeOut>(params);
            case FADE_IN:
                return std::make_unique<CommandFadeIn>(params);
            case MOVIE:
                return std::make_unique<CommandMovie>(params);
            case TEXTBOX:
                return std::make_unique<CommandTextBox>(params);
            case CHARA_QUAKE:
                return std::make_unique<CommandCharaQuake>(params);
            case CHARA_DOWN:
                return std::make_unique<CommandCharaDown>(params);
            case CHARA_UP:
                return std::make_unique<CommandCharaUp>(params);
            case SCROLL:
                return std::make_unique<CommandScroll>(params);
            case CHARA_Y:
                return std::make_unique<CommandCharaY>(params);
            case CHARA_SCROLL:
                return std::make_unique<CommandCharaScroll>(params);
            case ANIME_ON:
                return std::make_unique<CommandAnimeOn>(params);
            case ANIME_OFF:
                return std::make_unique<CommandAnimeOff>(params);
            case CHARA_ANIME:
                return std::make_unique<CommandCharaAnime>(params);
            case SET:
                return std::make_unique<CommandSet>(params);
            case ADD:
                return std::make_unique<CommandAdd>(params);
            case SUB:
                return std::make_unique<CommandSub>(params);
            case LABEL:
                return std::make_unique<CommandLabel>(params);
            case GOTO:
                return std::make_unique<CommandGoto>(params);
            case IF_GOTO:
                return std::make_unique<CommandIfGoto>(params);
            case CHANGE:
                return std::make_unique<CommandChange>(params);
            case CALL:
                return std::make_unique<CommandCall>(params);
            case RET:
                return std::make_unique<CommandRet>();
            case SEL:
                return std::make_unique<CommandSel>(params);
            case SELECT_TEXT:
                return std::make_unique<CommandSelectText>(params);
            case SELECT_VAR:
                return std::make_unique<CommandSelectVar>(params);
            case SELECT_IMG:
                return std::make_unique<CommandSelectImg>(params);
            case SELECT_IMGS:
                return std::make_unique<CommandSelectImgs>(params);
            case WAIT:
                return std::make_unique<CommandWait>(params);
            case WAIT_SE:
                return std::make_unique<CommandWaitSe>();
            case RAND:
                return std::make_unique<CommandRand>(params);
            case BGM:
                return std::make_unique<CommandBgm>(params);
            case BGM_STOP:
                return std::make_unique<CommandBgmStop>();
            case SE:
                return std::make_unique<CommandSe>(params);
            case SE_STOP:
                return std::make_unique<CommandSeStop>();
            case VO:
                return std::make_unique<CommandVo>(params);
            case LOAD:
                return std::make_unique<CommandLoad>(params);
            case ALBUM:
                return std::make_unique<CommandAlbum>(params);
            case MUSIC:
                return std::make_unique<CommandMusic>();
            case DATE:
                return std::make_unique<CommandDate>(params);
            case CONFIG:
                return std::make_unique<CommandConfig>();
            default:
                break;
        }
        return nullptr;  // Return nullptr if the Command type and parameters are invalid
    }
} // core