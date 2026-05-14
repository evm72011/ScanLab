#pragma once

#include <QString>
#include <cstdint>

enum class Icon : std::uint8_t
{
    Info,
    Success,
    Warning,
    Error
};

inline QString getIconSource(const Icon icon)
{
    switch (icon)
    {
    case Icon::Info:
    case Icon::Success:
        return "qrc:/icons/information.svg";

    case Icon::Warning:
        return "qrc:/icons/warning.svg";

    case Icon::Error:
        return "qrc:/icons/error.svg";
    }

    return "qrc:/icons/information.svg";
}
