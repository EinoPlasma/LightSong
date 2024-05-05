//
// Created by EinoPlasma on 2024/5/5.
//

#ifndef LIGHTSONG_UIEVENT_H
#define LIGHTSONG_UIEVENT_H

#include <string>

namespace sdl {

    enum class UiEventType {
        BUTTON_LEFT_CLICK,
        // BUTTON_HOVER,    // 废弃，UiEvent仅作为UI元素（如按钮）发送消息的手段，在上级的handleUiEvent()不会反过来修改UI元素（如按钮）的任何属性
        // BUTTON_NOT_HOVER,
    };

    class UiEvent {
    public:
        virtual UiEventType type() = 0;
    };

    class ButtonLeftClick : public UiEvent {
    public:
        UiEventType type() override {
            return UiEventType::BUTTON_LEFT_CLICK;
        }

        std::string buttonData;

        ButtonLeftClick(std::string buttonData) : buttonData(std::move(buttonData)) {};
    };


} // sdl

#endif //LIGHTSONG_UIEVENT_H
