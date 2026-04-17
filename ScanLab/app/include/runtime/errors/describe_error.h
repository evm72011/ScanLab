#pragma once

#include <magic_enum/magic_enum.hpp>

#include "runtime/errors/error_info.h"

template <typename T>
ErrorInfo describeErrorImpl(
    T error,
    const QHash<T, const char*>& map)
{
    const auto code = magic_enum::enum_name(error);
    const auto technicalCode =
        QString::fromUtf8(code.data(), static_cast<qsizetype>(code.size()));

    const auto it = map.find(error);
    if (it != map.end()) {
        return {technicalCode, it.value(), {}};
    }

    return {
        technicalCode,
        nullptr,
        QStringLiteral("Unknown error code: %1").arg(technicalCode)
    };
}
