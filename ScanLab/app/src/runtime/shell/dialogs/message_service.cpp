#include "runtime/shell/dialogs/message_service.h"

#include <utility>

void MessageService::show(QString title,
    QString shortText,
    QString detailsText,
    QString errorCode,
    Icon icon)
{
    const Message message{ //
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

void MessageService::showInfo(QString title,
    QString shortText,
    QString detailsText,
    QString errorCode)
{
    show(std::move(title),
        std::move(shortText),
        std::move(detailsText),
        std::move(errorCode),
        Icon::Info);
}

void MessageService::showSuccess(QString title,
    QString shortText,
    QString detailsText,
    QString errorCode)
{
    show(std::move(title),
        std::move(shortText),
        std::move(detailsText),
        std::move(errorCode),
        Icon::Success);
}

void MessageService::showWarning(QString title,
    QString shortText,
    QString detailsText,
    QString errorCode)
{
    show(std::move(title),
        std::move(shortText),
        std::move(detailsText),
        std::move(errorCode),
        Icon::Warning);
}

void MessageService::showError(QString title,
    QString shortText,
    QString detailsText,
    QString errorCode)
{
    show(std::move(title),
        std::move(shortText),
        std::move(detailsText),
        std::move(errorCode),
        Icon::Error);
}

void MessageService::showError(QString title, QString shortText, const ErrorInfo& errorInfo)
{
    show(std::move(title),
        std::move(shortText),
        errorInfo.message(),
        errorInfo.technicalCode,
        Icon::Error);
}

void MessageService::subscribe(Handler handler)
{
    handlers_.push_back(std::move(handler));
}