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

constexpr NotificationName fromString(std::string_view string) {
    if (string == "Gain") {
        return NotificationName::Gain;
    }
    if (string == "Overdrive") {
        return NotificationName::Overdrive;
    }
    if (string == "Tone") {
        return NotificationName::Tone;
    }
    return NotificationName::Unknown;
}
