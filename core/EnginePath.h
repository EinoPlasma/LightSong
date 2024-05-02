//
// Created by KBZ on 2024/4/29.
//

#ifndef LIGHTSONG_ENGINEPATH_H
#define LIGHTSONG_ENGINEPATH_H

#include <string>

namespace core {
    //|-----游戏目录
    //|-------bg（用于放置背景文件或背景资源文件）
    //|        |------ logo1.jpg（游戏运行显示的第一个 logo，扩展名需要与 gameconfig.txt 中的配置符合）
    //|        |------ logo2.jpg（游戏运行显示的第二个 logo，扩展名需要与 gameconfig.txt 中的配置符合）
    //|-------bgm（用于放置背景音乐文件）
    //|-------chara（用于放置立绘文件）
    //|-------save（用于放置存档文件）
    //|-------script（用于放置脚本文件）
    //|-------se（用于放置音效文件）
    //|-------system（用于放置系统图片，如文字框、选项框、鉴赏背景等，图片必须是 png 格式）
    //|------ albumbg_0.png、albumbg_1.png……（CG 鉴赏系统背景）
    //|------ cvThumb.png（CG 鉴赏系统中代表未解锁 CG 的图标）
    //|------ menu.png（系统菜单的背景）
    //|------ message.png、message_mask.png（对话框及其遮罩）
    //|------ name.png、name_mask.png（名字框及其遮罩）
    //|------ option.png、option_mask.png（选项框及其遮罩）
    //|------ sel_highlight.png、sel_highlight_mask.png（选项高亮条目及其遮罩）
    //|------ message_cursor.png、message_cursor_mask.png（对话末尾光标及其遮罩）
    //|-------video（用于放置视频文件）
    //|-------voice（用于放置语音文件）
    //|-------gameconfig.txt（游戏配置文件）
    //|-------icon.png（游戏图标）
    const std::string CONFIG_SCRITP_SUFFIX = ".txt";
    const std::string PATH_DIR_BG = "/bg/";
    const std::string PATH_DIR_BGM = "/bgm/";
    const std::string PATH_DIR_CHARA = "/chara/";
    const std::string PATH_DIR_SAVE = "/save/";
    const std::string PATH_DIR_SCRIPT = "/script/";
    const std::string PATH_DIR_SE = "/se/";
    const std::string PATH_DIR_SYSTEM = "/system/";
    const std::string PATH_DIR_VIDEO = "/video/";
    const std::string PATH_DIR_VOICE = "/voice/";
    const std::string PATH_FILE_GAMECONFIG = "/gameconfig.txt";
    const std::string PATH_FILE_ICON = "/icon.png";

    const std::string PATH_FILE_BG_LOGO1 = "logo1";
    const std::string PATH_FILE_BG_LOGO2 = "logo2";
} // core

#endif //LIGHTSONG_ENGINEPATH_H
