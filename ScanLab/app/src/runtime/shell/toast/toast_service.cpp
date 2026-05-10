#include "runtime/shell/toast/toast_service.h"

#include <utility>

void ToastService::show(
    std::string title,
    std::string text,
    Icon icon,
    int durationMs
    )
{
    const Toast toast{
        .title = std::move(title),
        .text = std::move(text),
        .icon = icon,
        .durationMs = durationMs
    };

    for (const auto& handler : handlers_)
    {
        handler(toast);
    }
}

void ToastService::subscribe(Handler handler)
{
    handlers_.push_back(std::move(handler));
}