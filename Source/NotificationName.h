// File: EnumDefinitions.h
#pragma once
#include <array>
#include <string_view>

enum class NotificationName {
    Gain,
    Overdrive,
    Tone,
    Unknown
};

// `enum` → `string` 変換関数
constexpr std::string_view toString(NotificationName name) {
    switch (name) {
        case NotificationName::Gain:
            return "Gain";
        case NotificationName::Overdrive:
            return "Overdrive";
        case NotificationName::Tone:
            return "Tone";
        default:
            return "Unknown";
    }
}

// `string` → `enum` 変換関数
constexpr Color fromString(std::string_view string) {
    if (string == "Gain") {
        return Color::Gain;
    }
    if (string == "Overdrive") {
        return Color::Overdrive;
    }
    if (string == "Tone") {
        return Color::Tone;
    }
    return Color::Unknown;
}
