#include "runtime/shell/dialogs/message_service.h"

#include <utility>

void MessageService::show(
    std::string title,
    std::string shortText,
    std::string detailsText,
    std::string errorCode,
    Icon icon
    )
{
    const Message message{
        .title = std::move(title),
        .shortText = std::move(shortText),
        .detailsText = std::move(detailsText),
        .errorCode = std::move(errorCode),
        .icon = icon
    };

    for (const auto& handler : handlers_)
    {
        handler(message);
    }
}

void MessageService::showInfo(
    std::string title,
    std::string shortText,
    std::string detailsText,
    std::string errorCode
    )
{
    show(
        std::move(title),
        std::move(shortText),
        std::move(detailsText),
        std::move(errorCode),
        Icon::Info
        );
}

void MessageService::showSuccess(
    std::string title,
    std::string shortText,
    std::string detailsText,
    std::string errorCode
    )
{
    show(
        std::move(title),
        std::move(shortText),
        std::move(detailsText),
        std::move(errorCode),
        Icon::Success
        );
}

void MessageService::showWarning(
    std::string title,
    std::string shortText,
    std::string detailsText,
    std::string errorCode
    )
{
    show(
        std::move(title),
        std::move(shortText),
        std::move(detailsText),
        std::move(errorCode),
        Icon::Warning
        );
}

void MessageService::showError(
    std::string title,
    std::string shortText,
    std::string detailsText,
    std::string errorCode
    )
{
    show(
        std::move(title),
        std::move(shortText),
        std::move(detailsText),
        std::move(errorCode),
        Icon::Error
        );
}

void MessageService::subscribe(Handler handler)
{
    handlers_.push_back(std::move(handler));
}