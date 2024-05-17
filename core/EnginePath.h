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

//    七、 系统图片的参数和要求
//            icon.png 和 system 文件夹下的图片大小有着特殊的要求，必须是 png 格式，大小要满足下面
//            的条件：
//    素材 大小
//    icon.png 必须为 57*57
//    albumbg_0.png、
//    albumbg_1.png……
//    和背景图相同
//            cvThumb.png 随意，推荐 120*90
//    menu.png S60v3：240*144；S60v5：360*216。当然别的大小也可以，但
//            pymo 不会根据不同屏幕大小进行缩放。菜单会被居中显示。
//    message.png、
//    message_mask.png
//            推荐 480*86，当然别的长宽比也可以，pymo 会根据不同屏幕大
//    小进行缩放，并且根据长宽比智能地调整对话框的排版。
//
//    message_cursor.png、
//    message_cursor_mask.png
//            推荐 24*24，接近方形就可以，pymo 会根据字体大小进行缩放
//    name.png、
//    name_mask.png
//            推荐 140*52，当然别的长宽比也可以，pymo 会根据字体大小进
//    行缩放，并且将人名居中显示。
//    option.png、
//    option_mask.png
//            S60v3：260*70；S60v5：390*105，当然别的大小也可以，但 pymo
//    不会根据不同屏幕大小进行缩放。选项会被居中显示。
//    sel_highlight.png、
//    sel_highlight_mask.png
//            推荐 260*48，当然别的长宽比也可以，pymo 会根据不同屏幕大
//    小进行缩放。
    const std::string CONFIG_SCRITP_SUFFIX = ".txt";
    const std::string CONFIG_SYSTEM_IMG_SUFFIX = ".png";

    const std::string PATH_DIR_BG = "/bg/";
    const std::string PATH_DIR_BGM = "/bgm/";
    const std::string PATH_DIR_CHARA = "/chara/";
    const std::string PATH_DIR_SCRIPT = "/script/";
    const std::string PATH_DIR_SE = "/se/";
    const std::string PATH_DIR_SYSTEM = "/system/";
    const std::string PATH_DIR_VIDEO = "/video/";
    const std::string PATH_DIR_VOICE = "/voice/";
    const std::string PATH_FILE_GAMECONFIG = "/gameconfig.txt";


    const std::string PATH_DIR_SAVE = "/save/";
    const std::string PATH_FILE_PREFIX_SAVE = "save_";
    const std::string PATH_FILE_SUFFIX_SAVE = ".json";

    const std::string PATH_FILE_BG_LOGO1 = PATH_DIR_BG + "logo1";
    const std::string PATH_FILE_BG_LOGO2 = PATH_DIR_BG + "logo2";

    const std::string PATH_FILE_ICON = PATH_DIR_SYSTEM + "icon.png";
    const std::string PATH_FILE_CVTHUMB = PATH_DIR_SYSTEM + "cvThumb.png";
    const std::string PATH_FILE_MENU = PATH_DIR_SYSTEM + "menu.png";
    const std::string PATH_FILE_MESSAGE = PATH_DIR_SYSTEM + "message.png";
    const std::string PATH_FILE_MESSAGE_CURSOR = PATH_DIR_SYSTEM + "message_cursor.png";
    const std::string PATH_FILE_NAME = PATH_DIR_SYSTEM + "name.png";
    const std::string PATH_FILE_OPTION = PATH_DIR_SYSTEM + "option.png";
    const std::string PATH_FILE_SELHIGHLIGHT = PATH_DIR_SYSTEM + "sel_highlight.png";

} // core

#endif //LIGHTSONG_ENGINEPATH_H
