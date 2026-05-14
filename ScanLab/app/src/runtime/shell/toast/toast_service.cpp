#include "runtime/shell/toast/toast_service.h"

#include <utility>

void ToastService::show(QString title, QString text, Icon icon, int durationMs)
{
    const Toast toast{ .title = std::move(title),
        .text = std::move(text),
        .icon = icon,
        .durationMs = durationMs };

    for (const auto& handler : handlers_)
    {
        handler(toast);
    }
}

void ToastService::showInfo(QString title, QString text)
{
    show(std::move(title), std::move(text), Icon::Info, 3000);
}

void ToastService::showWarning(QString title, QString text)
{
    show(std::move(title), std::move(text), Icon::Warning, 5000);
}

void ToastService::showError(QString title, QString text)
{
    show(std::move(title), std::move(text), Icon::Error, 0);
}

void ToastService::subscribe(Handler handler)
{
    handlers_.push_back(std::move(handler));
}